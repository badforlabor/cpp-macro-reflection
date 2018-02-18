

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
	Member(Person, person);
	VectorMember(Person, persons);
};