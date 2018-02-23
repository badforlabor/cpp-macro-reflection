#include <sstream>
#include <iostream>
#include <vector>
#include "myheader.h"
#include "json.h"

int main2()
{
	Person p;
	p.name = "liubo";
	p.age = 21;
	p.sex = 1;
	p.weight = 65.7f;

	{
		JsonArchive ar;
		ar.Serialize(p);
		ar.Dump();
	}

	std::vector<int> intArray;
	intArray.push_back(1);
	intArray.push_back(2);
	{
		JsonArchive ar;
		ar.SerializeArray(intArray);
		ar.Dump();
	}

	Company c;
	c.id = 1;
	c.person = p;
	c.persons.push_back(p);
	{
		JsonArchive ar;
		ar.Serialize(c);
		ar.Dump();
	}

	EmptyStruct empty;
	{
		JsonArchive ar;
		ar.Serialize(empty);
		ar.Dump();
	}


	return 0;
}