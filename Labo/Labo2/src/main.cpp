#include "csv.h"
#include "intstring.h"
#include "insertionsort.h"
#include "mergesort.h"
#include "shellsort.h"
#include "stlsort.h"

#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>

template <class T>
void measure_sorts(const std::string& csv_filename)
{
    constexpr int ondergrens = 10;
    constexpr int bovengrens = 100'000;

    CsvData csv_results{csv_filename, '.', ','};

    std::array<std::pair<std::string, std::unique_ptr<Sorteermethode<T>>>, 4> sorters = {
            std::make_pair("STL sort", std::make_unique<STLSort<T>>()),
            std::make_pair("Insertion sort", std::make_unique<InsertionSort<T>>()),
            std::make_pair("Shell sort", std::make_unique<ShellSort<T>>()),
            std::make_pair("Merge sort", std::make_unique<MergeSort<T>>())
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

int main()
{
    std::cout << "===== int =====" << std::endl;

    measure_sorts<int>("sort_int");

    std::cout << "===== double =====" << std::endl;

    measure_sorts<double>("sort_double");

    std::cout << "===== Intstring =====" << std::endl;

    measure_sorts<Intstring>("sort_intstring");

    return 0;
}
