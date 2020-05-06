#ifndef SORTING_INSERTIONSORT_H
#define SORTING_INSERTIONSORT_H

#include "sorteermethode.h"
#include <vector>

/** \class InsertionSort
*/
template<class T>
class InsertionSort: public Sorteermethode<T> {
    void operator()(std::vector<T> &v) const override {
        //loop over all numbers in the vector
        //we can start at one because a list of one number is already sorted
        for(std::size_t i = 1; i < v.size(); i++) {
            //move value to insert into right place into help variable
            T key = std::move(v[i]);
            //we have to check every T which comes before 
            int j = i - 1;
            while(j >= 0 && key < v[j]) {
                //move T which is greater than key one spot
                v[j + 1] = std::move(v[j]);
                j--;
            }
            //now the spot for key is at j+1
            v[j+1] = std::move(key);
        }
    }
};

#endif // SORTING_INSERTIONSORT_H

