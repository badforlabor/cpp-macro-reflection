#pragma once
#include <vector>

class ByteArray : public std::vector<unsigned char>
{
public:
	ByteArray() {}
};

#ifndef Int64
typedef long long Int64;
#endif


// 加上类型萃取，确保memberType的类型：POD，std::string，和自己定义的结构体。
template<class T>
struct isfake : std::false_type
{};
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