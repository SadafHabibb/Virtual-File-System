#ifndef QUEUE_H
#define QUEUE_H
#include<cstdlib>
#include<stdexcept>
#include <iostream>


using namespace std;
template <typename T>

class Queue
{
	private:
		T *array;
		int capacity;	//Max Capacity of the Queue
		int size;		//current number of elements in the Queue
		int front;		//front of the Queue
		int rear;		//index where a new element will be added
	public:
		Queue(int capacity=10);
		~Queue();
		void enqueue(T element); 
		T dequeue();
		bool isEmpty();
		bool isFull();
		T front_element();
		void display();
};
//================================================
#endif