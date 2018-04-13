
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


#elif defined(MACRO_ZERO)

#undef STRUCT
#undef Member
#undef VectorMember
#define STRUCT(clsName) \
inline void MacroZero(clsName& obj)
#define Member(memberType,memberName) static_assert(isfake<memberType>::value, "1"); \
{ MacroZero(obj.memberName); }
#define VectorMember(memberType,memberName) static_assert(isfake<memberType>::value, "1");\
{ obj.memberName.clear(); }


#else
/************************************************************************/
/* 定义结构体的序列化函数                                               */
/************************************************************************/

#undef STRUCT
#undef Member
#undef VectorMember
#define STRUCT(clsName) template <> struct isfake<clsName> : std::true_type {}; \
template<class T> void SerializeStruct(clsName& obj, T& ar, bool& b)
#define Member(memberType,memberName) static_assert(isfake<memberType>::value, "1"); \
{ ar.template SerializeField<memberType>(#memberName, obj.memberName, b); if(!b) return; }
#define VectorMember(memberType,memberName) static_assert(isfake<memberType>::value, "1");\
{ ar.template SerializeArrayField<memberType>(#memberName, obj.memberName, b); if(!b) return; }

#endif


