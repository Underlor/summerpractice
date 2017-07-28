#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Tree.h"

using namespace std;

int _print_t(Node<int> *tree, int is_left, int offset, int depth, char s[20][255])
{
	char b[20];
	int width = 5;

	if (!tree) return 0;

	sprintf(b, "(%03d)", tree->value);

	int left = _print_t(tree->left, 1, offset, depth + 1, s);
	int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

	for (int i = 0; i < width; i++)
		s[2 * depth][offset + left + i] = b[i];

	if (depth && is_left) {
		for (int i = 0; i < width + right; i++)
			s[2 * depth - 1][offset + left + width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

	}
	else if (depth && !is_left) {

		for (int i = 0; i < left + width; i++)
			s[2 * depth - 1][offset - width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset - width / 2 - 1] = '+';
	}

	return left + width + right;
}

void print_t(Node<int> *tree)
{
	char s[20][255];
	for (int i = 0; i < 20; i++)
		sprintf(s[i], "%80s", " ");

	_print_t(tree, 0, 0, 0, s);

	for (int i = 0; i < 20; i++)
		printf("%s\n", s[i]);
}

void main()
{
	Tree<int> tree;
	for (size_t i = 0; i < 16; i++)
	{
		tree.add(i, i);
	}

	print_t(tree.root);

	system("Pause");
}