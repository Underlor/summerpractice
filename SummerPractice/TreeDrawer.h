#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

template<class V>
class TreeDrawer
{
public:
	TreeDrawer(Node<V>* node) : root(node), index(0) {}
	~TreeDrawer();

	void run();
private:
	Node<V>* root;

	Font* font;
	//Drawable** shapes;
	CircleShape** shapes;
	RectangleShape** rects;
	Text** texts;

	int index;

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
	RenderWindow window(VideoMode(1024, 800), "SFML works!");
	window.setFramerateLimit(60);

	font = new Font();
	if (!font->loadFromFile("arial.ttf"))
		return;

	int size = count(root);
	//shapes = new Drawable*[size];
	shapes = new CircleShape*[size];
	rects = new RectangleShape*[size];
	texts = new Text*[size];

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

		for (size_t i = 0; i < index; i++)
		{
			//Drawable* shape = (shapes[i]);

			//if(shape)
			//	window.draw(*shape);
			window.draw(*shapes[i]);
			window.draw(*rects[i]);
			window.draw(*texts[i]);
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
void TreeDrawer<V>::createNodeShape(Node<V>* node)
{
	if (!node) return;

	createNodeShape(node->left);

	CircleShape* shape = new CircleShape(20);
	shape->setFillColor(Color::White);
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	shape->setPosition(index * shape->getRadius() * 2 + shape->getRadius(), 400 - node->height * shape->getRadius() * 3 + 40);

	Text* text = new Text(to_string(node->key), *font, 15);
	text->setFillColor(Color::Black);
	text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
	text->setPosition(shape->getPosition());

	//shapes[index++] = shape;
	//shapes[index++] = text;
	shapes[index] = shape;
	texts[index] = text;

	if (node->left)
	{
		float disx = (index * shape->getRadius() * 2 + shape->getRadius()) - ((index + 1) * shape->getRadius() * 2 + shape->getRadius());
		float disy = (400 - node->height * shape->getRadius() * 2 + 40) - (400 - node->left->height * shape->getRadius() * 2 + 40);

		float dis = sqrt((disx * disx) + (disy * disy));

		RectangleShape* rect = new RectangleShape(*new Vector2f(4, dis));
		rect->setPosition(shape->getPosition());
		rect->setRotation(45);

		rects[index] = rect;
	}
	else if(node->right)
	{
		float disx = (index * shape->getRadius() * 2 + shape->getRadius()) - ((index + 1) * shape->getRadius() * 2 + shape->getRadius());
		float disy = (400 - node->height * shape->getRadius() * 2 + 40) - (400 - node->right->height * shape->getRadius() * 2 + 40);

		float dis = sqrt((disx * disx) + (disy * disy));

		RectangleShape* rect = new RectangleShape(*new Vector2f(4, dis));
		rect->setPosition(shape->getPosition());
		rect->setRotation(-45);

		rects[index] = rect;
	}
	else 
	{
		float dis = 0;

		RectangleShape* rect = new RectangleShape(*new Vector2f(4, dis));
		rect->setPosition(shape->getPosition());
		rect->setRotation(45);

		rects[index] = rect;
	}
	index++;
	createNodeShape(node->right);
}