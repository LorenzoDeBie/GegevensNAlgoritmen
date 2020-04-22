#include "csv.h"
#include "intstring.h"
#include "insertion_sort/insertionsort.h"
#include "merge_sort/mergesort.h"
#include "shell_sort/shellsort.h"
#include "stlsort.h"
#include "quick_sort/quicksort.h"

#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>

#define LENGTH 10000

template <class T>
void measure_sorts(const std::string& csv_filename)
{
    constexpr int ondergrens = 10;
    //bovengrens = 1'000'000 => programma duurt 4min door insertion sort
    constexpr int bovengrens = 100'000;

    CsvData csv_results{csv_filename, '.', ','};

    std::array<std::pair<std::string, std::unique_ptr<Sorteermethode<T>>>, 5> sorters = {
            std::make_pair("STL sort", std::make_unique<STLSort<T>>()),
            std::make_pair("Insertion sort", std::make_unique<InsertionSort<T>>()),
            std::make_pair("Shell sort", std::make_unique<ShellSort<T>>()),
            std::make_pair("Merge sort", std::make_unique<MergeSort<T>>()),
            std::make_pair("Quick sort", std::make_unique<QuickSort<T>>())
    };

    for (const auto& sorter : sorters)
    {

        std::cout << std::endl;
        std::cout << sorter.first << ":" << std::endl;
        std::cout << std::endl;

        sorter.second->meet(ondergrens, bovengrens, std::cout, csv_results);
    }

    std::cout << std::endl << "Writing data to \"" << csv_results.geef_bestandsnaam() << "\" ..." << std::endl;
    csv_results.write_to_file();
    std::cout << "Data written" << std::endl << std::endl;
}

void test_sorts() {
    std::cout << "===== int =====" << std::endl;

    measure_sorts<int>("sort_int");

    std::cout << "===== double =====" << std::endl;

    measure_sorts<double>("sort_double");

    std::cout << "===== Intstring =====" << std::endl;

    measure_sorts<Intstring>("sort_intstring");
}

template<class T>
void test_sort(Sorteermethode<T>& sort) {
    Sortvector<T> data(LENGTH);
	
    //test with random permutation
    data.fill_random();
    std::cout << data << std::endl;
    sort(data);
    std::cout << data << std::endl;
    if(!data.is_sorted()) {
        std::cerr << "Failed to sort random vector" << std::endl;
        exit(1);
    }

    //test with already sorted vector
    data.fill_range();
    std::cout << data << std::endl;
    sort(data);
    std::cout << data << std::endl;
    if(!data.is_sorted()) {
        std::cerr << "Failed to sort sorted vector" << std::endl;
        exit(1);
    }

    //test with reversed vector
    data.fill_reverse();
    std::cout << data << std::endl;
    sort(data);
    std::cout << data << std::endl;
    if(!data.is_sorted()) {
        std::cerr << "Failed to sort reverse sorted vector" << std::endl;
        exit(1);
    }

    std::cout << "OK" << std::endl;
}

void debug_sort(Sorteermethode<int>& sort) {
    Sortvector<int> data{1,5,4,2,3};
    sort(data);
    if(!data.is_sorted()) {
        std::cerr << "Failed to sort vector!" << std::endl;
        exit(1);
    }
    std::cout << "OK" << std::endl;
}

int main()
{

    //test and compare all sorting algorithms with different types
    //test_sorts();

    QuickSort<int> test;
    //test one algorithm with a given type
    test_sort(test);

    //debug one algorithm with ints
    //debug_sort(test);

    return 0;
}
