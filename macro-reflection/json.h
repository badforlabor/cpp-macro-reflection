#pragma once

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

	void Dump()
	{
		std::cout << ss.str() << std::endl;
	}
private:
	std::stringstream ss;
};


