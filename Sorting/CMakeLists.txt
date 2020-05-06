cmake_minimum_required(VERSION 3.15)
project(Sorting)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(Chrono lib/chrono.cpp)
add_library(Csv lib/csv.cpp)

add_executable(insertion_sort src/insertion_sort/insertionsort)
target_link_libraries(insertion_sort LINK_PUBLIC Chrono)
target_link_libraries(insertion_sort LINK_PUBLIC Csv)

add_executable(merge_sort src/merge_sort/mergesort)
target_link_libraries(insertion_sort LINK_PUBLIC Chrono)
target_link_libraries(insertion_sort LINK_PUBLIC Csv)

add_executable(quick_sort src/quick_sort/quicksort)
target_link_libraries(insertion_sort LINK_PUBLIC Chrono)
target_link_libraries(insertion_sort LINK_PUBLIC Csv)

add_executable(shell_sort src/shell_sort/shellsort)
target_link_libraries(insertion_sort LINK_PUBLIC Chrono)
target_link_libraries(insertion_sort LINK_PUBLIC Csv)

add_executable(heap_sort src/heap_sort/heapsort)
target_link_libraries(insertion_sort LINK_PUBLIC Chrono)
target_link_libraries(insertion_sort LINK_PUBLIC Csv)

add_executable(binary_search src/binary_search/binarysearch)

