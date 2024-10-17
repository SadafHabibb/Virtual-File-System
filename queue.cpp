#include "queue.hpp"
#include "inode.hpp" 
#include "vector.hpp"

using namespace std;

// Constructor for the Queue class template
template<typename T>
Queue<T>::Queue(int capacity)
{   
    // Allocate memory for the array that will hold queue elements
    this->array = new T[capacity];

    // Initialize the capacity of the queue
    this->capacity = capacity;

    // Initialize the size of the queue to 0 (no elements initially)
    this->size = 0;

    // Initialize the front index to 0 (the first element)
    this->front = 0;

    // Initialize the rear index to capacity - 1 (the last possible position)
    this->rear = -1;

}


// Destructor for the Queue class template
template<typename T>
Queue<T>::~Queue() {
    if (array) {
        // Deallocate the memory used by the array when the queue is destroyed
        delete[] array; 
    }
}

// Function to enqueue an element into the queue
template<typename T>
void Queue<T>::enqueue(T element)
{
    // Check if the queue is full
    if (isFull())
    {
        // If the queue is full, throw a runtime error
        throw std::runtime_error("QueueFull");
    }

    // Increment the rear index, wrapping around if necessary
    rear = (rear + 1) % capacity;

    // Add the new element to the rear of the queue
    array[rear] = element;

    // Increase the size of the queue
    size++;
}

// Function to dequeue an element from the queue
template<typename T>
T Queue<T>::dequeue()
{
    // Check if the queue is empty
    if (isEmpty())
    {
        // If the queue is empty, throw a runtime error
        throw runtime_error("QueueEmpty");
    }

    // Retrieve the element at the front of the queue
    T element = array[front];

    // Increment the front index, wrapping around if necessary
    front = (front + 1) % capacity;

    // Decrease the size of the queue
    size--;

    // Return the dequeued element
    return element;
}

template <typename T>
T Queue<T>::front_element() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return array[front];
}

// Function to check if the queue is empty
template<typename T>
bool Queue<T>::isEmpty()
{
    // Check if the size of the queue is 0
    return size == 0;
}

// Function to check if the queue is full
template<typename T>
bool Queue<T>::isFull()
{
    // Check if the size of the queue has reached its capacity
    return size == capacity;
}

//method to display elements of queue
template <typename T>
void Queue<T>::display() {
    // iterate through elements of queue
    for (int i = 0; i < size; i++) {
        cout << array[(front + i) % capacity] << " ";
    }
    cout << endl;
}

template class Queue<string>;
template class Queue<Inode*>;


