#pragma once
#include "Liquid.h"

template <typename K, typename V>
class Bucket
{
public:
	Bucket(K key = NULL, V value = NULL) : Head(new Liquid<K, V>(key, value)) {};
	~Bucket();

	void add(K key, V Value);
	bool remove(K key);
	V get(const K& key);

	Liquid<K, V>* getHead()
	{
		return Head;
	}

private:
	Liquid<K, V>* Head;
};

template <typename K, typename V>
inline Bucket<K, V>::~Bucket()
{
	while (Head != NULL)
	{
		Liquid<K, V> *temp = Head->next;
		delete Head;
		Head = temp;
	}
}

template <typename K, typename V>
void Bucket<K, V>::add(K key, V Value)
{
	Liquid<K, V> *temp = new Liquid<K,V>(key, Value, Head);
	Head = temp;
}

template <typename K, typename V>
bool Bucket<K, V>::remove(K key)
{
	Liquid<K, V> *back = NULL;
	Liquid<K, V> *temp = Head;
	while (temp != NULL)
	{
		if (temp->key == key)
		{
			if (back != NULL)
			{
				back->next = temp->next;
			}
			delete temp;
			return true;

		}
		else
		{
			back = temp;
			temp = temp->next;
		}
	}
	return false;
}

template <typename K, typename V>
V Bucket<K, V>::get(const K& key)
{
	Liquid<K, V> *temp = Head;
	while (temp != NULL)
	{
		if (temp->key == key)
		{
			return temp->value;
		}
		temp = temp->next;
	}
	return NULL;
}
