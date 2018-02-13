using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LitJson;

namespace test_macro
{
    class EmptyStruct
    {

    }
    class Person
    {
        public int age;
        public string name;
        public float weight;
        public int sex;
        public EmptyStruct empty;
    }
    class Company
    {
        public int id;
        public Person person;
        public List<Person> persons;
    }

    class Program
    {
        static void Main(string[] args)
        {
#if false
            var json = System.IO.File.ReadAllText("../../test.txt");
            var obj = JsonMapper.ToObject<Company>(json);
#else
            Company obj = new Company();
            obj.id = 1;
            obj.person = new Person();
            obj.person.age = 21;
            obj.person.name = "liubo";
            obj.person.weight = 65.7f;
            obj.person.sex = 1;
            obj.person.empty = new EmptyStruct();
            obj.persons = new List<Person>();
            obj.persons.Add(obj.person);
#endif
            Console.WriteLine(JsonMapper.ToJson(obj));
        }
    }
}
