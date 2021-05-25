#include <iostream>


class Manager 
{
public:
    int m_counter;
    Manager():m_counter(1){}

    void inc() {
        m_counter++;
    }

    void dec(){
        m_counter--;
    }

    int get_counter() {
        return m_counter;
    }
};


template<typename T>
class RefCounter
{
    T * ptr;
    Manager *mng;

public:

    RefCounter(){}

    RefCounter(T *obj):ptr(obj) {
        mng = new Manager();
    }
    

    ~RefCounter() {
        mng->dec();
        if (mng->get_counter()==0) {
            delete ptr;
            delete mng;
        }
    }
   
    RefCounter & operator=(RefCounter &other) {
        ptr = other.ptr;
        mng = other.mng;
        mng->inc();

        return *this;
    }
};


int main()
{
    RefCounter<int> rf(new int(3));
    {
        RefCounter<int> rf2;
        
        rf2 = rf;
    }


    

   return 0;
}