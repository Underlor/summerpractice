#include <iostream>
#include "HashTable.h"

using namespace std;
class ContainerOfLiquid
{
public:
	ContainerOfLiquid(char*);
	~ContainerOfLiquid();
	friend std::ostream& operator<<(std::ostream& os, const ContainerOfLiquid& s)
	{
		return os << s.test;
	}

	bool operator ==(ContainerOfLiquid mom)
	{
		return this->test == mom.test;
	}

private:
	char* test;
};

ContainerOfLiquid::ContainerOfLiquid(char* test)
{
	this->test = test;
}

ContainerOfLiquid::~ContainerOfLiquid()
{
	//delete[] test;
}

void main()
{
	int size = 200;
	HashTable<ContainerOfLiquid, char*> table(size);

	table.add(ContainerOfLiquid("H20"), "Water");
	table.add(ContainerOfLiquid("C3H5(OH)3"), "Glycerol");
	table.add(ContainerOfLiquid("CH3OH"), "Methanol");
	table.add(ContainerOfLiquid("C2H5OH"), "Ethanol");

	cout << table.get(ContainerOfLiquid("H20")) << endl;
	cout << table.get(ContainerOfLiquid("C3H5(OH)3")) << endl;
	cout << table.get(ContainerOfLiquid("CH3OH")) << endl;
	cout << table.get(ContainerOfLiquid("C2H5OH")) << endl;

	system("Pause");
}