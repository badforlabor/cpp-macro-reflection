#include <sstream>
#include <iostream>
#include <vector>

struct FakeReflection {};
#include "reflection.h"
#undef STRUCT
#undef Member
#undef VectorMember
#define STRUCT(clsName) template<class T> void SerializeStruct(clsName& obj, T& ar)
#define Member(memberType, memberName) ar.SerializeField<memberType>(#memberName, obj.##memberName);
#define VectorMember(memberType, memberName) ar.SerializeArrayField<memberType>(#memberName, obj.##memberName);
#include "reflection.h"

class BinaryStream
{
public:
	BinaryStream()
	{
		pos = 0;
		readpos = 0;
		memset(buffer, 0, 10000);
	}
	template<class T>
	BinaryStream& operator<<(T& t)
	{
		int size = sizeof(T);
		memcpy(buffer + pos, &t, size);
		pos += size;
		return *this;
	}
	template<class T>
	BinaryStream& operator>>(T& t)
	{
		int size = sizeof(T);
		t = *(T*)(buffer + readpos);
		readpos += size;
		return *this;
	}

private:
	char buffer[10000];
	int pos;
	int readpos;
};


class BinaryWriteArchive
{
public:
	BinaryWriteArchive() {}

	template<class T>
	void SerializeField(const char* FieldName, T& Field)
	{
		Serialize<T>(Field);
	}
	template<class T>
	void SerializeArrayField(const char* FieldName, std::vector<T>& Field)
	{
		SerializeArray<T>(Field);
	}
	template<class T>
	void SerializeArray(std::vector<T>& obj)
	{
		int size = obj.size();
		Serialize(size);
		for (size_t i = 0; i < size; i++)
		{
			Serialize(obj[i]);
		}
	}

	template<class T>
	void Serialize(T& obj)
	{
		SerializeStruct(obj, *this);
	}
	template<> void Serialize<int>(int& obj)
	{
		ss << obj;
	}
	template<> void Serialize<float>(float& obj)
	{
		ss << obj;
	}
	template<> void Serialize<std::string>(std::string& obj)
	{
		ss << obj;
	}
	template<> void Serialize<unsigned char>(unsigned char& obj)
	{
		ss << obj;
	}

	void Dump()
	{
		
	}

public:
	BinaryStream ss;
};

class BinaryReadArchive
{
public:
	BinaryReadArchive() {}
	template<class T>
	void SerializeField(const char* FieldName, T& Field)
	{
		Serialize<T>(Field);
	}
	template<class T>
	void SerializeArrayField(const char* FieldName, std::vector<T>& Field)
	{
		SerializeArray<T>(Field);
	}
	template<class T>
	void SerializeArray(std::vector<T>& obj)
	{
		int size = obj.size();
		Serialize(size);
		obj.resize(size);
		for (size_t i = 0; i < size; i++)
		{
			Serialize(obj[i]);
		}
	}

	template<class T>
	void Serialize(T& obj)
	{
		SerializeStruct(obj, *this);
	}
	template<> void Serialize<int>(int& obj)
	{
		ss >> obj;
	}
	template<> void Serialize<float>(float& obj)
	{
		ss >> obj;
	}
	template<> void Serialize<std::string>(std::string& obj)
	{
		ss >> obj;
	}
	template<> void Serialize<unsigned char>(unsigned char& obj)
	{
		ss >> obj;
	}

	void Dump()
	{

	}

public:
	BinaryStream ss;
};

int main1()
{
	Person p;
	p.name = "liubo";
	p.age = 21;
	p.sex = 1;
	p.weight = 65.7f;

	{
		BinaryWriteArchive ar;
		ar.Serialize(p);
		ar.Dump();
	}

	std::vector<int> intArray;
	intArray.push_back(1);
	intArray.push_back(2);
	{
		BinaryWriteArchive ar;
		ar.SerializeArray(intArray);
		ar.Dump();
	}

	Company c;
	c.id = 1;
	c.person = p;
	c.persons.push_back(p);
	{
		BinaryWriteArchive ar;
		ar.Serialize(c);
		ar.Dump();


		BinaryReadArchive read;
		read.ss = ar.ss;
		Company c2;
		read.Serialize(c2);
		std::cout << c2.id << std::endl;
	}

	EmptyStruct empty;
	{
		BinaryWriteArchive ar;
		ar.Serialize(empty);
		ar.Dump();
	}



	return 0;
}