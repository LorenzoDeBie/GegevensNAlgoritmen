#include "shellsort.h"
#define LENGTH 10000

int main()
{
    ShellSort<int> sorter;
    //test one algorithm with a given type
    sorter.test(LENGTH);
    sorter.debug();
    return 0;
}
