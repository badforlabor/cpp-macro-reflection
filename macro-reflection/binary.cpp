#include <sstream>
#include <iostream>
#include <vector>
#include <cassert>

#include "myheader.h"
#include "binary.h"


int main1()
{
	Person p;
	p.name = "liubo11111111111111111111111111111111112";
	p.age = 21;
	p.sex = 1;
	p.weight = 65.7f;

	{
		BinaryArchive ar;
		ar.Serialize(p);
		ar.Dump();
	}

	std::vector<int> intArray;
	intArray.push_back(1);
	intArray.push_back(2);
	{
		BinaryArchive ar;
		ar.SerializeArray(intArray);
		ar.Dump();
	}

	Company c;
	c.id = 1;
	c.raw.insert(c.raw.begin(), 10, 1);
	c.person = p;
	c.persons.push_back(p);
	{
		BinaryArchive ar;
		ar.Serialize(c);
		ar.Dump();


		BinaryArchive read(true);
		read.ss = ar.ss;// .CopyData(ar.ss);
		Company c2;
		read.Serialize(c2);
		std::cout << c2.id << std::endl;
	}

	EmptyStruct empty;
	{
		BinaryArchive ar;
		ar.Serialize(empty);
		ar.Dump();
	}



	return 0;
}