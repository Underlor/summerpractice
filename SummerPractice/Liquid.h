#pragma once

template <typename K, typename V>
class Liquid
{
public:
	V value;
	K key;
	Liquid<K, V> *next;
	Liquid(const K inpkey, const V item, Liquid<K, V>* nextptr = NULL) : key(inpkey), value(item), next(nextptr) {}
};
