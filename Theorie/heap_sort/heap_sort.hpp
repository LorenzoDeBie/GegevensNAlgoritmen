#include <vector>
#include <stdlib.h>

template<class T>
void create_max_heap(std::vector<T> &list, int size) {
    for(int i = size / 2 - 1; i >= 0; i--) {
        int current = i;
        //set this to current for entering while loop
        int biggestChild = current;
        //keep switching with biggest child as long as we aren't a leaf && we did the swap
        while(current < size / 2 && current == biggestChild) {
            //first child is biggest by default
            biggestChild = current * 2 + 1;
            //if second child exists && it is bigger then first
            if (current * 2 + 2 < size && list[current * 2 + 2] > list[current * 2 + 1])
                biggestChild = current * 2 + 2;
            //do the swap if a child is bigger
            if(list[biggestChild] > list[current]) {
                std::swap(list[biggestChild], list[current]);
                current = biggestChild;
            }
        }
    }
}

template<class T>
void swap_root_element(std::vector<T> &list, int size, T n) {
    //heap condition cannot be broken if the new element is bigger than the now biggest element
    if(n >= list[0]) {
        std::swap(list[0], n);
        return;
    }
    list[0] = n;
    int current = 0;
    //set this to current for entering while loop
    int biggestChild = current;
    //keep switching with biggest child as long as we aren't a leaf && we did the swap
    while(current < size / 2 && current == biggestChild) {
        //first child is biggest by default
        biggestChild = current * 2 + 1;
        //if second child exists && it is bigger then first
        if (current * 2 + 2 < size && list[current * 2 + 2] > list[current * 2 + 1])
            biggestChild = current * 2 + 2;
        //do the swap if a child is bigger
        if(list[biggestChild] > list[current]) {
            std::swap(list[biggestChild], list[current]);
            current = biggestChild;
        }
    }
}

template<class T>
void heap_sort_asc(std::vector<T> &list) {
    create_max_heap(list, list.size());
    //only to size - 1 because last element will be smalles & in right place
    for(int i = 0; i < list.size() - 1; i++) {
        int size = list.size() - i; //decrement the size of list each time
        int n = list[size - 1]; //leaf to put in root
        list[size - 1] = list[0]; // put biggest element to the end of the list
        swap_root_element(list, size - 1, n); //swap the root element && restore heap condition
    }
}