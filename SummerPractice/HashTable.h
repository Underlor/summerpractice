#pragma once
#include "Bucket.h"

template <class K, class V>
class HashTable
{
public:
	HashTable(int size = 10)
	{
		this->size = size;
		buckets = new Bucket<K, V>[size];
	}

	~HashTable()
	{
		delete[] buckets;
	}

	void add(const K& key, const V& value)
	{	
		buckets[hash(key)].add(key, value);
	}

	V get(const K& key)
	{
		return buckets[hash(key)].get(key);
	}

	bool remove(const K& key)
	{
		return buckets[hash(key)].remove(key);
	}

private:
	int size;
	Bucket<K, V>* buckets;

	unsigned long hash(K key)
	{
		return (*reinterpret_cast<unsigned long*>(&key)) % size;
	}
};