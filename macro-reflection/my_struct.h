

STRUCT(EmptyStruct)
{
};


STRUCT(Person)
{
	Member(int, age);
	Member(std::string, name);
	Member(float, weight);
	Member(int, sex);
	Member(EmptyStruct, empty);
};

STRUCT(Company)
{
	Member(int, id);
	Member(Int64, guid);
	Member(Person, person);
	Member(ByteArray, raw);
	VectorMember(Person, persons);
};