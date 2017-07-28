
template <class V>
class Node // структура для представления узлов дерева
{
public:
	Node(int k, V v) : key(k), value(v), left(0), right(0), height(1) {}

	int key;
	V value;
	unsigned char height;
	Node<V> *left, *right;
};

template <class V>
class Tree {
public:
	Tree();
	~Tree();

	Node<V>* root;

	void add(int key, V value)
	{
		root = insert(root, key, value);
	}

	void del(int key)
	{
		root = remove(root, key);
	}

	void print()
	{
		print(root);
	}
private:
	void print(Node<V>* p)
	{
		if (!p) return;

		print(p->left);
		cout << p->value << " ";
		print(p->right);
	}

	unsigned char height(Node<V>* p)
	{
		return p ? p->height : 0;
	}

	int bfactor(Node<V>* p)
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(Node<V>* p)
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	Node<V>* rotateright(Node<V>* p) // правый поворот вокруг p
	{
		Node<V>* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	Node<V>* rotateleft(Node<V>* q) // левый поворот вокруг q
	{
		Node<V>* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	Node<V>* balance(Node<V>* p) // балансировка узла p
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // балансировка не нужна
	}

	Node<V>* insert(Node<V>* p, int k, V value) // вставка ключа k в дерево с корнем p
	{
		if (!p) return new Node<V>(k, value);
		if (k < p->key)
			p->left = insert(p->left, k, value);
		else
			p->right = insert(p->right, k, value);
		return balance(p);
	}

	Node<V>* findmin(Node<V>* p) // поиск узла с минимальным ключом в дереве p 
	{
		return p->left ? findmin(p->left) : p;
	}

	Node<V>* removemin(Node<V>* p) // удаление узла с минимальным ключом из дерева p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	Node<V>* remove(Node<V>* p, int k) // удаление ключа k из дерева p
	{
		if (!p) return 0;
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else //  k == p->key 
		{
			Node<V>* q = p->left;
			Node<V>* r = p->right;
			delete p;
			if (!r) return q;
			Node<V>* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}
};

template<class V>
Tree<V>::Tree()
{
}

template<class V>
Tree<V>::~Tree()
{
}
