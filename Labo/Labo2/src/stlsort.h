#pragma once

#include "sorteermethode.h"
#include <algorithm>
#include <vector>

/** \class STLSort
*/
template<class T>
class STLSort : public Sorteermethode<T>{
    void operator()(std::vector<T>& v) const override {
        std::sort(v.begin(), v.end());
    }
};


