
#ifndef MACRO_IMPLE

/************************************************************************/
/* 声明结构体                                                           */
/************************************************************************/
#ifndef STRUCT
#define STRUCT(clsName) struct clsName
#endif
#ifndef Member
#define Member(memberType, memberName) memberType memberName
#endif
#ifndef VectorMember
#define VectorMember(memberType, memberName) std::vector<memberType> memberName
#endif

#else
/************************************************************************/
/* 定义结构体的序列化函数                                               */
/************************************************************************/

// 加上类型萃取，确保memberType的类型：POD，std::string，和自己定义的结构体。
template<class T>
struct isfake : std::false_type
{};
template<> struct isfake<std::string> : std::true_type
{};
template<> struct isfake<int> : std::true_type
{};
template<> struct isfake<float> : std::true_type
{};
template<> struct isfake<ByteArray> : std::true_type
{};

#undef STRUCT
#undef Member
#undef VectorMember
#define STRUCT(clsName) template<> struct isfake<clsName> : std::true_type {}; \
template<class T> void SerializeStruct(clsName& obj, T& ar)
#define Member(memberType, memberName) static_assert(isfake<memberType>::value, "1"); \
		ar.SerializeField<memberType>(#memberName, obj.##memberName);
#define VectorMember(memberType, memberName) ar.SerializeArrayField<memberType>(#memberName, obj.##memberName);


#endif


