#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "sorteermethode.h"
#include <iostream>
#include <vector>

/** \class Shellsort
*/
template<class T>
class ShellSort: public Sorteermethode<T> {
    void operator()(std::vector<T> &v) const override {
        int k = floor(v.size() / 2);
        while(k > 0) {
            //do insertion sort here
            for(int i = k; i < v.size(); i++) {
                T help = std::move(v[i]);
                int j = i - k;
                while(j >= 0 && v[j] > help) {
                    v[j + k] = std::move(v[j]);
                    j -= k;
                }
                v[j + k] = std::move(help);
            }
            k = floor(k / 2);
        }
    }
};

#endif

