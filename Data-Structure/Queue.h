#pragma once
#include"Double_linked_list.h"
template<class T>
class Queue
{
private:
	Double_linked_list<T> buffer;
public:
	void Enqueue(T data);
	T Dequeue();
	bool is_empty() const;
	int size() const;
	void display() const;
	T first_one_to_out();

};
