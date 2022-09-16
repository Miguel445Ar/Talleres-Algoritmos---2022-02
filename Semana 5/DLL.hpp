#ifndef __DOUBLY_LINKED_LIST__
#define __DOUBLY_LINKED_LIST__

#include "Interfaces.hpp"

template<typename T>
class DoublyLinkedList {
    typedef long long ll;
public:
    DoublyLinkedList() {
        this->_head = this->_top = nullptr;
        this->_size = 0ll;
    }
    ~DoublyLinkedList() {
        
    }
    size_t size() { return _size; }
    void popBack() {

    }
    void popFront() {

    }
    void pushBack(T value) {
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
    void pushFront(T value) {
        Node* newNode = new Node(value);
        if(!_size) {
            this->_head = this->_top = newNode;
            _size = 1ll;
            return;
        }
        this->_head->back = newNode;
        newNode->next = this->_head;
        this->_head = newNode;
    }
    void eraseAt(ll pos) {
        if(pos < 0 || pos >= _size)
            throw "Invalid Position";
    }
    void insertAt(T value, ll pos) {
        if(pos < 0 || pos > _size)
            throw "Invalid Position";
        if(pos == 0) pushFront(value);
        else if (pos == _size) pushBack(value);
        else {
            
        }
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
public:
    class ForwardIterator: public GIterator<T> {
    public:
        ForwardIterator(Node* ptr) {
            this->_ptr = ptr;
        }
        ~ForwardIterator() {
            this->_ptr = nullptr;
        }
        T& operator*() override {
            if(!this->_ptr) throw "Cannot return value from null iterator";
            return this->_ptr->value;
        }
        void operator++() override {
            if(!this->_ptr) throw "Cannot move a null iterator";
            this->_ptr = this->_ptr->next;
        }
        void operator--() override{
            if(!this->_ptr) throw "Cannot move a null iterator";
            this->_ptr = this->_ptr->back;
        }
        bool operator!=(void* it) override {
            ForwardIterator fit = *(ForwardIterator*)it;
            return this->_ptr != fit._ptr;
        }
    private:
        Node* _ptr;
    };
    class ReversedIterator: public GIterator<T> {
    public:
        ReversedIterator(Node* ptr) {
            this->_ptr = ptr;
        }
        T& operator*() override {
            if(!this->_ptr) throw "Cannot return value from null iterator";
            return this->_ptr->value;
        }
        void operator++() override {
            if(!this->_ptr) throw "Cannot move a null iterator";
            this->_ptr = this->_ptr->back;
        }
        void operator--() override{
            if(!this->_ptr) throw "Cannot move a null iterator";
            this->_ptr = this->_ptr->next;
        }
        bool operator!=(void* it) override {
            ReversedIterator rit = *(ReversedIterator*)it;
            return this->_ptr != rit._ptr;
        }
    private:
        Node* _ptr;
    };
    ForwardIterator begin() {
        return ForwardIterator(this->_head);
    }
    ForwardIterator end() {
        return ForwardIterator(nullptr);
    }
    ReversedIterator rbegin() {
        return ReversedIterator(this->_top);
    }
    ReversedIterator rend() {
        return ReversedIterator(nullptr);
    }
};

#endif