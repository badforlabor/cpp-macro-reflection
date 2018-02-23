#include <sstream>
#include <iostream>
#include <vector>
#include <cassert>

#include "myheader.h"

class BinaryStream
{
public:
	BinaryStream(bool r)
	{
		pos = 0;
		readpos = 0;
	}

	void CopyData(const std::vector<unsigned char>& data)
	{
		buffer = data;
	}
	void CopyData(const BinaryStream& data)
	{
		buffer = data.buffer;
	}

	template<class T>
	BinaryStream& operator<<(T& t)
	{
		// POD类型的才可以直接sizeof
		static_assert(std::is_pod<T>::value, "must be pod");
		int size = sizeof(T);
		buffer.insert(buffer.end(), size, 0);
		memcpy(buffer.data() + pos, &t, size);
		pos += size;
		return *this;
	}
	template<>
	BinaryStream& operator<<(std::string& t)
	{
		size_t size = t.size();
		(*this) << size;
		assert(size <= 1024 * 1024 * 1024);
		buffer.insert(buffer.end(), t.begin(), t.end());
		pos += size;
		return *this;
	}

	template<>
	BinaryStream& operator<<(ByteArray& t)
	{
		size_t size = t.size();
		(*this) << size;
		assert(size <= 1024 * 1024 * 1024);
		buffer.insert(buffer.end(), t.begin(), t.end());
		pos += size;
		return *this;
	}

	template<class T>
	BinaryStream& operator>>(T& t)
	{
		static_assert(std::is_pod<T>::value, "must be pod");
		int size = sizeof(T);
		t = *(T*)(buffer.data() + readpos);
		readpos += size;
		return *this;
	}
	template<>
	BinaryStream& operator >> (std::string& t)
	{
		size_t size = 0;
		(*this) >> size;

		assert(readpos + size <= buffer.size());
		t.append(buffer.begin() + readpos, buffer.begin() + readpos + size);
		readpos += size;
		return *this;
	}
	template<>
	BinaryStream& operator >> (ByteArray& t)
	{
		size_t size = 0;
		(*this) >> size;

		assert(readpos + size <= buffer.size());
		
		t.insert(t.begin(), buffer.begin() + readpos, buffer.begin() + readpos + size);
		readpos += size;
		return *this;
	}


	// 通用序列化
	template<class T>
	BinaryStream& AutoSerialize (bool read, T& t)
	{
		if (read)
		{
			return (*this) >> t;
		}
		else
		{
			return (*this) << t;
		}
	}
	// 通用序列化
	template<class T>
	BinaryStream& AutoSerialize(bool read, std::vector<T>& t)
	{
		// 还没实现。
		static_assert(false, "failed");
		return *this;
	}

private:
	std::vector<unsigned char> buffer;
	int pos;
	int readpos;
};


class BinaryArchive
{
public:
	BinaryArchive() : read(false), ss(false) {}
	BinaryArchive(bool r) : read(r), ss(r){}

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
		size_t size = obj.size();
		Serialize(size);
		if (read)
		{
			obj.resize(size);
		}
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
	template<class T>
	void SerializePod(T& obj)
	{
		SerializeStruct(obj, *this);
	}

	template<> void Serialize<unsigned int>(unsigned int& obj)
	{
		ss.AutoSerialize(read, obj);
	}
	template<> void Serialize<int>(int& obj)
	{
		ss.AutoSerialize(read, obj);
	}
	template<> void Serialize<long>(long& obj)
	{
		ss.AutoSerialize(read, obj);
	}
	template<> void Serialize<long long>(long long& obj)
	{
		ss.AutoSerialize(read, obj);
	}
	template<> void Serialize<float>(float& obj)
	{
		ss.AutoSerialize(read, obj);
	}
	template<> void Serialize<double>(double& obj)
	{
		ss.AutoSerialize(read, obj);
	}
	template<> void Serialize<unsigned char>(unsigned char& obj)
	{
		ss.AutoSerialize(read, obj);
	}
	template<> void Serialize<char>(char& obj)
	{
		ss.AutoSerialize(read, obj);
	}
	template<> void Serialize<std::string>(std::string& obj)
	{
		ss.AutoSerialize(read, obj);
	}
	template<> void Serialize<ByteArray>(ByteArray& obj)
	{
		ss.AutoSerialize(read, obj);
	}

	void Dump()
	{
		
	}

public:
	BinaryStream ss;
	bool read;
};

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