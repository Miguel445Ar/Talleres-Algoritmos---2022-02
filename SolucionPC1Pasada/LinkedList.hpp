#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <functional>

template<class T>
class LinkedList {
public:
    LinkedList() {
        this->_head = this->_top = nullptr;
        this->_size = 0;
    }
    ~LinkedList() {
        while(this->_size) popFront();
    }
    // void operator=(const LinkedList& other) = delete;
    void pushBack(T value) {
        Node* newNode = new Node(value);
        if(this->_size == 0) {
            this->_head = this->_top = newNode;
            ++this->_size;
            return;
        }
        this->_top->_next = newNode;
        this->_top = newNode;
        ++this->_size;
    }
    void popFront() {
        if(this->_size == 1) {
            delete this->_head;
            this->_head = this->_top = nullptr;
            this->_size = 0ll;
            return;
        }
        Node* toDelete = this->_head;
        this->_head = this->_head->_next;
        toDelete->_next = nullptr;
        delete toDelete;
        --this->_size;
    }
    void display(std::function<void(T)> printNodeValue) {
        Node* aux = this->_head;
        while(aux != nullptr) {
            printNodeValue(aux->_value);
            aux = aux->_next;
        }
    }
    void exchangeByTwo() {
        Node* first = this->_head;
        Node* second = this->_head->_next;
        while(true) {
            if(second == nullptr) return;
            if(second->_next == nullptr) return;
            T val = first->_value;
            first->_value = second->_value;
            second->_value = val;
            first = first->_next->_next;
            second = second->_next->_next;
        }
    }
private:
    class Node {
    public:
        Node() = delete;
        Node(T value): _value(value), _next(nullptr) {}
    private:
        T _value;
        Node* _next;
        friend class LinkedList;
    };
    Node* _head; // inicio de la lista
    Node* _top; // final de la lista
    size_t _size; // cantidad de elementos
};

#endif