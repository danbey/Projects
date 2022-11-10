#include <iostream>
/*
class Manager 
{
    int m_counter;
public:
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
*/

class Item {};

template<typename T>
class RefCnt;

class CntHolderIFace {};

template<class T>
class CntHolder;

template<class T>
class CntHolder :public CntHolderIFace
{
public:
    CntHolder(T *realPtr): pointee(realPtr){}
    ~CntHolder() {
        delete pointee;
    }

    void addRef() {
        refCounter++;
    };

    void removeRef() {
        if (--refCounter == 0)
        delete this;
    };

    T * pointee;
    int refCounter;

private:

};

template<typename T>
class RefCnt 
{
public:
    RefCnt(T * realPtr): pCntHolder(new CntHolder<T>(realPtr)) {
        init();
    }

    ~RefCnt() {
        pCntHolder->removeRef();
    }

    void init() {
        //Todo check isShare;
        pCntHolder->addRef();
    }

    CntHolder<T> * pCntHolder;

};


class RCItem {
public:
    //Item public functions
    RCItem():realItem(new Item()) {} 

    RefCnt<Item> realItem;
private:
};



int main()
{
  //  RefCounter<int> rf(new int(3));
    {
    //    RefCounter<int> rf2;
        
        //rf2 = rf;
    }

   return 0;
}