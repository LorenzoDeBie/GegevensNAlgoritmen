#include "insertionsort.h"

#define LENGTH 10000

int main()
{
    InsertionSort<int> sorter;
    //test one algorithm with a given type
    sorter.test(LENGTH);
    sorter.debug();
    return 0;
}
