#include <iostream>

template <typename T>
class DVector
{
    T *data;
    size_t m_size;
    size_t m_idx;

public:
    DVector(size_t db_size): m_size(db_size), m_idx(0) 
    {
        data = new T[db_size]; 
    }

    ~DVector()
    {
        delete []data;
    }

    T& operator[](int idx)
    {
        
        return data[idx];
    }

    class Iterator
    {
        T *m_current;

    public:
        Iterator(T *pcurrent): m_current(pcurrent) {}

        T& operator*()
        {
            return *m_current;
        }

        Iterator& operator++()
        {
            m_current++;
            return *this;
        }

        bool operator !=(const Iterator &other)
        {
            return !(other.m_current == m_current);
        }

    };

    Iterator begin()
    {
        return  DVector::Iterator(&data[0]);
    }

    Iterator end()
    {
        return  DVector::Iterator(&data[m_size]);
    }

    void push_back(const T &item)
    {
        if (m_idx < m_size) {
            data[m_idx++]  = item;
        }
    }
    
};


int main()
{

    DVector<int> vec(10);

    vec[5] = 10;


    std::cout << vec[5] << std::endl;
   return 0;
}