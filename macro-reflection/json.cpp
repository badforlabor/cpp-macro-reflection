#include <sstream>
#include <iostream>
#include <vector>
#include "myheader.h"
#include "json.h"

template<> void JsonArchive::Serialize<unsigned int>(unsigned int& obj, bool& b)
{
	ss << obj;
}
template<> void JsonArchive::Serialize<int>(int& obj, bool& b)
{
	ss << obj;
}
template<> void JsonArchive::Serialize<Int64>(Int64& obj, bool& b)
{
	ss << obj;
}
template<> void JsonArchive::Serialize<long>(long& obj, bool& b)
{
	ss << obj;
}
template<> void JsonArchive::Serialize<float>(float& obj, bool& b)
{
	ss << obj;
}
template<> void JsonArchive::Serialize<double>(double& obj, bool& b)
{
	ss << obj;
}
template<> void JsonArchive::Serialize<unsigned char>(unsigned char& obj, bool& b)
{
	ss << obj;
}
template<> void JsonArchive::Serialize<char>(char& obj, bool& b)
{
	ss << obj;
}
template<> void JsonArchive::Serialize<std::string>(std::string& obj, bool& b)
{
	ss << "\"" << obj << "\"";
}
template<> void JsonArchive::Serialize<ByteArray>(ByteArray& obj, bool& b)
{
	// 把ByteArray当成string
	ss << "\"\"";
}

int main2()
{
	Person p;
	p.name = "liubo";
	p.age = 21;
	p.sex = 1;
	p.weight = 65.7f;
	bool b = true;

	{
		JsonArchive ar;
		ar.Serialize(p, b);
		ar.Dump();
	}

	std::vector<int> intArray;
	intArray.push_back(1);
	intArray.push_back(2);
	{
		JsonArchive ar;
		ar.SerializeArray(intArray, b);
		ar.Dump();
	}

	Company c;
	c.id = 1;
	c.person = p;
	c.persons.push_back(p);
	{
		JsonArchive ar;
		ar.Serialize(c, b);
		ar.Dump();
	}

	EmptyStruct empty;
	{
		JsonArchive ar;
		ar.Serialize(empty, b);
		ar.Dump();
	}


	return 0;
}