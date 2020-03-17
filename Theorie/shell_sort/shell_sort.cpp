#include <vector>
#include <math.h>

using namespace std;

template<class T>
void shell_sort_asc(vector<T>& lijst) {
    int k = floor(lijst.size() / 2);
    while(k > 0) {
        //do insertion sort here
        for(int i = k; i < lijst.size(); i++) {
            T help = std::move(lijst[i]);
            int j = i - k;
            while(j >= 0 && lijst[j] > help) {
                lijst[j + k] = std::move(lijst[j]);
                j -= k;
            }
            lijst[j + k] = std::move(help);
        }
        k = floor(k / 2);
    }
}

template<class T>
void shell_sort_desc(vector<T>& lijst) {
    int k = floor(lijst.size() / 2);
    while(k > 0) {
        for(int i = k; i < lijst.size(); i++) {
            T help = std::move(lijst[i]);
            int j = i - k;
            while(j >= 0 && lijst[j] < help) {
                lijst[j + k] = std::move(lijst[j]);
                j -= k;
            }
            lijst[j + k] = std::move(help);
        }
        k = floor(k / 2);
    }
}