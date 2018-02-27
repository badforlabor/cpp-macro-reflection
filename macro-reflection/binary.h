#pragma once
#include <sstream>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <cassert>
#include "inside_type.h"

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
	const unsigned char* GetDataPtr() const
	{
		return &(buffer[0]);
	}
	size_t GetSize() const
	{
		return buffer.size();
	}
	void Resize(size_t size)
	{
		buffer.resize(size);
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

	// 读取数据之前检查一下，如果数据内容大小不对，那么强制认定为读取完毕了。防止数据被污染！
	bool CheckReadSize(int size)
	{
		assert(readpos + size <= buffer.size());
		if (readpos + size > buffer.size())
		{
			readpos = buffer.size();
			return false;
		}
		return true;
	}

	template<class T>
	BinaryStream& operator >> (T& t)
	{
		static_assert(std::is_pod<T>::value, "must be pod");
		int size = sizeof(T);
		
		if (!CheckReadSize(size))
		{
			return *this;
		}

		t = *(T*)(buffer.data() + readpos);
		readpos += size;
		return *this;
	}


	// 通用序列化
	template<class T>
	BinaryStream& AutoSerialize(bool read, T& t)
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
#if 0
	// 通用序列化
	template<class T>
	BinaryStream& AutoSerialize(bool read, std::vector<T>& t)
	{
		// 还没实现。
		static_assert(false, "failed");
		return *this;
	}
#endif

private:
	std::vector<unsigned char> buffer;
	int pos;
	int readpos;
};

class BinaryArchive
{
public:
	BinaryArchive() : read(false), ss(false) {}
	BinaryArchive(bool r) : read(r), ss(r) {}

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
	
	void Dump()
	{

	}
	const unsigned char* GetDataPtr() const
	{
		return ss.GetDataPtr();
	}
	size_t GetSize() const
	{
		return ss.GetSize();
	}


public:
	BinaryStream ss;
	bool read;
};


template<> BinaryStream& BinaryStream::operator<<(std::string& t);
template<> BinaryStream& BinaryStream::operator<<(ByteArray& t);
template<> BinaryStream& BinaryStream::operator >> (std::string& t);
template<> BinaryStream& BinaryStream::operator >> (ByteArray& t);


template<> void BinaryArchive::Serialize<unsigned long int>(unsigned long int& obj);
template<> void BinaryArchive::Serialize<unsigned int>(unsigned int& obj);
template<> void BinaryArchive::Serialize<int>(int& obj);
template<> void BinaryArchive::Serialize<Int64>(Int64& obj);
template<> void BinaryArchive::Serialize<long>(long& obj);
template<> void BinaryArchive::Serialize<float>(float& obj);
template<> void BinaryArchive::Serialize<double>(double& obj);
template<> void BinaryArchive::Serialize<unsigned char>(unsigned char& obj);
template<> void BinaryArchive::Serialize<char>(char& obj);
template<> void BinaryArchive::Serialize<std::string>(std::string& obj);
template<> void BinaryArchive::Serialize<ByteArray>(ByteArray& obj);

