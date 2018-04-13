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
		tempB = true;
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
	int GetSize() const
	{
		return (int)buffer.size();
	}
	void Resize(int size)
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
		assert(tempB);

		static_assert(std::is_pod<T>::value, "must be pod");
		int size = sizeof(T);
		
		if (!CheckReadSize(size))
		{
			tempB = false;
			return *this;
		}

		t = *(T*)(buffer.data() + readpos);
		readpos += size;
		return *this;
	}


	// 通用序列化
	template<class T>
	BinaryStream& AutoSerialize(bool read, T& t, bool& b)
	{
		tempB = true;
		if (read)
		{
			BinaryStream& ret = (*this) >> t;
			b = tempB;
			return ret;
		}
		else
		{
			BinaryStream& ret = (*this) << t;
			b = tempB;
			return ret;
		}
	}

private:
	std::vector<unsigned char> buffer;
	int pos;
	int readpos;
	bool tempB;
};

class BinaryArchive
{
public:
	BinaryArchive() : read(false), ss(false) {}
	BinaryArchive(bool r) : read(r), ss(r) {}

	template<class T>
	void SerializeField(const char* FieldName, T& Field, bool& b)
	{
		Serialize<T>(Field, b);
	}
	template<class T>
	void SerializeArrayField(const char* FieldName, std::vector<T>& Field, bool& b)
	{
		SerializeArray<T>(Field, b);
	}
	template<class T>
	void SerializeArray(std::vector<T>& obj, bool& b)
	{
		int size = (int)obj.size();
		Serialize(size, b);
		if (!b)
		{
			return;
		}
		if (read)
		{
			obj.resize(size);
		}
		for (int i = 0; i < (int)size; i++)
		{
			Serialize(obj[i], b);
			if (!b)
			{
				return;
			}
		}
		return;
	}

	template<class T>
	void Serialize(T& obj, bool& b)
	{
		SerializeStruct(obj, *this, b);
	}
	template<class T>
	void SerializePod(T& obj, bool& b)
	{
		SerializeStruct(obj, *this, b);
	}
	template<class T>
	bool Serialize(T& obj)
	{
		bool b = true;
		this->Serialize(obj, b);
		return b;
	}
	
	void Dump()
	{

	}
	const unsigned char* GetDataPtr() const
	{
		return ss.GetDataPtr();
	}
	int GetSize() const
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


template<> void BinaryArchive::Serialize<unsigned long int>(unsigned long int& obj, bool& b);
template<> void BinaryArchive::Serialize<unsigned int>(unsigned int& obj, bool& b);
template<> void BinaryArchive::Serialize<int>(int& obj, bool& b);
template<> void BinaryArchive::Serialize<Int64>(Int64& obj, bool& b);
template<> void BinaryArchive::Serialize<long>(long& obj, bool& b);
template<> void BinaryArchive::Serialize<float>(float& obj, bool& b);
template<> void BinaryArchive::Serialize<double>(double& obj, bool& b);
template<> void BinaryArchive::Serialize<unsigned char>(unsigned char& obj, bool& b);
template<> void BinaryArchive::Serialize<char>(char& obj, bool& b);
template<> void BinaryArchive::Serialize<std::string>(std::string& obj, bool& b);
template<> void BinaryArchive::Serialize<ByteArray>(ByteArray& obj, bool& b);

