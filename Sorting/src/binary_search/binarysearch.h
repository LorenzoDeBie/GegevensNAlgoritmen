//
// Created by lorenzodb on 21/04/2020.
//

#ifndef CLIONTEST_BINARYSEARCH_H
#define CLIONTEST_BINARYSEARCH_H

#include <vector>

template <class T>
int binary_search(const std::vector<T> &v, const T& value) {
    int start = 0, end = v.size(), mid = v.size() / 2;
    while(end - start > 1) {
        const T& mid_val = v[mid];
        if(mid_val == value) return mid;
        else if (value < mid_val) {
            end = mid;
        }
        else {
            start = mid;
        }
        mid = start + (end - start) / 2;
    }
    return value == v[mid] ? mid : -1;
}
#endif //CLIONTEST_BINARYSEARCH_H
