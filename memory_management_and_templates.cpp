#include "pch.h"
#include <iostream>

template<typename T>
class DynArray {
private:
	T* data;
	int capacity;
	int length;

public:
	DynArray() {
		data = nullptr;
		capacity = 0;
		length = 0;
	}

	~DynArray() {
		delete[] data;
	}

	int size() { // const
		return length;
	}

	bool isEmpty() { // const
		if (length == 0)
		{
			return true;
		}
		else {
			return false;
		}
	}

	void clear() {
		length = 0;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity <= capacity)
		{
			return;
		}

		T* newData = new T[newCapacity];

		for (int i = 0; i < length; i++)
		{
			newData[i] = data[i];
		}

		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

	// add
	void add(const T& element)
	{
		if (length >= capacity)
		{
			int newCapacity;
			if (capacity == 0) {
				newCapacity = 1;
			}
			else
			{
				newCapacity = capacity * 2;
			}
			reserve(newCapacity);
		}

		data[length++] = element;
	}

	// removeAt
	void removeAt(int index)
	{
		if (index < 0 || index >= length) {
			return;
		}
		for (int i = index; i < length - 1; i++)
		{
			data[i] = data[i + 1];
		}
		length--;
	}

	const T& operator[](int index) const {
		return data[index];
	}
};

/* Memory management + templates

Write dynamic array structure (simplified equivalent of std::vector).
Functions to implement:
- size, returns the number of elements in
- isEmpty, returns true if array is empty (has no elements)
- add, adds element to array, reallocates memory if not enough space (not enough capacity)
- removeAt, removes element at given index
- clear, removes all elements in array (does not deallocate memory)
*/

// array is empty after creation
TEST(DynArrayTests, EmptyArray) {
	DynArray<int> arr;
	EXPECT_EQ(0, arr.size());
	EXPECT_EQ(true, arr.isEmpty());
}

// adding two elements to array and accessing them
TEST(DynArrayTests, AddingElements) {
	DynArray<int> arr;
	arr.add(42);
	arr.add(24);
	EXPECT_EQ(2, arr.size());
	EXPECT_EQ(42, arr[0]);	// here, read about overloading operator[] in class
	EXPECT_EQ(24, arr[1]);
}

TEST(DynArrayTests, RemovingElements) {
	DynArray<int> arr;
	arr.add(42);
	arr.add(24);
	EXPECT_EQ(2, arr.size());
	arr.removeAt(0);	// remove first element
	EXPECT_EQ(24, arr[0]);	// second element (23) fell into [0] because we removed first one (42)
}

TEST(DynArrayTests, ClearAllElements) {
	DynArray<int> arr;
	arr.add(42);
	arr.add(24);
	EXPECT_EQ(2, arr.size());
	arr.clear();
	EXPECT_EQ(0, arr.size());
}

TEST(DynArrayTests, AddElementsInFor) {
	DynArray<int> arr;
	
	for(int i=0; i<1024; ++i)
	{
		arr.add(i);	// memory might need to grow to have all elements inside
	}
}

TEST(DynArrayTests, ReserveMemoryUpfront) {
	DynArray<int> arr;
	arr.reserve(1024);	// reserve memory for 1024 elements
	
	for(int i=0; i<1024; ++i)
	{
		arr.add(i);		// no memory reallocation
	}
}
