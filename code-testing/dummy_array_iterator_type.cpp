#include <iostream> 
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

using VecInt = vector<int>;
using VecChar = vector<char>;

template <typename T,  typename C, size_t const size> 
class dummy_array_iterator_type;

template < typename T , size_t const size>
class dummy_array;

template<typename T, size_t const size>
using dummy_array_iterator = dummy_array_iterator_type<T, dummy_array<T , size>, size>;

template<typename T, size_t const size>
using dummy_array_const_iterator = dummy_array_iterator_type<T, dummy_array<T , size> const, size>;


template < typename T , size_t const size>
class dummy_array
{
private:
    T data[size] = {};
public:
  dummy_array(){}
  ~dummy_array(){}
  
  T const & GetAt(size_t const index) const
  {
    if (index < size) return data[index];

    throw std::out_of_range("index is out of range");
  }

  void SetAt(size_t const index, T const & value)
  {
    if (index < size) data[index] = value;
    else throw std::out_of_range("index is out of range");
  }

  size_t GetSize() const { return size; }
};

template <typename T,  typename C, size_t const size>
class dummy_array_iterator_type
{
private:
  size_t index;
  C& collection;

public:
  dummy_array_iterator_type(C & collection, size_t const index):
                            index(index), collection(collection) {}

  bool operator!= (dummy_array_iterator_type const & other) const
  {
    return index != other.index;
  }

  T const & operator* () const
  {
    return collection.GetAt(index);
  }

  dummy_array_iterator_type const & operator++ ()
  {
    index++;
    return *this;
  }

  
};

template<typename T, size_t const size>
  inline dummy_array_iterator<T, size> begin(dummy_array<T, size> & collection) 
  {
    return dummy_array_iterator<T, size>(collection, 0);
  }

template<typename T, size_t const size>
  inline dummy_array_iterator<T, size> end(dummy_array<T, size> & collection) 
  {
    return dummy_array_iterator<T, size>(collection, collection.GetSize());
  }

int main()
{ 

    dummy_array<int, 5> arr;

    arr.SetAt(0, 11);
    arr.SetAt(1, 22);
    arr.SetAt(2, 33);
    arr.SetAt(3, 44);


    //for (auto &&i : arr) 
    dummy_array_iterator<int, 5> i = begin<int, 5>(arr);
    for (; i != end<int, 5>(arr); ++i)
    {
        cout << *i << endl;
    }
   return 0;

}