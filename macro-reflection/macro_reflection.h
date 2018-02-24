
#ifndef MACRO_IMPLE

/************************************************************************/
/* 声明结构体                                                           */
/************************************************************************/
#undef STRUCT
#undef Member
#undef VectorMember
#define STRUCT(clsName) struct clsName
#define Member(memberType, memberName) memberType memberName
#define VectorMember(memberType, memberName) std::vector<memberType> memberName


#else
/************************************************************************/
/* 定义结构体的序列化函数                                               */
/************************************************************************/

#undef STRUCT
#undef Member
#undef VectorMember
#define STRUCT(clsName) template <> struct isfake<clsName> : std::true_type {}; \
template<class T> void SerializeStruct(clsName& obj, T& ar)
#define Member(memberType,memberName) static_assert(isfake<memberType>::value, "1"); \
ar.template SerializeField<memberType>(#memberName, obj.memberName);
#define VectorMember(memberType,memberName) static_assert(isfake<memberType>::value, "1");\
ar.template SerializeArrayField<memberType>(#memberName, obj.memberName);

#endif


