
#include <iostream>

template <typename T>
class stack {

public:
    stack(): _capacity(1) , _top(-1) {
        _stack = (T*)malloc(_capacity *sizeof(T));

    }

    void push(T item) {
        _top++;
        if (_top >= _capacity) {
            _capacity = _capacity*5;
            _stack = (T*)realloc(_stack, _capacity*sizeof(T));
        }

        _stack[_top] = item;
    }

    void pop() {
        if (_top) _top--;
    }

    T& top() {
        if (_top) {
            return _stack[_top];
        }
        static T null;
        return null;
    }

private:

    T* _stack;
    int _capacity, _top;
};

class MinStack {

public:


private:
    stack<int> _real_stack;
    stack<int> _min_stack;
    int _current_min;
    
public:
    MinStack() { }

    void push(int val) {
        _real_stack.push(val);
        
        if (val <= _current_min) {
            _current_min = val;
            _min_stack.push(val);
        }
    }
   
    void pop() {
        if (_real_stack.top() == _min_stack.top()) {
            _min_stack.pop();
            _current_min =  _min_stack.top();
        }

        _real_stack.pop();
    }
    
    int top() {
        return _real_stack.top();
    }
    
    int getMin() {
        return _current_min;
    }
};

int main()
{

    

   return 0;
}
