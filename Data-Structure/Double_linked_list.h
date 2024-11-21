#pragma once
#include<iostream>
template<class T>
class Node
{
public:
	T data;
	Node* next;
	Node* prev;
	Node(T temp_data) {
		data = temp_data;
		next = nullptr;
		prev = nullptr;
	}

};
template <typename T>
class Double_linked_list
{
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
public:
	Double_linked_list();//constructor
	~Double_linked_list();//distructor
	void push_back(T value);
	void push_front(T value);
	T pop_back();
	T pop_front();
	T find_on_index(int index) const;//note:this is based on array example:a[0]=12 we should insert 0 in the function
	int get_size()const;
	void display()const;
	int does_exist(T data)const;
	int does_exist(T data2, bool (*predicate)(T, T)) const;
	T operator[](int);
};

