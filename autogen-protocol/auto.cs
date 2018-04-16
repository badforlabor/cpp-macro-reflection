using System;
using System.Reflection;
using System.Globalization;
using Microsoft.CSharp;
using System.CodeDom;
using System.CodeDom.Compiler;
using System.Text;
using System.Collections.Generic;
using System.IO;
using NVelocity;
using NVelocity.App;
using NVelocity.Runtime;

namespace autogen_protocol
{
    class ClassInfo
    {
        public string Name { get; set; }
        public List<FieldInfo> Fields { get; set; }
    };

    class TypeUtil
    {
        public bool IsArray(FieldInfo f)
        {
            if (f.FieldType.GetInterface(typeof(System.Collections.IList).Name) != null)
                return true;
            return false;
        }
        public string TypeString(FieldInfo f)
        {
            if (f.FieldType.GetInterface(typeof(System.Collections.IList).Name) != null)
            {
                return string.Format("std::vector<{0}>", dictName(f.FieldType.GenericTypeArguments[0].Name));
            }

            return dictName(f.FieldType.Name);
        }
        public string ConstructInfo(ClassInfo cls)
        {
            StringBuilder buffer = new StringBuilder();
            buffer.Append(cls.Name);
            buffer.Append("()");

            int cnt = 0;
            foreach (var f in cls.Fields)
            {
                string v = "";
                if (f.FieldType == typeof(int) || f.FieldType == typeof(Int64))
                {
                    v = string.Format("{0}({1})", f.Name, "0");
                }
                else if (f.FieldType == typeof(bool))
                {
                    v = string.Format("{0}({1})", f.Name, "false");
                }

                if (!string.IsNullOrEmpty(v))
                {
                    if (cnt == 0)
                    {
                        buffer.Append(":");
                    }
                    if (cnt > 0)
                    {
                        buffer.Append(",");
                    }
                    if (cnt%3 == 2)
                    {
                        buffer.Append("\r\n\t\t");
                    }
                    buffer.Append(v);
                    cnt++;
                }
            }
            buffer.Append("\r\n\t{}");

            return buffer.ToString();
        }

        string dictName(string s)
        {
            if (dict.ContainsKey(s))
            {
                return dict[s];
            }
            throw new Exception("类型必须提前定义：" + s);
        }
        public Dictionary<string, string> dict;
    }


    class auto
    {
        // 加载".cs"文件
        public static Assembly CompileFiles(string[] files)
        {
            // 1.CSharpCodePrivoder
            CSharpCodeProvider objCSharpCodePrivoder = new CSharpCodeProvider();
            // 2.ICodeComplier
            ICodeCompiler objICodeCompiler = objCSharpCodePrivoder.CreateCompiler();
            // 3.CompilerParameters
            CompilerParameters objCompilerParameters = new CompilerParameters();
            objCompilerParameters.ReferencedAssemblies.Add("System.dll");
            objCompilerParameters.GenerateExecutable = false;
            objCompilerParameters.GenerateInMemory = true;
            // 4.CompilerResults
            CompilerResults cr = objICodeCompiler.CompileAssemblyFromFileBatch(objCompilerParameters, files);
            if (cr.Errors.HasErrors)
            {
                Console.WriteLine("编译错误：");
                foreach (CompilerError err in cr.Errors)
                {
                    Console.WriteLine(err.ErrorText);
                }
                return null;
            }
            else
            {
                // 通过反射，调用HelloWorld的实例
                //Assembly objAssembly = cr.CompiledAssembly;
                //object objHelloWorld = objAssembly.CreateInstance("DynamicCodeGenerate.HelloWorld");
                //MethodInfo objMI = objHelloWorld.GetType().GetMethod("OutPut");
                //Console.WriteLine(objMI.Invoke(objHelloWorld, null));
                Console.WriteLine("编译成功！");
                return cr.CompiledAssembly;
            }
        }
        public static void ExecAll()
        {
            string[] files = { "MacroJsonProtocol.cs" };
            var assemble = CompileFiles(files);
            if (assemble == null)
            {
                return;
            }

            var types = assemble.GetTypes();
            List<ClassInfo> AllCls = new List<ClassInfo>();
            foreach (var t in types)
            {
                // 取出所有public成员变量。
                var fileds = t.GetFields();

                ClassInfo cls = new ClassInfo();
                cls.Name = t.Name;
                cls.Fields = new List<FieldInfo>();
                foreach (var f in fileds)
                {
                    cls.Fields.Add(f);
                }
                AllCls.Add(cls);
            }

            // 生成c++代码
            foreach (var cls in AllCls)
            {
                
            }
            GenerateCode(AllCls);
        }

        public static void CommonGenerateCode(List<ClassInfo> AllCls, string TemplateFileName, string OutputFile)
        {
            var util = new TypeUtil();
            util.dict = new Dictionary<string, string>();

            util.dict.Add(typeof(int).Name, "int");
            util.dict.Add(typeof(Int64).Name, "Int64");
            util.dict.Add(typeof(string).Name, "std::string");

            foreach (var cls in AllCls)
            {
                util.dict.Add(cls.Name, cls.Name);
            }


            VelocityEngine ve = new VelocityEngine();
            ve.Init();


            VelocityContext vc = new VelocityContext();
            //传入模板所需要的参数
            vc.Put("AllCls", AllCls); //设置参数为对象，在模板中可以通过$dic.dudu 来引用
            vc.Put("util", util);


            StringWriter sw = new StringWriter();
            // 注意cls.Name必须是属性，而不是普通的成员变量，要不会无效！
            string vt = File.ReadAllText(TemplateFileName);
            ve.Evaluate(vc, sw, "gen-src-tag", vt);

            Console.WriteLine(sw.GetStringBuilder().ToString());

            File.WriteAllText(OutputFile, sw.GetStringBuilder().ToString());
        }
        public static void GenerateCode(List<ClassInfo> AllCls)
        {
            CommonGenerateCode(AllCls, "../../vt-struct.txt", "../../auto_c2gs_protol_struct.h");
            CommonGenerateCode(AllCls, "../../vt-functions.txt", "../../auto_c2gs_protol_function.h");
        }
    }
}
