#ifndef __DOUBLY_LINKED_LIST__
#define __DOUBLY_LINKED_LIST__

#include <functional>
#include <cstdint>

template<class T>
class DoublyLinkedList {
public:
    DoublyLinkedList(std::function<void(T)> show): _show(show) {
        this->_start = this->_end = nullptr;
        this->_size = 0;
    }
    void pushBack(T value) {
        Node* newNode = new Node(value);
        if(_size == 0) {
            this->_start = this->_end = newNode;
            _size = 1;
            return;
        }
        this->_end->next = newNode;
        newNode->back = this->_end;
        this->_end = this->_end->next;
        ++_size;
    }
    void insertAt(T value, int pos) {
        if(pos < 0 || pos > _size) throw "Invalid position >:V";
        if(pos == 0) { pushFront(value); return; }
        if(pos == _size) { pushBack(value); return; }
        Node* aux = this->_start;
        Node* newNode = new Node(value);
        for(int i = 0; i < pos - 1; ++i) aux = aux->next;
        // Enlazar el nodo a insertar con el nodo en la posiciÃ³n pos (aux->next)
        newNode->next = aux->next;
        aux->next->back = newNode;
        // Enlazamos el nodo a insertar con el nodo anterior al de la posiciÃ³n pos (aux)
        aux->next = newNode;
        newNode->back = aux;

        ++this->_size;
    }
    void pushFront(T value) {
        Node* newNode = new Node(value);
        if(_size == 0) {
            this->_start = this->_end = newNode;
            this->_size = 1;
            return;
        }
        newNode->next = this->_start;
        this->_start->back = newNode;
        this->_start = this->_start->back;
        ++this->_size;
    }
    void display() {
        Node* aux = this->_start;
        while(aux) {
            _show(aux->value);
            aux = aux->next;
        }
    }
    void popFront() {

    }
    void popBack() {

    }
    void eraseAt(int pos) {

    }
    // Iterador del inicio
    // Iterador del final

    // Buble Sort
    void bubleSort(std::function<bool(T,T)> compare) {
        Node* aux = this->_start;
        if(aux == nullptr) throw "Cannot sort an empty list";
        while(aux != this->_end) {
            if(compare(aux->value,aux->next->value)){
                this->_swap(aux->value,aux->next->value);
                if(aux != this->_start)
                    aux = aux->back;
                continue;
            }
            aux = aux->next;
        }
    }

    // Selection Sort
private:
    struct Node {
        T value;
        Node* next;
        Node* back;
        Node(T value): value(value), next(nullptr), back(nullptr) {}
    };
    Node* _start;
    Node* _end;
    size_t _size;
    std::function<void(T)> _show;
private:
    void _swap(T& a, T& b) {
        T c = a;
        a = b;
        b = c;
    }
public:
    class Iterator {
    public:
        Iterator(Node* node): _node(node) {}
        // Sobrecarga ++
        void operator++(){
            if(this->_node == nullptr) throw "Cannot move a null node";
            this->_node = this->_node->next;
        }
        // Sobrecarga -- (opcional)
        // Sobrecarga *
        T operator*() {
            if(this->_node == nullptr) throw "Cannot return value from null pointer";
            return this->_node->value;
        }
        // Sobrecarga !=
        bool operator!=(Iterator other) {
            return this->_node != other._node;
        }
    private:
        // 1. Nodo guía
        Node* _node;
    };
public:
    Iterator begin() {
        return Iterator(this->_start);
    }
    Iterator end() {
        return Iterator(nullptr);
    }
};

#endif