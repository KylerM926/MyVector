#pragma once
#ifndef MEHLHOFF_MYVECTOR
#define MEHLHOFF_MYVECTOR

#include <cstddef>
#include <stdexcept>

template<typename T>
class MyVector{
private:
	T* elem;
	std::size_t array_size;
	std::size_t space; // how many elements the array has room for
public:
	MyVector(){
		elem = nullptr;
		array_size = 0;
		space = 0;
	}

	~MyVector(){
		delete[] elem;
	}

	// prevent copying (prevent undefined behavior or memory leak)
	MyVector(const MyVector&) = delete;
	MyVector& operator=(const MyVector&) = delete;

	// return the number of elements in container
	std::size_t size() const {
		return array_size;
	}

	// rethrn the allocated capacity
	std::size_t capacity() const {
		return space;
	}

	void reserve(std::size_t new_capacity){
		if (new_capacity <= space){
			return; // already big enoough! nothing to do
		}

		T* new_elem = new T[new_capacity];

		// copy new elements into bigger array
		try
		{
			for (std::size_t i = 0; i < array_size; i++){
				new_elem[i] = elem[i];
			}
		}
		catch (...){
			delete[] new_elem;
			throw;
		}

		// release old array after copy succeeds and switch to new bigger array
		delete[] elem;
		elem = new_elem;
		space = new_capacity;
	}

	void push_back(const T& value){
		if (array_size == space){ // full make more room
			if (space == 0){
				reserve(1); // start with room for 1 if first element
			}
			else {
				reserve(space * 2); // double - keep push back fast
			}
		}

		elem[array_size] = value;
		array_size++;
	}

	T& at(std::size_t index){
		if (index >= array_size){
			throw std::out_of_range("Index out of range!");
		}

		return elem[index];
	}
};

#endif
