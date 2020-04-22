#pragma once
/**
 \class Sortvector
 \brief class for sortable vectors
 
 Includes some helper functions to compare sorting solutions
*/
#include <iostream>
    using std::istream;
    using std::ostream;
    using std::move;
    using std::swap;
#include <iomanip>   // for setw
#include <cstdlib>   // for rand - Pay Attention!! 
#include <vector>
    using std::vector;
#include <random>
#include <functional>
    using std::function;
#include <cassert>

template<class T>
class Sortvector:public vector<T>{
  public:

    /**
     * \fn Constructor: argument = size of vector
     * 
     * vector will be filled with n different T's in a random permuation
     * */
    Sortvector(int);
    using vector<T>::vector;

    
    //no generated copy constructor, copy assignment, move constructor or move assignment
    Sortvector(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(Sortvector<T>&& v) = delete;
    Sortvector(Sortvector<T>&& v) = delete;

    /// \fn fill_rane \brief fills vector with T(0) ... T(size() - 1) in that order
    void fill_range();
    void reverse();
    void fill_reverse();
    void shuffle();
    void fill_random_unique();
    void fill_random();

    /**
     * \fn is_sorted checks if vector is sorted based on comparer
     *
     * default is ascending
     *
     * \param comparer function to check if two elements are in the right order
     *
     * \returns bool indicating if vector is sorted
     * */
    bool is_sorted(function<bool (const T& t1, const T& t2)> comparer = [](const T &t1, const T &t2) -> int {
        if(t1 > t2) return false;
        return true;
    }) const;
    
    /// \fn is_range controleert of *this eruit ziet als het resultaat van vul_range(), d.w.z.
    /// dat, voor alle i, (*this)[i]==T(i);
    /** \fn is_range
     *  \brief checks if vector is equal to result of fill_range
     *  
     *  for all i : (*this)[i]==T(i)
     * */
    bool is_range() const;

    friend ostream& operator<<(ostream& os, const Sortvector<T>& s){
        s.write(os);
        return os;
    }

  private: 
    void write(ostream & os)const;
    
};

/***************************** IMPLEMENTATION **************************************/

//constructor
template <class T>
Sortvector<T>::Sortvector(int grootte) : std::vector<T>(grootte)
{
    if (grootte > 0)
    {
        fill_random();
    }
}

template <class T>
void Sortvector<T>::fill_range() {
    for(std::size_t i = 0; i < this->size(); i++) {
        (*this)[i] = T(i);
    }
}

template <class T>
void Sortvector<T>::fill_reverse() {
    for(std::size_t i = 0; i < this->size(); i++) {
        (*this)[i] = T(this->size() - i - 1);
    }
}

template <class T>
void Sortvector<T>::fill_random()
{
    if (this->empty())
    {
        return;
    }

    std::random_device rd;
    std::mt19937 eng{rd()};
    const int max_value = (this->size() - 1);
    assert(max_value < std::numeric_limits<int>::max());
    std::uniform_int_distribution<int> dist{0, static_cast<int>(max_value)};

    std::generate(this->begin(), this->end(), [&dist, &rd]() { return dist(rd); });
}

template <class T>
void Sortvector<T>::write(ostream & os)const{
    for(auto&& t : *this){
        os<<t<<" ";
    }
    os<<"\n";
}

template<class T>
bool Sortvector<T>::is_sorted(function<bool (const T &t1, const T &t2)> comparer) const {
    for(std::size_t i = 0; i < this->size() - 1; i++) {
        if(!comparer((*this)[i], (*this)[i+1])) return false;
    }
    return true;
}

template<class T>
bool Sortvector<T>::is_range() const {
    for(std::size_t i = 0; i < this->size(); i++) {
        if((*this)[i] != T(i)) return false;
    }
    return true;
}

template<class T>
void Sortvector<T>::reverse() {
    for(std::size_t i = 0; i < this->size() / 2; i++) {
        std::swap((*this)[i], (*this)[this->size() - 1 - i]);
    }
}

