//
// Created by lorenzodb on 06/04/2020.
//

#ifndef CLIONTEST_QUICKSORT_H
#define CLIONTEST_QUICKSORT_H

#include <sorteermethode.h>

template<class T>
class QuickSort : public Sorteermethode<T>{
public:
    void operator()(vector<T> &v) const override;
private:
    void sort(vector<T>&v, int start, int stop) const;
    void sort_cursus(vector<T>&v, int l, int r) const;
};

template<class T>
void QuickSort<T>::sort_cursus(vector<T> &v, int l, int r) const {
    if(l < r-1) {
        T pivot = v[l];
        int i = l, j = r - 1;
        while(v[j] > pivot) j--;
        while( i < j) {
            swap(v[i], v[j]);
            i++;
            while(v[i] < pivot) i++;
            j--;
            while(v[j] > pivot) j--;
        }

        sort_cursus(v, l, j+1);
        sort_cursus(v, j+1, r);
    }
}

template<class T>
void QuickSort<T>::sort(vector<T> &v, int start, int stop) const {
    //no need to sort a list of length 1
    if(stop - start < 2) return;

    int i = start, j = stop;
    //TODO: make this random
    const T pivot = v[i];
    //find first value smaller than pivot
    while(v[--j] > pivot);
    while(i < j) {
        //swap elements at index i & j
        swap(v[i], v[j]);
        //find next value bigger than pivot
        while(v[++i] < pivot);
        //find next value smaller than pivot
        while(v[--j] > pivot);
    }

    sort(v, start,  j + 1);
    sort(v, j + 1, stop);
}

template<class T>
void QuickSort<T>::operator()(vector<T> &v) const {
    sort(v, 0, v.size());
}


#endif //CLIONTEST_QUICKSORT_H
