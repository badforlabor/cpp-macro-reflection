﻿#include <sstream>
#include <iostream>
#include <vector>
#include "myheader.h"

class JsonArchive
{
public:
	template<class T>
	void SerializeField(const char* FieldName, T& Field)
	{
		static_assert(isfake<std::string>::value || std::is_pod<int>::value, "1");
		static_assert(isfake<Person>::value, "1");

		ss << "\"" << FieldName << "\":";// << Field << ",";
		Serialize<T>(Field);
		ss << ",";
	}
	template<class T>
	void SerializeArrayField(const char* FieldName, std::vector<T>& Field)
	{
		ss << "\"" << FieldName << "\":";// << Field << ",";
		SerializeArray<T>(Field);
		ss << ",";
	}
	template<class T>
	void SerializeArray(std::vector<T>& obj)
	{
		ss << "[";
		for (size_t i = 0; i < obj.size(); i++)
		{
			if (i > 0)
			{
				ss << ",";
			}

			Serialize(obj[i]);
		}
		ss << "]";
	}

	template<class T>
	void Serialize(T& obj)
	{
		ss << "{";
		int oldpos = (int)ss.tellp();
		SerializeStruct(obj, *this);
		int pos = (int)ss.tellp();
		if (pos > oldpos)
		{
			// 去掉最后的","
			ss.seekp(pos - 1);
		}
		ss << "}";
	}
	template<> void Serialize<int>(int& obj)
	{
		ss << obj;
	}
	template<> void Serialize<float>(float& obj)
	{
		ss << obj << "f";
	}
	template<> void Serialize<std::string>(std::string& obj)
	{
		ss << "\"" << obj << "\"";
	}
	template<> void Serialize<ByteArray>(ByteArray& obj)
	{
		
	}
	template<> void Serialize<unsigned char>(unsigned char& obj)
	{
		ss << (int)obj;
	}

	void Dump()
	{
		std::cout << ss.str() << std::endl;
	}
private:
	std::stringstream ss;
};


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