template <class V>
class Node 
{
public:
	Node(int k, V v) : key(k), value(v), left(0), right(0), height(1) {}

	int key;
	V value;
	unsigned int height;
	Node<V> *left, *right;
};

template <class V>
class Tree {
public:
	Tree();
	~Tree();

	void insert(int key, V value)
	{
		root = insert(root, key, value);
	}

	void remove(int key)
	{
		root = remove(root, key);
	}

	Node<V>* getRoot()
	{
		return root;
	}
private:
	Node<V>* root;

	unsigned int getHeight(Node<V>* node)
	{
		return node ? node->height : 0;
	}

	int getBalanceFactor(Node<V>* node)
	{
		return getHeight(node->right) - getHeight(node->left);
	}

	void fixHeight(Node<V>* node)
	{
		unsigned int heightLeft = getHeight(node->left);
		unsigned int heightRight = getHeight(node->right);

		node->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
	}

	Node<V>* rotateRight(Node<V>* node) // правый поворот вокруг node
	{
		Node<V>* temp = node->left;
		node->left = temp->right;
		temp->right = node;

		fixHeight(node);
		fixHeight(temp);

		return temp;
	}

	Node<V>* rotateLeft(Node<V>* node) // левый поворот вокруг node
	{
		Node<V>* temp = node->right;
		node->right = temp->left;
		temp->left = node;

		fixHeight(node);
		fixHeight(temp);

		return temp;
	}

	Node<V>* balance(Node<V>* node) // балансировка узла node
	{
		fixHeight(node);

		if (getBalanceFactor(node) == 2)
		{
			if (getBalanceFactor(node->right) < 0)
			{
				node->right = rotateRight(node->right);
			}

			return rotateLeft(node);
		}
		if (getBalanceFactor(node) == -2)
		{
			if (getBalanceFactor(node->left) > 0)
			{
				node->left = rotateLeft(node->left);
			}

			return rotateRight(node);
		}

		return node; // балансировка не нужна
	}

	Node<V>* insert(Node<V>* node, int key, V value) // вставка ключа key в дерево с корнем node
	{
		if (!node)
		{
			return new Node<V>(key, value);
		}

		if (key < node->key)
		{
			node->left = insert(node->left, key, value);
		}
		else
		{
			node->right = insert(node->right, key, value);
		}

		return balance(node);
	}

	Node<V>* findMin(Node<V>* node) // поиск узла с минимальным ключом в дереве node 
	{
		return node->left ? findMin(node->left) : node;
	}

	Node<V>* removeMin(Node<V>* node) // удаление узла с минимальным ключом из дерева node
	{
		if (node->left == 0)
		{
			return node->right;
		}

		node->left = removeMin(node->left);
		return balance(node);
	}

	Node<V>* remove(Node<V>* node, int k) // удаление ключа k из дерева node
	{
		if (!node)
		{
			return 0;
		}

		if (k < node->key)
		{
			node->left = remove(node->left, k);
		}
		else if (k > node->key)
		{
			node->right = remove(node->right, k);
		}
		else
		{
			Node<V>* q = node->left;
			Node<V>* r = node->right;
			delete node;
			if (!r) return q;
			Node<V>* min = findMin(r);
			min->right = removeMin(r);
			min->left = q;
			return balance(min);
		}

		return balance(node);
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
