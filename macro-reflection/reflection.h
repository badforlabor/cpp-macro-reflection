

#ifndef STRUCT
#define STRUCT(clsName) struct clsName
#endif
#ifndef Member
#define Member(memberType, memberName) memberType memberName
#endif
#ifndef VectorMember
#define VectorMember(memberType, memberName) std::vector<memberType> memberName
#endif


STRUCT(EmptyStruct)
{
};

STRUCT(Person)
{
	Member(int, age);
	Member(std::string, name);
	Member(float, weight);
	Member(int, sex);
	Member(EmptyStruct, empty);
};

STRUCT(Company)
{
	Member(int, id);
	Member(Person, person);
	VectorMember(Person, persons);
};
