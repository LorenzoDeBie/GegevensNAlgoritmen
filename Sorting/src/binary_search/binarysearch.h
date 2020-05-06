//
// Created by lorenzodb on 21/04/2020.
//

#ifndef CLIONTEST_BINARYSEARCH_H
#define CLIONTEST_BINARYSEARCH_H

#include <vector>

/**
 * Searches a vector for a given value.
 *
 * @tparam T Type of data inside vector
 * @param v sorted vector to search in
 * @param value value to search for
 * @return index of value in v
 */

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
