#include <iostream>
#include "DLL.hpp"
#include "Stack.hpp"

class Vector {
    int value;
public:
    Vector(int value): value(value) {}
    int& operator*(){
        return value;
    }
};

class MinStack {
    Stack<int>* pila;
    Stack<int>* minHistory;
public:
    MinStack() {
        pila = new Stack<int>;
        minHistory = new Stack<int>;
    }
    void push(int value) {
        pila->push(value);
        if(minHistory->size() == 0){
            minHistory->push(value);
            return;
        }
        int top = minHistory->top();
        if(value < top) minHistory->push(value);
        else minHistory->push(top);
    }
    void pop() {
        pila->pop();
        minHistory->pop();
    }
    int top(){
        return pila->top();
    }
    int getMin() {
        return minHistory->top();
    }
};

int main() {
    DoublyLinkedList<int> dll;
    dll.pushBack(5);
    dll.pushBack(6);
    dll.pushBack(7);
    dll.pushBack(8);
    MinStack mini;
    mini.push(-1);
    mini.push(0);
    mini.push(-2);
    mini.push(1);
    std::cout << mini.getMin();
    return 0;
}