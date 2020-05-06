#include "csv.h"
#include "intstring.h"
#include "heap.h"
#include "heapsort.h"

#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>

#define LENGTH 10000


template<class T>
void test_sort(Sorteermethode<T>& sort) {
    Sortvector<T> data(LENGTH);

    //test with random permutation
    data.fill_random();
    std::cout << data << std::endl;
    sort(data);
    std::cout << data << std::endl;
    if(!data.is_sorted()) {
        std::cerr << "Failed to sort random vector" << std::endl;
        exit(1);
    }

    //test with already sorted vector
    data.fill_range();
    std::cout << data << std::endl;
    sort(data);
    std::cout << data << std::endl;
    if(!data.is_sorted()) {
        std::cerr << "Failed to sort sorted vector" << std::endl;
        exit(1);
    }

    //test with reversed vector
    data.fill_reverse();
    std::cout << data << std::endl;
    sort(data);
    std::cout << data << std::endl;
    if(!data.is_sorted()) {
        std::cerr << "Failed to sort reverse sorted vector" << std::endl;
        exit(1);
    }

    std::cout << "OK" << std::endl;
}

void debug_sort(Sorteermethode<int>& sort) {
    Sortvector<int> data{1,5,4,2,3};
    sort(data);
    if(!data.is_sorted()) {
        std::cerr << "Failed to sort vector!" << std::endl;
        exit(1);
    }
    std::cout << "OK" << std::endl;
}

int main()
{
    /*HeapSort<int> test;
    //test one algorithm with a given type
    test_sort(test);
    */

    int arr[] = {5, 8, 6, 20, 3, 54, 1, 9, 8};
    Heap<int> heap(arr);

    heap.insert(21);
    heap.insert(3);
    heap.insert(0);

    return 0;
}
