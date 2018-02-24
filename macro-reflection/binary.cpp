#include <sstream>
#include <iostream>
#include <vector>
#include <cassert>

#include "myheader.h"
#include "binary.h"




template<> BinaryStream& BinaryStream::operator<<(std::string& t)
{
	size_t size = t.size();
	(*this) << size;
	assert(size <= 1024 * 1024 * 1024);
	buffer.insert(buffer.end(), t.begin(), t.end());
	pos += size;
	return *this;
}

template<> BinaryStream& BinaryStream::operator<<(ByteArray& t)
{
	size_t size = t.size();
	(*this) << size;
	assert(size <= 1024 * 1024 * 1024);
	buffer.insert(buffer.end(), t.begin(), t.end());
	pos += size;
	return *this;
}

template<> BinaryStream& BinaryStream::operator >> (std::string& t)
{
	size_t size = 0;
	(*this) >> size;

	assert(readpos + size <= buffer.size());
	t.append(buffer.begin() + readpos, buffer.begin() + readpos + size);
	readpos += size;
	return *this;
}
template<> BinaryStream& BinaryStream::operator >> (ByteArray& t)
{
	size_t size = 0;
	(*this) >> size;

	assert(readpos + size <= buffer.size());

	t.insert(t.begin(), buffer.begin() + readpos, buffer.begin() + readpos + size);
	readpos += size;
	return *this;
}


template<> void BinaryArchive::Serialize<unsigned int>(unsigned int& obj)
{
	ss.AutoSerialize(read, obj);
}
template<> void BinaryArchive::Serialize<int>(int& obj)
{
	ss.AutoSerialize(read, obj);
}
template<> void BinaryArchive::Serialize<Int64>(Int64& obj)
{
	ss.AutoSerialize(read, obj);
}
template<> void BinaryArchive::Serialize<long>(long& obj)
{
	ss.AutoSerialize(read, obj);
}
template<> void BinaryArchive::Serialize<float>(float& obj)
{
	ss.AutoSerialize(read, obj);
}
template<> void BinaryArchive::Serialize<double>(double& obj)
{
	ss.AutoSerialize(read, obj);
}
template<> void BinaryArchive::Serialize<unsigned char>(unsigned char& obj)
{
	ss.AutoSerialize(read, obj);
}
template<> void BinaryArchive::Serialize<char>(char& obj)
{
	ss.AutoSerialize(read, obj);
}
template<> void BinaryArchive::Serialize<std::string>(std::string& obj)
{
	ss.AutoSerialize(read, obj);
}
template<> void BinaryArchive::Serialize<ByteArray>(ByteArray& obj)
{
	ss.AutoSerialize(read, obj);
}









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