#ifndef __STACK_HPP__
#define __STACK_HPP__


template<typename T>
class Stack {
    typedef long long ll;
public:
    Stack() {
        this->_head = this->_top = nullptr;
        this->_size = 0ll;
    }
    ~Stack() {
        while(_size) pop();
    }
    size_t size() { return _size; }
    T top() {
        if(this->_top == nullptr) throw "Cannot return value from null pointer";
        return this->_top->value;
    }
    void pop() {
        if(_size == 0) throw "Stack is empty >:v";
        if(_size == 1) {
            delete this->_head;
            this->_head = this->_top = nullptr;
            _size = 0;
            return;
        }
        this->_top = this->_top->back;
        this->_top->next->back = nullptr;
        this->_top->next->next = nullptr;
        delete this->_top->next;
        --_size;
        this->_top->next = nullptr;
    }
    void push(T value) {
        Node* newNode = new Node(value);
        if(!_size) {
            this->_head = this->_top = newNode;
            _size = 1ll;
            return;
        }
        this->_top->next = newNode;
        newNode->back = this->_top;
        this->_top = newNode;
        ++_size;
    }
private:
    struct Node {
        T value;
        Node* next;
        Node* back;
        Node() = delete;
        Node(T value): value(value), next(nullptr), back(nullptr) {}
    };
    Node* _head;
    Node* _top;
    size_t _size;
};


#endif