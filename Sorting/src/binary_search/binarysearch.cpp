//
// Created by lorenzodb on 22/04/2020.
//
#include <iostream>

#include "binarysearch.h"
#include "sortvector.h"

int main(int argc, char** argv) {
    Sortvector<int> v{0,1,2,3,4,5,6,7,8,9};
    for(int i = 0; i < v.size(); i++) {
        int index = binary_search(v, i);
        if(index != i) {
            std::cerr << "Index is wrong. Expected: " << i << " Actual: " << index << std::endl;
            return -1;
        }
    }

    Sortvector<int> v2{0,1,2,4,5,6,7,8,9,10};
    for(int i = 0; i < v2.size(); i++) {
        int index = binary_search(v2, v2[i]);
        if(index != i) {

        }
    }

    std::vector<int> numbers{3, -1, 11, 255, -255};
    for(int i = 0; i < numbers.size(); i++) {
        int index = binary_search(v2, numbers[i]);
        if(index != -1) {
            std::cerr << "Index is wrong while searching for " << v[i] << ". Expected: -1 Actual: " << index << std::endl;
            return -1;
        }
    }

    std::cout << "OK" << std::endl;
    return 0;
}

