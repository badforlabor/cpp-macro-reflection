#pragma once
#include <sstream>
#include <iostream>
#include <vector>
#include <cassert>
#include "inside_type.h"

class JsonArchive
{
public:
	template<class T>
	void SerializeField(const char* FieldName, T& Field, bool& b)
	{
		//static_assert(isfake<std::string>::value || std::is_pod<int>::value, "1");
		//static_assert(isfake<Person>::value, "1");

		ss << "\"" << FieldName << "\":";// << Field << ",";
		Serialize<T>(Field, b);
		ss << ",";
	}
	template<class T>
	void SerializeArrayField(const char* FieldName, std::vector<T>& Field, bool& b)
	{
		ss << "\"" << FieldName << "\":";// << Field << ",";
		SerializeArray<T>(Field, b);
		ss << ",";
	}
	template<class T>
	void SerializeArray(std::vector<T>& obj, bool& b)
	{
		ss << "[";
		for (int i = 0; i < (int)obj.size(); i++)
		{
			if (i > 0)
			{
				ss << ",";
			}

			Serialize(obj[i], b);
		}
		ss << "]";
	}

	template<class T>
	void Serialize(T& obj, bool& b)
	{
		ss << "{";
		int oldpos = (int)ss.tellp();
		SerializeStruct(obj, *this, b);
		int pos = (int)ss.tellp();
		if (pos > oldpos)
		{
			// 去掉最后的","
			ss.seekp(pos - 1);
		}
		ss << "}";
	}

	void Dump()
	{
		std::cout << ss.str() << std::endl;
	}

	std::string GetStr()
	{
		return ss.str();
	}
private:
	std::stringstream ss;
};

template<> void JsonArchive::Serialize<unsigned int>(unsigned int& obj, bool& b);
template<> void JsonArchive::Serialize<int>(int& obj, bool& b);
template<> void JsonArchive::Serialize<Int64>(Int64& obj, bool& b);
template<> void JsonArchive::Serialize<long>(long& obj, bool& b);
template<> void JsonArchive::Serialize<float>(float& obj, bool& b);
template<> void JsonArchive::Serialize<double>(double& obj, bool& b);
template<> void JsonArchive::Serialize<unsigned char>(unsigned char& obj, bool& b);
template<> void JsonArchive::Serialize<char>(char& obj, bool& b);
template<> void JsonArchive::Serialize<std::string>(std::string& obj, bool& b);
template<> void JsonArchive::Serialize<ByteArray>(ByteArray& obj, bool& b);

