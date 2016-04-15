#include "bintree.h"

void main () 
{
	setlocale(LC_CTYPE, "Russian");
	bintree<int> *a = new bintree<int>();
	Node<int> *b = new Node<int>();
	b->key = 9;
	a->insert(a->root,b);
	b->key = 6;
	a->insert(a->root,b);
	b->key = 8;
	a->insert(a->root, b);
	b->key = 2;
	a->insert(a->root, b);
	b->key = 4;
	a->insert(a->root, b);
	b->key = 0;
	a->insert(a->root, b);
	b->key = 5;
	a->insert(a->root, b);
	b->key = 1;
	a->insert(a->root, b);
	b->key = 7;
	a->insert(a->root, b);
	a->print(a->root);
	b->key = 9;
	Node<int> *c = a->FindNext(a->root, b);
	cout << c->key;
}