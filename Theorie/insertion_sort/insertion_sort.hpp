#include <vector>


template<class T>
void insertion_sort_stable_asc(std::vector<T> &list) {
    //loop over all numbers in the vector
    //we can start at one because a list of one number is already sorted
    for(int i = 1; i < list.size(); i++) {
        //move value to insert into right place into help variable
        T key = std::move(list[i]);
        //we have to check every T which comes before 
        int j = i - 1;
        while(j >= 0 && key < list[j]) {
            //move T which is greater than key one spot
            list[j + 1] = std::move(list[j]);
            j--;
        }
        //now the spot for key is at j+1
        list[j+1] = std::move(key);
    }
}

template<class T>
void insertion_sort_unstable_asc(std::vector<T> &list) {
    //loop over all numbers in the vector
    //we can start at one because a list of one number is already sorted
    for(int i = 1; i < list.size(); i++) {
        //move value to insert into right place into help variable
        T key = std::move(list[i]);
        //we have to check every T which comes before 
        int j = i - 1;
        while(j >= 0 && key <= list[j]) {
            //move T which is greater than key one spot
            list[j + 1] = std::move(list[j]);
            j--;
        }
        //now the spot for key is at j+1
        list[j+1] = std::move(key);
    }
}

template<class T>
void insertion_sort_stable_desc(std::vector<T> &list) {
    //loop over all numbers in the vector
    //we can start at one because a list of one number is already sorted
    for(int i = 1; i < list.size(); i++) {
        //move value to insert into right place into help variable
        T key = std::move(list[i]);
        //we have to check every T which comes before 
        int j = i - 1;
        while(j >= 0 && key > list[j]) {
            //move T which is greater than key one spot
            list[j + 1] = std::move(list[j]);
            j--;
        }
        //now the spot for key is at j+1
        list[j+1] = std::move(key);
    }
}