#ifndef MERGESORT_H
#define MERGESORT_H

#include "sorteermethode.h"
#include <vector>
#include <utility>

/** \class MergeSort
*/
template<class T>
class MergeSort: public Sorteermethode<T> {
    void operator()(std::vector<T> &v) const override {
        if(v.size() == 1) return;
        //divide vector
        std::vector<T> h(v.size() - (v.size() / 2));
        //merge sort whole vector with h
        mergeSort(v, 0, v.size(), h); 
    }
private:
    /** \fn mergeSort
     *  @param v vector to sort
     *  @param startIndex index of v to start sorting at
     *  @param n number of elements to sort
     *  @param h helpvector (size is beg enough)
     * */
    void mergeSort(std::vector<T> &v, int startIndex, int n, std::vector<T> &h) const {
        if(n == 1) return;
        //divide vector
        int size1 = n / 2;
        int size2 = n - (n / 2);
        mergeSort(v, startIndex, size1, h);
        mergeSort(v, startIndex + size1, size2, h);
        //now we need to merge two "vector" [startIndex, startIndex + (n / 2) - 1] 
        // and [startIndex + (n / 2),startIndex + n - 1]
        int counter1 = 0, counter2 = 0, hcounter = 0;
        while(counter1 < size1 && counter2 < size2) { 
            //move smalles value to h vector
            if(v[counter1 + startIndex] < v[counter2 + startIndex + size1]) {
                h[hcounter++] = std::move(v[counter1++ + startIndex]);
            }
            else {
                h[hcounter++] = std::move(v[counter2++ + startIndex + size1]);
            }
            //check which vector was depleted first
            if(counter1 < counter2) {
                //move remaining values of 1 to h
                while(counter1 < size1) {
                    h[hcounter++] = std::move(v[counter1++ + startIndex]);
                }
            }
            else {
                //move remaining values of 2 to h
                while(counter2 < size2) {
                    h[hcounter++] = std::move(v[counter2++ + startIndex + size1]);
                }
            }
            //move h back into v
            for(int i = 0; i < n; i++) {
                v[startIndex + i] = std::move(h[i]);
            }
        }
        
    }
};

#endif

