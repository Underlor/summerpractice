#include <iostream>
#include "Tree.h"
#include "TreeDrawer.h"

using namespace std;

void main()
{
	Tree<int> tree;
	for (size_t i = 0; i < 20; i++)
	{
		tree.insert(i, i);
	}


	TreeDrawer<int>* drawer = new TreeDrawer<int>(tree.getRoot());
	drawer->run();
}