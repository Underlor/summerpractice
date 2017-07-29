#pragma once
#include <SFML/Graphics.hpp>
#include "HashTable.h"

using namespace sf;

template<class V>
class TreeDrawer
{
public:
	TreeDrawer(Node<V>* node) : root(node) {}
	~TreeDrawer();

	void run();
private:
	Node<V>* root;
	CircleShape** shapes;

	int count(Node<V>*);
	void createNodeShape(Node<V>*);
};

template<class V>
TreeDrawer<V>::~TreeDrawer()
{
}

template<class V>
void TreeDrawer<V>::run()
{
	RenderWindow window(VideoMode(600, 800), "SFML works!");
	window.setFramerateLimit(60);
	int size = count(root);
	shapes = new CircleShape*[size];
	for (size_t i = 0; i < size; i++)
		shapes[i] = new CircleShape();

	createNodeShape(root);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		for (size_t i = 0; i <= root->height; i++)
			window.draw(*(shapes[i]));

		window.display();
	}
}

template<class V>
int TreeDrawer<V>::count(Node<V>* node)
{
	if (!node) return 0;
	else return count(node->left) + count(node->right) + 1;
}

template<class V>
void TreeDrawer<V>::createNodeShape(Node<V>* node)
{
	if (!node) return;

	createNodeShape(node->left);
	CircleShape* shape = new CircleShape(20);
	shape->setFillColor(Color::White);
	//shape->setOrigin(shape->getRadius(), shape->getRadius());
	shape->setPosition(node->key * 20/* * (shape->getRadius() + 4)*/, 400);
	//shape->setPosition(20, 20);

	shapes[node->key] = shape;
	createNodeShape(node->right);
}