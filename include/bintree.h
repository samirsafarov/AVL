#ifndef __bintree_h__
#define __bintree_h__

#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

template <class TType>
class Node
{
public:
	TType key; //ключ
	Node<TType> *left; //левый ук-ль
	Node<TType> *right; //правый ук-ль
	Node<TType> *parent; //родитель
	Node() {left = NULL; right = NULL; parent = NULL;};
	Node(const TType& k) {key = k; left = NULL; right = NULL; parent = NULL;};
};

template <class TType>
class bintree
{	
private:
	int size; //количество элементов в дереве
public:
	Node<TType> *root;
	bintree ();
	~bintree ();
	bintree (const bintree<TType> &);
	Node<TType>* CopyTree (Node<TType> *root);
	void insert (Node<TType>* &root, Node<TType> *node); //вставка
	Node<TType>* Findkey (Node<TType> *root, const TType &); // поиск по ключу
	Node<TType>* FindMax (Node<TType> *root); //поиск максимума
	Node<TType>* FindMin (Node<TType> *root); // минимума
	Node<TType>* FindNext (Node<TType> *root, Node<TType> *node); //поиск следующего за заданным
	void Delete (Node<TType>* root, const TType &); //удаление
	void print (Node<TType> *root); // вывод
	int operator== (const bintree<TType>& a)const;
};

template <class TType>
bintree<TType>::bintree ()
{
	root = NULL;
	size = 0;
};

template <class TType>
bintree<TType>::bintree (const bintree<TType> &a)
{
	root = CopyTree(a.root);
	size = a.size;
};

template <class TType>
bintree<TType>::~bintree ()
{
	delete root;
};

template <class TType>
Node<TType>* bintree<TType>::CopyTree (Node<TType> *node)
{
	if (node == NULL)
        return NULL;
	Node<TType>* tmp = CopyTree (node->left);
	Node<TType>* tmp1 = CopyTree (node ->right);
	Node<TType>* tmp2 = new Node<TType>;
	tmp2 -> key = node->key;
	tmp2->left = tmp;
	tmp2->right = tmp1;
	return tmp2;
};

template <class TType>
void bintree<TType>::insert (Node<TType>* &root, Node<TType> *node)
{
	TType a = node->key;
	if (root == NULL)
	{
		root = new Node<TType>;
		root ->key = a;
		size++;
		return;
	}
	Node<TType>* x = root;
	Node<TType>* y = new Node<TType>;
	while (x != NULL)
	{
 		y = x;
		if (x->key <= node->key)
			x = x->right;
		else
			x = x->left;
	}
	if (y->key <= node->key)
	{
		y->right = new Node<TType>;
		y->right->key = a;
		y->right->parent = y;
		size++;
	}
	else
	{
		y->left = new Node<TType>;
		y->left->key = a;
		y->left->parent = y;
		size++;
	}
};

template <class TType>
void bintree<TType>::Delete (Node<TType>* root, const TType &)
{
	Node<TType>* x = Findkey(root, k);
	if (x == NULL)
		return;
	if ((x->left == NULL) && (x-right == NULL))
	{
		if (x->parent->right == x)
			x->parent->right = NULL;
		else
			x->parent.left = NULL;
		return;
	}
	if (x->left == NULL) && (x->right != NULL)
	{
		Node<TType>* y = x->right;
		y->parent = x->parent;
		if (x->parent->right == x)
			x->parent->right = y;
		else
			x->parent->left = y;
		return;
	}
	if ((x->left != NULL) && (x->right == NULL))
	{
		Node<TType>* y = x->left;
		y->parent = x->parent;
		if (x->parent->right == x)
			x->parent->right = y;
		else
			x->parent->left = y;
		return;
	}
	Node<TType>* y = FindMin(x->right);
	x->key = y->key;
	y->parent->left = y->right;
	if (y->right != NULL)
		y->right->parent = y->parent;
	delete y;
};

template <class TType>
Node<TType>* bintree<TType>::Findkey (Node<TType> *root, const TType &k)
{
	while ((root != NULL) && (root -> key != k))
	{
		if (k < root->key)
			root = root ->left;
		if (k > root ->key)
			root = root -> right;
	}
	if (root == NULL)
		throw
		exception ("Ключ не найден");
	return root;
};

template <class TType>
Node<TType>* bintree<TType>::FindMin (Node<TType> *root)
{
	if (root == NULL)
		throw
		exception ("А дерево то пустое");
	while (root -> left != NULL)
		root = root -> left;
	return root;
};

template <class TType>
Node<TType>* bintree<TType>::FindMax (Node<TType> *root)
{
	if (root == NULL)
		throw
		exception ("А дерево то пустое");
	while (root -> right != NULL)
		root = root -> right;
	return root;
};

template <class TType>
Node<TType>* bintree<TType>::FindNext (Node<TType> *root, Node<TType> *node)
{
	if (root == NULL)
		throw
		exception("А дерево то пустое");
	if (node == NULL)
		throw
		exception("Надо бы ключ не пустой");
	node = Findkey(root, node->key);
	if (node -> right != NULL)
		return FindMin (node -> right);
	while ((node -> parent != NULL) && (node->parent->right == node))
		node = node -> parent;
	return node -> parent;
};
		
template <class TType>
void bintree<TType>::print (Node<TType> *root)
{
	if (root == NULL)
	{
		cout << "Дерево пустое" << endl;
		return;
	}
	queue <Node<TType>*> q;
	q.push(root);
	while (q.empty() == 0)
	{
		Node<TType>* tmp = q.front();
		cout << tmp->key << " ";
		q.pop();
		if (tmp->left != NULL)
			q.push (tmp->left);
		if (tmp->right != NULL)
			q.push(tmp->right);
	}
	cout << endl;
}

template <class TType>
int bintree<TType>::operator== (const bintree<TType>& a)const
{
	if ((root == NULL) && (a.root == NULL))
		return 1;
	if (size != a.size)
		return 0;
	int *z = new int[size];
	int *b = new int[a.size];
	queue <Node<TType>*> q;
	queue <Node<TType>*> p;
	q.push(root);
	int tmp1=0,tmp2=0;
	while (q.empty() == 0)
	{
		Node<TType>* tmp = q.front();
		z[tmp1] = tmp->key;
		q.pop();
		if (tmp->left != NULL)
			q.push (tmp->left);
		if (tmp->right != NULL)
			q.push(tmp->right);
		tmp1++;
	}
	p.push(a.root);
	while (p.empty() == 0)
	{
		Node<TType>* tmp3 = p.front();
		b[tmp2] = tmp3->key;
		p.pop();
		if (tmp3->left != NULL)
			p.push (tmp3->left);
		if (tmp3->right != NULL)
			p.push(tmp3->right);
		tmp2++;
	}
	for (int i=0; i<size; i++)
		if (z[i] != b[i])
			return 0;
	return 1;
}
#endif