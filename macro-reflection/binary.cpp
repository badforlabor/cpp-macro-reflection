#include <sstream>
#include <iostream>
#include <vector>
#include <cassert>

#include "myheader.h"
#include "binary.h"




template<> BinaryStream& BinaryStream::operator<<(std::string& t)
{
	int size = (int)t.size();
	(*this) << size;
	assert(size <= 1024 * 1024 * 1024);
	buffer.insert(buffer.end(), t.begin(), t.end());
	pos += size;
	return *this;
}

template<> BinaryStream& BinaryStream::operator<<(ByteArray& t)
{
	int size = (int)t.size();
	(*this) << size;
	assert(size <= 1024 * 1024 * 1024);
	buffer.insert(buffer.end(), t.begin(), t.end());
	pos += size;
	return *this;
}

template<> BinaryStream& BinaryStream::operator >> (std::string& t)
{
	assert(tempB);

	int size = 0;
	(*this) >> size;

	if (!CheckReadSize(size))
	{
		tempB = false;
		return *this;
	}

	t.append(buffer.begin() + readpos, buffer.begin() + readpos + size);
	readpos += size;
	return *this;
}
template<> BinaryStream& BinaryStream::operator >> (ByteArray& t)
{
	assert(tempB);

	int size = 0;
	(*this) >> size;

	if (!CheckReadSize(size))
	{
		tempB = false;
		return *this;
	}

	t.insert(t.begin(), buffer.begin() + readpos, buffer.begin() + readpos + size);
	readpos += size;
	return *this;
}


template<> void BinaryArchive::Serialize<unsigned long int>(unsigned long int& obj, bool& b)
{
	ss.AutoSerialize(read, obj, b);
}
template<> void BinaryArchive::Serialize<unsigned int>(unsigned int& obj, bool& b)
{
	ss.AutoSerialize(read, obj, b);
}
template<> void BinaryArchive::Serialize<int>(int& obj, bool& b)
{
	ss.AutoSerialize(read, obj, b);
}
template<> void BinaryArchive::Serialize<Int64>(Int64& obj, bool& b)
{
	ss.AutoSerialize(read, obj, b);
}
template<> void BinaryArchive::Serialize<long>(long& obj, bool& b)
{
	ss.AutoSerialize(read, obj, b);
}
template<> void BinaryArchive::Serialize<float>(float& obj, bool& b)
{
	ss.AutoSerialize(read, obj, b);
}
template<> void BinaryArchive::Serialize<double>(double& obj, bool& b)
{
	ss.AutoSerialize(read, obj, b);
}
template<> void BinaryArchive::Serialize<unsigned char>(unsigned char& obj, bool& b)
{
	ss.AutoSerialize(read, obj, b);
}
template<> void BinaryArchive::Serialize<char>(char& obj, bool& b)
{
	ss.AutoSerialize(read, obj, b);
}
template<> void BinaryArchive::Serialize<std::string>(std::string& obj, bool& b)
{
	ss.AutoSerialize(read, obj, b);
}
template<> void BinaryArchive::Serialize<ByteArray>(ByteArray& obj, bool& b)
{
	ss.AutoSerialize(read, obj, b);
}


void MacroZero(int& v)
{
	v = 0;
}
void MacroZero(float& v)
{
	v = 0;
}
void MacroZero(bool& v)
{
	v = false;
}
void MacroZero(Int64& v)
{
	v = 0;
}
extern void MacroZero(ByteArray& v)
{}
extern void MacroZero(std::string& v)
{}












int main1()
{
	Person p;
	p.name = "liubo11111111111111111111111111111111112";
	p.age = 21;
	p.sex = 1;
	p.weight = 65.7f;
	bool b = true;

	{
		BinaryArchive ar;
		ar.Serialize(p, b);
		ar.Dump();
	}

	std::vector<int> intArray;
	intArray.push_back(1);
	intArray.push_back(2);
	{
		BinaryArchive ar;
		ar.SerializeArray(intArray, b);
		ar.Dump();
	}

	Company c;
	c.id = 1;
	c.raw.insert(c.raw.begin(), 10, 1);
	c.person = p;
	c.persons.push_back(p);
	{
		BinaryArchive ar;
		ar.Serialize(c, b);
		ar.Dump();


		BinaryArchive read(true);
		read.ss = ar.ss;// .CopyData(ar.ss);
		Company c2;
		read.Serialize(c2, b);
		std::cout << c2.id << std::endl;
	}

	EmptyStruct empty;
	{
		BinaryArchive ar;
		ar.Serialize(empty, b);
		ar.Dump();
	}



	return 0;
}