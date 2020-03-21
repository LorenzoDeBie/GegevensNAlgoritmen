#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <utility>
#include <cstdlib>

#define SEED 0

//Sorting algorithms
#include "../insertion_sort/insertion_sort.hpp"
#include "../shell_sort/shell_sort.hpp"
#include "../selection_sort/selection_sort.hpp"
#include "../heap_sort/heap_sort.hpp"

using namespace std;

vector<int> create_test_vector(int size = 10, int min = 0, int max = 100) {
    vector<int> result;
    result.reserve(size);
    for(int i = 0; i < size; i++) {
        result.push_back(rand() % max + min);
    }
    return result;
}

template<class T>
void print_vector(const vector<T> &list) {
    for(T item: list) {
        cout << item << " ";
    }
    cout << endl;
}

void test_sorts() {
    vector<pair<string, function<void (vector<int>&)>>> sorters;
    sorters.push_back(make_pair("insertion_sort_asc", insertion_sort_stable_asc<int>));
    sorters.push_back(make_pair("insertion_sort_desc", insertion_sort_stable_desc<int>));
    sorters.push_back(make_pair("shell_sort_asc", shell_sort_asc<int>));
    sorters.push_back(make_pair("shell_sort_desc", shell_sort_desc<int>));
    sorters.push_back(make_pair("selection_sort_asc", selection_sort_asc<int>));
    sorters.push_back(make_pair("selection_sort_desc", selection_sort_desc<int>));
    sorters.push_back(make_pair("heap_sort_asc", heap_sort_asc<int>));

    for(auto &sorter : sorters) {
        vector<int> lijst = create_test_vector();
        cout << "voor sorteren: ";
        for(int n : lijst) {
            cout << n << " ";
        }
        cout << endl << "nu sorteren met " << sorter.first << endl;
        sorter.second(lijst);
        cout << "na sorteren: ";
        for(int n : lijst) {
            cout << n << " ";
        }
        cout << endl;
    }
}

int main(int argc, char** argv) {
    srand(SEED);
    test_sorts();
    return 0;
}