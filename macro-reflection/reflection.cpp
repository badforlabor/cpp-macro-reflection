#include <sstream>
#include <iostream>

#define EXPAND_MACRO 0
#if EXPAND_MACRO
struct Person
{
	int age;
	std::string name;
	float weight;
	unsigned char sex;
};

template<typename T> void Serialize(Person& obj, T& ar)
{
	ar.Serialize("age", obj.age);
	ar.Serialize("name", obj.name);
	ar.Serialize("weight", obj.weight);
	ar.Serialize("sex", obj.sex);
}
#else
#include "reflection.h"
#undef STRUCT
#undef Member
#define STRUCT(clsName) template<class T> void Serialize(clsName& obj, T& ar)
#define Member(memberType, memberName) ar.Serialize<memberType>(#memberName, obj.##memberName);
#include "reflection.h"
#endif

class StringArchive
{
public:
	template<class T>
	void Serialize(const char* FieldName, T& Field)
	{
		ss << "\"" << FieldName << "\":" << Field << ",";
	}

	void Dump()
	{
		std::cout << ss.str() << std::endl;
	}
private:
	std::stringstream ss;
};


int main()
{
	Person p;
	p.name = "liubo";
	p.age = 21;
	p.sex = 1;
	p.weight = 65.7f;

	StringArchive ar;
	Serialize(p, ar);
	ar.Dump();

	return 0;
}