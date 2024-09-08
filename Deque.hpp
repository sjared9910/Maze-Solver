#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "abstract_deque.hpp"
#include <utility>
#include <stdexcept>
template <typename T>
class Deque : public AbstractDeque<T>
{
public:

	//constructor
	Deque();
	//copy constructor
	Deque(const Deque <T>& rhs);
	//deconstructor
	virtual ~Deque();
	//determines if the array is empty
	bool isEmpty() const noexcept;
	//pushes value to the front of the array. Grows array by *2 if needed
	void pushFront(const T& item);
	//removes front value from array, decreases array size
	void popFront();
	//returns value of front value in array
	const T& front() const throw(std::runtime_error);
	//pushes value to the back of the array shifting everything by 1 space
	void pushBack(const T& item);
	//removes back value from array, decreases array size
	void popBack();
	//returns back value from array
	const T& back() const throw(std::runtime_error);
	//returns array size
	int size();
	//assignment operator
	Deque<T>& operator=(Deque rhs);

private:
	//default capacity of the array
	int DEFAULT_CAPACTIY;
	//dynamic array of items
	T* items;
	//position of the front value
	int frontQueue;
	//position of the back value
	int backQueue;
	//array size
	int count;
};
#include "Deque.txx"
#endif
