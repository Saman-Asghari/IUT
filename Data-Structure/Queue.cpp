#include "Queue.h"
template<class T>
int Queue<T>::size()const {
	return buffer.get_size();
}
template<class T>
void Queue<T>::Enqueue(T data) {
	buffer.push_back(data);
}
template<class T>
bool Queue<T>::is_empty() const {
	return buffer.get_size() == 0;
}
template<class T>
T Queue<T>::Dequeue() {
	if (is_empty()) {
		throw std::out_of_range("Queue is empty");
	}
	T temp = buffer.pop_front();
	return temp;
}
template<class T>
void Queue<T>::display()const {
	buffer.display();
}
template<class T>
T Queue<T>::first_one_to_out() {
	return buffer[0];
}