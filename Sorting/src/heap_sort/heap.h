//
// Created by lorenzodb on 27/04/2020.
//

#ifndef SORTING_HEAP_H
#define SORTING_HEAP_H

#include <vector>

template <class T>
class Heap : private std::vector<T> {
public:

    // TODO: Possible ways to construct a heap
    Heap();
    Heap(int);

    template<class Enumerable>
    Heap(Enumerable &container);

    // TODO: Operations to define:
    // Insert
    void insert(T &&value);
    // Change root
    void changeRoot(T &value);
    // Delete root
    void deleteRoot();
    // Change element at index
    void changeAtIndex(int index);
};

template<class T>
Heap<T>::Heap() : std::vector<T>() {}

template<class T>
Heap<T>::Heap(int size) : std::vector<T>(size) {}

template<class T>
template<class Enumerable>
Heap<T>::Heap(Enumerable &container) : std::vector<T>() {
    //TODO: implement constructor
    //creation by inserting all elements
    for(auto &iter : container) {
        insert(iter);
    }
}

template<class T>
void Heap<T>::insert(T &&value) {
    int currentIndex = this->size();
    int capacity = this->capacity();
    //increases the size of the vector and adds the new element to the end
    this->push_back(value);
    //now we have to restore the heap condition
    // while not root && parent element is smaller than we are
    while(currentIndex > 0 && (*this)[(currentIndex - 1) / 2] < (*this)[currentIndex]) {
        std::swap((*this)[(currentIndex - 1) / 2], (*this)[currentIndex]);
        currentIndex = (currentIndex - 1) / 2;
    }
}

template<class T>
void Heap<T>::changeRoot(T &value) {

}


#endif //SORTING_HEAP_H
