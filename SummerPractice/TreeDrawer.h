#pragma once

#include <SFML/Graphics.hpp>
#include "Bucket.h"


using namespace sf;

template<class V>
class TreeDrawer
{
public:
	TreeDrawer(Node<V>* node) : root(node), index(1) {}
	~TreeDrawer();

	void run();
private:
	Node<V>* root;
					
	Font* font;
	Bucket<int, Drawable*>* shapes;

	int index;

	int count(Node<V>*);
	int getHeight(Node<V>*);
	CircleShape* createNodeShape(Node<V>*, int = 0);

};

template<class V>
TreeDrawer<V>::~TreeDrawer()
{
}

template<class V>
void TreeDrawer<V>::run()
{
	RenderWindow window(VideoMode(1024, 800), "SUKA works!", Style::None | Style::Titlebar | Style::Close);
	window.setFramerateLimit(60);

	font = new Font();
	if (!font->loadFromFile("arial.ttf"))
		return;

	int size = count(root);
	shapes = new Bucket<int, Drawable*>();

	createNodeShape(root, getHeight(root));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(Color::White);

		Liquid<int, Drawable*>* temp = shapes->getHead();
		while (temp->next != NULL)
		{
			Drawable* drawable = temp->value;

			window.draw(*drawable);

			temp = temp->next;
		}

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
int TreeDrawer<V>::getHeight(Node<V>* node)
{
	if (!node) return 0;
	return 1 + max(node->left->height, node->right->height);
}

template<class V>
CircleShape* TreeDrawer<V>::createNodeShape(Node<V>* node, int height)
{
	if (!node) return NULL;

	CircleShape* left = createNodeShape(node->left, height - 1);

	CircleShape* shape = new CircleShape(20);
	shape->setFillColor(Color::Black);
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	shape->setPosition(index * shape->getRadius() * 2 + shape->getRadius(), 400 - height * shape->getRadius() * 3 + 40);

	Text* text = new Text(to_string(node->key), *font, 15);
	text->setFillColor(Color::White);
	text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
	text->setPosition(shape->getPosition());

	shapes->add(index, text);
	shapes->add(index, shape);

	CircleShape* right = createNodeShape(node->right, height - 1);

	Color lineColor = Color::Blue;

	if (left != NULL)
	{
		VertexArray* line = new VertexArray(LinesStrip, 2);
		(*line)[0].position = shape->getPosition();
		(*line)[0].color = lineColor;
		(*line)[1].position = left->getPosition();
		(*line)[1].color = lineColor;

		shapes->add(index, line);
	}
	if (right != NULL)
	{
		VertexArray* line = new VertexArray(LinesStrip, 2);
		(*line)[0].position = shape->getPosition();
		(*line)[0].color = lineColor;
		(*line)[1].position = right->getPosition();
		(*line)[1].color = lineColor;

		shapes->add(index, line);
	}

	index++;

	return shape;
}