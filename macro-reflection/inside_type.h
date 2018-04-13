#pragma once
#include <vector>
#include <memory>

class ByteArray : public std::vector<unsigned char>
{
public:
	ByteArray() {}

	void SetData(std::shared_ptr<std::istream> stm)
	{
		stm->seekg(0, std::ios_base::end);
		int data_len = (int)(stm->tellg());
		this->resize(data_len);
		if (data_len > 0)
		{
			stm->seekg(0, std::ios_base::beg);
			stm->read((char*)GetPtr(), data_len);
		}
	}

	value_type* GetPtr()
	{
		value_type& first = (*this)[0];
		return &first;
	}

	void* GetBuffer()
	{
		return (void*)GetPtr();
	}
	int GetSize()
	{
		return (int)size();
	}
};



#ifndef Int64
typedef long long Int64;
#endif


// 加上类型萃取，确保memberType的类型：POD，std::string，和自己定义的结构体。
template<class T>
struct isfake : std::false_type
{
	typedef T inside_type;
};
template<> struct isfake<std::string> : std::true_type
{};
template<> struct isfake<int> : std::true_type
{};
template<> struct isfake<Int64> : std::true_type
{};
template<> struct isfake<float> : std::true_type
{};
template<> struct isfake<ByteArray> : std::true_type
{};


extern void MacroZero(int& v);
extern void MacroZero(float& v);
extern void MacroZero(bool& v);
extern void MacroZero(Int64& v);
extern void MacroZero(ByteArray& v);
extern void MacroZero(std::string& v);