#include "vector.hpp"
#include "inode.hpp" 
#include "queue.hpp"

using namespace std;

template <typename T>
Vector<T>::Vector() {
    this->v_capacity = 0; 
    this->data = new T[v_capacity]; 
    this->v_size = 0; // Initialize the vector's size to 0 because it's empty initially.
}


template <typename T>
Vector<T>::~Vector() {
    if (data) {
     delete[] data; // If data has been allocated, free the memory to prevent memory leaks.
    }
}

template <typename T>
void Vector<T>::push_back(T element) {
    // Check if the element already exists in the vector
    bool isDuplicate = false;
    for (int i = 0; i < v_size; ++i) {
        if (data[i] == element) {
            isDuplicate = true;
            break;
        }
    }

    // If not a duplicate, add the new element to the end of the vector
    if (!isDuplicate) {
        if (v_size >= v_capacity) {
            // Check if the vector is full and needs to be resized.
            if (this->v_capacity == 0) {
                v_capacity = 1; // If it's the first element, set capacity to 1.
            } else {
                v_capacity *= 2; // Double the capacity if the vector is full.
            }

            T *ndata = new T[v_capacity]; // Allocate a new data array with the updated capacity.

            for (int j = 0; j < v_size; j++) {
                ndata[j] = data[j]; // Copy existing elements from the old array to the new array.
            }

            delete[] data; // Free the old data array if it was allocated.
            data = ndata; // Update the data pointer to point to the new array.
        }

        data[v_size] = element; // Add the new element to the end of the vector.
        v_size++; // Increment the vector's size.
    }
}


template <typename T>
void Vector<T>::insert(int index, T element) {
    if (index < 0 || index > v_size) {
        // Check if the specified index is valid (within the vector's bounds).
        throw out_of_range("Index out of range"); // If not, throw an out-of-range exception.
    }

    if (v_size >= v_capacity) {
        if (v_capacity == 0) {
            v_capacity = 1; // If it's the first element, set capacity to 1.
        } else {
            v_capacity *= 2; // Double the capacity if the vector is full.
        }

        T* ndata = new T[v_capacity]; // Allocate a new data array with the updated capacity.

        for (int j = 0; j < index; j++) {
            ndata[j] = data[j]; // Copy existing elements up to the specified index to the new array.
        }

        ndata[index] = element; // Insert the new element at the specified index.

        for (int j = index; j < v_size; j++) {
            ndata[j + 1] = data[j]; // Copy the remaining elements to the new array.
        }

        
        delete[] data; // Free the old data array if it was allocated.
        data = ndata; // Update the data pointer to point to the new array.
    } else {
        for (int j = v_size; j > index; j--) {
            data[j] = data[j - 1]; // Shift elements to make space for the new element.
        }
        data[index] = element; // Insert the new element at the specified index.
    }
    v_size++; // Increment the vector's size.
}

template <typename T>
void Vector<T>::erase(int index) {
    if (index < 0 || index >= v_size) {
        // Check if the specified index is valid (within the vector's bounds).
        throw out_of_range("Index out of range"); // If not, throw an out-of-range exception.
    }

    // T temp = data[index];
    // delete data[index];
    for (int j = index + 1; j < v_size; j++) {
        data[j - 1] = data[j]; // Shift elements to remove the element at the specified index.
    }

    // delete temp;
    v_size--; // Decrement the vector's size.
}

template <typename T>
T& Vector<T>::operator[](int index) {
    return data[index]; // Overloaded operator to access elements by index. Return a reference to the element at the specified index.
}

template <typename T>
T& Vector<T>::at(int index) {
    if (index < 0 || index >= v_size) {
        // Access elements by index with bounds checking.
        throw std::out_of_range("Index out of range"); // Check if the specified index is valid before returning the element.
    }
    return data[index]; // Return a reference to the element at the specified index.
}

template <typename T>
const T& Vector<T>::front() const {
    if (v_size > 0) {
        return data[0];
    } else {
        throw out_of_range("Vector is empty");
    }
}

template <typename T>
const T& Vector<T>::back() const {
    if (v_size > 0) {
        return data[v_size - 1];
    } else {
        throw out_of_range("Vector is empty");
    }
}


template <typename T>
int Vector<T>::size() const {
    return v_size; // Return the current size of the vector (number of elements).
}

template <typename T>
int Vector<T>::capacity() const {
    return v_capacity; // Return the current capacity of the vector (maximum elements it can hold without resizing).
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (v_capacity > v_size) {
        v_capacity = v_size; // Reduce the vector's capacity to match its current size to save memory.

        T* ndata = new T[v_capacity]; // Create a new array with the reduced capacity.

        for (int j = 0; j < v_size; j++) {
            ndata[j] = data[j]; // Copy data from the old array to the new array.
        }

        
        delete[] data; // Free the old data array if it was allocated.
        data = ndata; // Update the data pointer to point to the new array.
    }
}

template <typename T>
bool Vector<T>::empty() const {
    return (v_size == 0); // Check if the vector is empty (size is zero) and return true if it's empty.
}

template <typename T>
void Vector<T>::display() {
    if (v_size == 0) {
        cout << "Vector is empty." << endl;
        return;
    }

    cout << "Vector Contents:" << endl;
    for (int i = 0; i < v_size; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

template <typename T>
T* Vector<T>:: begin() {
    return &data[0];  
}
template <typename T>
T* Vector<T>::end() {
    return data + v_size;  // Returns an iterator pointing one past the end
}


template class Vector<Inode*>;


