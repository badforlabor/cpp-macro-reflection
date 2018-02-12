

#ifndef STRUCT
#define STRUCT(clsName) struct clsName
#endif
#ifndef Member
#define Member(memberType, memberName) memberType memberName
#endif

STRUCT(Person)
{
	Member(int, age);
	Member(std::string, name);
	Member(float, weight);
	Member(int, sex);
};