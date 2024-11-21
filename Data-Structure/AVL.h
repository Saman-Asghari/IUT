#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<typename T, typename V>
struct AVL_elem
{
	T* data;
	V key;
	AVL_elem* p;
	AVL_elem* l_c;
	AVL_elem* r_c;
	int h;
	//external nodes =0
};

template<typename T, typename V>
class AVL_TREE
{
public:
	AVL_TREE();
	int insert(V, T*);
	AVL_elem<T, V>* find(V);
	AVL_elem<T, V>* remove(V);
	AVL_elem<T, V>* remove(AVL_elem<T, V>*);
	vector<AVL_elem<T, V>*>* elements();//sorted incremental (inorder traversal)
	vector<AVL_elem<T, V>*>* inorder_traversal(vector<AVL_elem<T, V>*>*, AVL_elem<T, V>*);
	void r_rotate(AVL_elem<T, V>*);
	void l_rotate(AVL_elem<T, V>*);
	AVL_elem<T, V>* successor(AVL_elem<T, V>*);

	bool is_empty();
	int num_o_elements();
	~AVL_TREE() {};

private:
	int height;
	int count;
	AVL_elem<T, V>* root;
	AVL_elem<T, V>* assumed_null;

};

