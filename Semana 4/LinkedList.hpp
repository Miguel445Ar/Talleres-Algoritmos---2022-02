#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <functional>

template<class T>
class LinkedList {
public:
    LinkedList(std::function<void(T)> show): _show(show) {
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
    void display() {
        Node* aux = this->_head;
        while(aux != nullptr) {
            _show(aux->_value);
            aux = aux->_next;
        }
    }
    void reverseList() {
        if(_size == 0) throw "You cannot reverse an empty linked list";
        Node* aux = _top;
        _top = _reverse(_head);
        _head = aux;
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
    std::function<void(T)> _show;
private:
    Node* _reverse(Node* n) {
        if(n->_next == nullptr) return n;
        Node* r = _reverse(n->_next);
        r->_next = n;
        n->_next = nullptr;
        return n;
    }
};

#endif