#include <iostream>
#include "HashTable.h"

using namespace std;
class ContainerOfLiquid
{
public:
	ContainerOfLiquid(char*);
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


void main()
{
	int size = 200;
	HashTable<ContainerOfLiquid, char*> table(size);

	table.add(ContainerOfLiquid("H2O"), "Water");
	table.add(ContainerOfLiquid("C3H5(OH)3"), "Glycerol");
	table.add(ContainerOfLiquid("CH3OH"), "Methanol");
	table.add(ContainerOfLiquid("C2H5OH"), "Ethanol");

	cout << "Key = H2O value = " << table.get(ContainerOfLiquid("H2O")) << endl;
	cout << "Key = C3H5(OH)3 value = " << table.get(ContainerOfLiquid("C3H5(OH)3")) << endl;
	cout << "Key = CH3OH value = " << table.get(ContainerOfLiquid("CH3OH")) << endl;
	cout << "Key = C2H5OH value = " << table.get(ContainerOfLiquid("C2H5OH")) << endl;

	system("Pause");
}