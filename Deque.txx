#include "Deque.hpp"

//constructor
template <typename T>
Deque <T>::Deque()
{
	//sets all default values
	DEFAULT_CAPACTIY = 64;
	frontQueue = -1;
	backQueue = -1;
	count = 0;

	//creates dynamic array set to default 64
	items = new T[DEFAULT_CAPACTIY];
}

//copy constructor
template <typename T>
Deque <T>::Deque(const Deque <T>& rhs)
{
	//transfers rhs data
	count = rhs.count;
	frontQueue = rhs.frontQueue;
	backQueue = rhs.backQueue;
	DEFAULT_CAPACTIY = rhs.DEFAULT_CAPACTIY;

	//creates a new dynamic array based on rhs size
	items = new T[DEFAULT_CAPACTIY];

	//transfers all of rhs items
	for (int i = 0; i < DEFAULT_CAPACTIY; i++)
	{
		items[i] = rhs.items[i];
	}
}

//deconstructor
template <typename T>
Deque <T>::~Deque()
{
	//deletes dynamic array
	delete[] items;
}

//Check to see if array is empty
template <typename T>
bool Deque <T>::isEmpty() const noexcept
{
	//if count = 0, array is empty
	return count == 0;
}

//returns array size
template <typename T>
int Deque <T>::size()
{
	//returns occupied spots in array
	return count;
}

//pushes value to front of array
//grows array if needed
template <typename T>
void Deque <T>::pushFront(const T& item)
{
	//if count is equal to the capacity
	if (count == DEFAULT_CAPACTIY)
	{
		//creates a temp array set to item array
		T* hold = items;
		//creates a new dynamic array with 2 * the capacity
		items = new T[2 * DEFAULT_CAPACTIY];

		int k = 0;
		//sets new item array to temp array
		for (int i = frontQueue; i < DEFAULT_CAPACTIY; i++)
		{
			items[i + DEFAULT_CAPACTIY] = hold[i];
			k++;
		}

		//sets everything before the front queue index
		for (int i = 0; i < frontQueue; i++)
		{
			items[i] = hold[i];
		}
		//deletes temp array
		delete[] hold;
		//doubles capacity variable
		DEFAULT_CAPACTIY = DEFAULT_CAPACTIY * 2;
		//realligns front index
		frontQueue = DEFAULT_CAPACTIY - 1 - k;
		//sets item;
		items[frontQueue] = item;
		count++;
	}

	//if array size is under capacity
	else if (count < DEFAULT_CAPACTIY)
	{
		//if array is empty
		if (frontQueue == -1)
		{
			//sets index to first value
			frontQueue = 0;
			backQueue = 0;
		}
		//if array is empty and has value added
		else if (frontQueue == 0)
		{
			//sets front index to array
			frontQueue = DEFAULT_CAPACTIY - 1;
		}
		else
		{
			//decrements front index
			frontQueue = (frontQueue - 1) % DEFAULT_CAPACTIY;
		}
		//sets array front index to item, increases array size
		items[frontQueue] = item;
		count++;
	}
}

//Removes front value from array
template <typename T>
void Deque <T>::popFront()
{
	//if array isnt empty
	if (!isEmpty())
	{
		//goes to next front value
		frontQueue = (frontQueue + 1) % DEFAULT_CAPACTIY;
		//array size is decremented
		count--;
	}
	//if array is empty, error is thrown
	else
	{
		throw std::runtime_error("popfront() called with empty queue");
	}
}

//returns front value
template <typename T>
const T& Deque <T>::front() const throw(std::runtime_error)
{
	//if array is empty, error is thrown
	if (isEmpty())
	{
		throw std::runtime_error("front() called with empty queue");
	}
	//returns front value
	return items[frontQueue];
}

//pushes value to back of array, grows array capacity if needed
template <typename T>
void Deque <T>::pushBack(const T& item)
{
	//if array size is at capacity
	if (count == DEFAULT_CAPACTIY)
	{
		//creates a temp array set to item array
		T* hold = items;
		//creates a new dynamic array with 2 * the capacity
		items = new T[2 * DEFAULT_CAPACTIY];

		//sets new item array to temp array
		for (int i = 0; i < DEFAULT_CAPACTIY; i++)
		{
			items[i] = hold[i];
		}
		//deletes temp array
		delete[] hold;
		//doubles capacity variable
		DEFAULT_CAPACTIY = DEFAULT_CAPACTIY * 2;
	}

	//if array size is under capacity
	if (count < DEFAULT_CAPACTIY)
	{
		//if array is empty
		if (frontQueue == -1)
		{
			//sets array index values
			frontQueue = 0;
			backQueue = 0;
		}
		//if back index reachs capacity
		else if (backQueue == DEFAULT_CAPACTIY - 1)
		{
			//sets index back 0
			backQueue = 0;
		}
		//standard push to back
		else
		{
			//sets back index to next position
			backQueue = (backQueue + 1) % DEFAULT_CAPACTIY;
		}
		//sets item to array at back index
		items[backQueue] = item;
		//increments array size
		count++;
	}
}

//removes back value
template <typename T>
void Deque <T>::popBack()
{
	//if array is not empty
	if (!isEmpty())
	{
		//goes to next back value
		backQueue = (backQueue - 1 + DEFAULT_CAPACTIY) % DEFAULT_CAPACTIY;
		//array size is decremented
		count--;
	}
	//if array is empty, error is thrown
	else
	{
		throw std::runtime_error("popback() called with empty queue");
	}
}

//returns back value from array
template <typename T>
const T& Deque <T>::back() const throw(std::runtime_error)
{
	//if array is empty, error is thrown
	if (isEmpty())
	{
		throw std::runtime_error("back() called with empty queue");
	}
	//returns back value
	return items[backQueue];
}

//operator uses the copy-swap paradigm to create a copy of the parameter
template <typename T>
Deque<T>& Deque<T>::operator=(Deque<T> rhs)
{
	//deletes item array
	delete[] items;
	//swaps rhs data details to item array
	std::swap(count, rhs.count);
	std::swap(frontQueue, rhs.frontQueue);
	std::swap(backQueue, rhs.backQueue);
	std::swap(DEFAULT_CAPACTIY, rhs.DEFAULT_CAPACTIY);

	//creates a new item array based on rhs details
	items = new T[DEFAULT_CAPACTIY];

	//sets item to rhs items
	for (int i = 0; i < DEFAULT_CAPACTIY; i++)
	{
		items[i] = rhs.items[i];
	}
	//returns new items array
	return *this;
}

