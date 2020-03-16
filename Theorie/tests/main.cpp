#include <iostream>
#include <memory>
#include <functional>
#include <map>
#include <vector>
#include <utility>
#include <cstdlib>

#define SEED 0

//Sorting algorithms
#include "../insertion_sort/insertion_sort.cpp"

using namespace std;

vector<int> create_test_vector(int size = 10, int min = 0, int max = 100) {
    vector<int> result;
    result.reserve(size);
    for(int i = 0; i < size; i++) {
        result.push_back(rand() % max + min);
    }
    return result;
}

void test_sorts() {
    map<string, function<void (vector<int>&)>> sorters;
    sorters.insert(make_pair("insertion_sort_asc", insertion_sort_stable_asc<int>));
    sorters.insert(make_pair("insertion_sort_desc", insertion_sort_stable_desc<int>));

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