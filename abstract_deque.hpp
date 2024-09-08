#ifndef ABSTRACT_DEQUE_HPP
#define ABSTRACT_DEQUE_HPP

template <typename T>
class AbstractDeque
{
public:

	//Returns true if the deque is empty, else false
	virtual bool isEmpty() const noexcept = 0;

	//Adds item in front of queue
	virtual void pushFront(const T& item) = 0;
	
	//Removes item from front of queue
	virtual void popFront() = 0;

	//Returns item in front of queue
	virtual const T& front() const = 0;

	//Adds item at back of queue
	virtual void pushBack(const T& item) = 0;

	//Removes item from back of queue
	virtual void popBack() = 0;

	//Returns item at back of queue
	virtual const T& back() const = 0;
};

#endif
