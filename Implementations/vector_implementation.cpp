#include <iostream>      // for input/output
#include <stdexcept>     // for exception handling (like std::out_of_range)

// Template class definition: allows MyVector to store any data type (int, float, string, etc.)
template<typename T>
class MyVector {
private:
    T* data;             // Raw pointer to a dynamically allocated array
    size_t _size;        // Current number of elements in the vector
    size_t _capacity;    // Current total allocated capacity of the array

    // Resizes the internal array to new_capacity
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];  // Allocate a new array with the desired capacity
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = data[i];          // Copy existing elements to the new array
        }
        delete[] data;                      // Free memory from the old array
        data = new_data;                    // Point to the new array
        _capacity = new_capacity;           // Update the capacity
    }

public:
    // Default constructor: initialize everything to zero/null
    MyVector() : data(nullptr), _size(0), _capacity(0) {}

    // Destructor: called when object is destroyed, frees dynamically allocated memory
    ~MyVector() {
        delete[] data;                      // Prevent memory leak
    }

    // Adds a new element to the end of the vector
    void push_back(const T& value) {
        // If size == capacity, we need to resize (grow)
        if (_size == _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;  // Double capacity or initialize to 1
            resize(new_capacity);  // Allocate more space
        }
        data[_size++] = value;     // Add element and increment size
    }

    // Removes the last element from the vector
    void pop_back() {
        if (_size == 0) {
            // Throw exception if trying to pop from empty vector
            throw std::out_of_range("pop_back from empty vector");
        }
        --_size;   // Just decrease the size; actual memory remains for simplicity
    }

    // Indexing operator - non-const version (can modify values)
    T& operator[](size_t index) {
        return data[index];  // No bounds checking for performance (like std::vector)
    }

    // Indexing operator - const version (for read-only access)
    const T& operator[](size_t index) const {
        return data[index];
    }

    // Returns current size (number of elements in vector)
    size_t size() const {
        return _size;
    }

    // Returns current capacity (maximum number of elements before reallocation)
    size_t capacity() const {
        return _capacity;
    }

    // Checks whether the vector is empty
    bool empty() const {
        return _size == 0;
    }
};

// ✅ Sample usage of MyVector with integers
int main() {
    MyVector<int> vec;  // Create an empty vector of integers

    // Push integers 1 through 5
    for (int i = 1; i <= 5; ++i) {
        vec.push_back(i);  // Add element to vector
        // Output current element, size, and capacity after each push
        std::cout << "Pushed: " << i
                  << ", Size: " << vec.size()
                  << ", Capacity: " << vec.capacity() << '\n';
    }

    // Remove the last element
    vec.pop_back();
    std::cout << "After pop_back, size: " << vec.size() << '\n';

    // Access and print remaining elements using operator[]
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "vec[" << i << "] = " << vec[i] << '\n';
    }

    return 0;
}
