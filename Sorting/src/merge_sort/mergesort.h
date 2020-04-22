#pragma once

#include "sorteermethode.h"
#include <vector>
    using std::vector;
#include <utility>

/** \class MergeSort
 *  \brief implements merge sort on a vector
 *
 *  recursive and non recursive strategies will be implemented
*/
template<class T>
class MergeSort: public Sorteermethode<T> {
    void operator()(vector<T> &v) const override;
private:
    /**
     * \fn merge_sort_rec
     * \brief recursive version of merge sort
     *
     * \param v vector to sort
     * \param start start index
     * \size size of the vector
     * \h since merge sort sorts out of place we need another vector, same size as v
     */
    void merge_sort_rec(vector<T> &v, int start, int size, vector<T> &h) const;

    void merge(vector<T> &v, int start, int mid, int size, vector<T> &h) const;
};

template <class T>
void MergeSort<T>::operator()(vector<T> &v) const {
    vector<T> h(v.size());
    merge_sort_rec(v, 0, v.size(), h);
}

template<class T>
void MergeSort<T>::merge_sort_rec(vector<T> &v, int start, int size, vector<T> &h) const {
    //vectors of size 1 are already sorted
    if(size < 2) return;
    //split vector in two and use merge sort on both sides
    merge_sort_rec(v, start, size/2, h);
    merge_sort_rec(v, start + size/2, size - size/2, h);
    // merge the two sorted halves
    merge(v, start, start + size/2, size, h);
}

template<class T>
void MergeSort<T>::merge(vector<T> &v, int start, int mid, int size, vector<T> &h) const {
    int i = start, j = mid, counter = start;
    while(i < mid && j < start + size) {
        //use <= to make it stable (we take from left side first
        if(v[i] <= v[j])
            h[counter++] = std::move(v[i++]);
        else
            h[counter++] = std::move(v[j++]);
    }
    if(i == mid) {
        //first half is empty move second half to help vector
        std::move(v.begin() + j, v.begin() + start + size, h.begin() + counter);
    }
    else {
        std::move(v.begin() + i, v.begin() + mid, h.begin() + counter);
    }

    //move results back into v
    std::move(h.begin() + start, h.begin() + start + size, v.begin() + start);
}

