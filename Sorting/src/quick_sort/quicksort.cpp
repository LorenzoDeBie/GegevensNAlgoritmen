#include "quicksort.h"

#define LENGTH 10000

int main()
{
    QuickSort<int> sorter;
    //test one algorithm with a given type
    sorter.test(LENGTH);
    sorter.debug();
    return 0;
}
