#include <vector>
#include <stdlib.h>

template<class T>
void selection_sort_asc(vector<T>& lijst) {
    for(int i = lijst.size() - 1; i > 0; i--) {
        int imax = i;
        for(int j = 0; j < i; j++)
            if(lijst[j] > lijst[imax]) imax = j;
        std::swap(lijst[i], lijst[imax]);
    }
}

template<class T>
void selection_sort_desc(vector<T>& lijst) {
    for(int i = lijst.size() - 1; i > 0; i--) {
        int imax = i;
        for(int j = 0; j < i; j++)
            if(lijst[j] < lijst[imax]) imax = j;
        std::swap(lijst[i], lijst[imax]);
    }
}