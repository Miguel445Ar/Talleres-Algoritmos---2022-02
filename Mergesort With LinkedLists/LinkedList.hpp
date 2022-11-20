#ifndef __LINKED_LIST_M__
#define __LINKED_LIST_M__

#include <iostream>
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
    void mergesort() {
        _mergesort(_head,_top);
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
    // O(n)
    Node* _splitList(Node* start, Node* end, Node*& aux) {
        Node* slow = start;
        Node* fast = start;
        aux = nullptr;
        while(fast != end->_next && fast->_next != end->_next) {
            fast = fast->_next->_next;
            aux = slow;
            slow = slow->_next;
        }
        return slow;
    }
    // O(nlogn)
    void _mergesort(Node* start, Node* end) {
        if(start == end) return;
        Node* beforeMiddle = nullptr;
        Node* middle = _splitList(start,end, beforeMiddle);
        if(middle == end)
            middle = beforeMiddle;
        _mergesort(start,middle);
        _mergesort(middle->_next,end);
        _merge(start,middle,end);
    }
    // O(n)
    void _merge(Node* start, Node* middle, Node* end) {
        Node* left = start;
        Node* right = middle->_next;
        Node* subList = nullptr;
        Node* n1 = start;
        Node* n2 = nullptr;
        while(left != middle->_next && right != end->_next) {
            if(left->_value > right->_value) {
                if(subList == nullptr){
                    subList = new Node(right->_value);
                    n2 = subList;
                    right = right->_next;
                    continue;
                }
                subList->_next = new Node(right->_value);
                right = right->_next;
            }else {
                if(subList == nullptr){
                    subList = new Node(left->_value);
                    n2 = subList;
                    left = left->_next;
                    continue;
                }
                subList->_next = new Node(left->_value);
                left = left->_next;
            }
            subList = subList->_next;
        }
        while(left != middle->_next) {
            if(subList == nullptr){
                subList = new Node(left->_value);
                n2 = subList;
                left = left->_next;
                continue;
            }
            subList->_next = new Node(left->_value);
            left = left->_next;
            subList = subList->_next;
        }
        while(right != end->_next) {
            if(subList == nullptr){
                subList = new Node(right->_value);
                n2 = subList;
                right = right->_next;
                continue;
            }
            subList->_next = new Node(right->_value);
            right = right->_next;
            subList = subList->_next;
        }

        // Modificar la lista original
        Node* aux = n2;
        while(aux != nullptr) {
            n1->_value = aux->_value;
            aux = aux->_next;
            n1 = n1->_next;
        }
        while(n2 != nullptr) _popFront(n2);
    }
    void _display(Node* n) {
        Node* aux = n;
        while(aux != nullptr) {
            _show(aux->_value);
            aux = aux->_next;
        }
        std::cout << "\n";
    }
    void _popFront(Node*& n) {
        if(n == nullptr) return;
        Node* aux = n;
        n = n->_next;
        delete aux;
        aux = nullptr;
    }
};

#endif