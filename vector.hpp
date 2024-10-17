#ifndef VECTOR_H
#define VECTOR_H

#include<cstdlib>
#include<stdexcept>
#include<iostream>


using namespace std;

template <typename T>
class Vector
{
	private:
		T *data;						//pointer to int(array) to store elements
		int v_size;						//current size of vector (number of elements in vector)
		int v_capacity;					//capacity of vector
	public:
		Vector();			//Constructor
		~Vector();					//Destructor
		int size() const;				//Return current size of vector
		int capacity() const;			//Return capacity of vector
		bool empty() const; 			//Rturn true if the vector is empty, False otherwise
		const T& front() const;				//Returns reference of the first element in the vector
		const T& back() const;				//Returns reference of the Last element in the vector
		void push_back(T element);		//Add an element at the end of vector
		void insert(int index, T element); //Add an element at the index 
		void erase(int index);			//Removes an element from the index
		T& operator[](int index);			//Returns the reference of an element at given index
		T& at(int index); 				//return reference of the element at given index
		void shrink_to_fit();			//Reduce vector capacity to fit its size
		void display();
		T* begin();
    	T* end();
};
#endif