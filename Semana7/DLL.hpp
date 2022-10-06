#ifndef __DLL_HPP__
#define __DLL_HPP__

#include <cstdint>
#include <functional>

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
        // Enlazar el nodo a insertar con el nodo en la posición pos (aux->next)
        newNode->next = aux->next;
        aux->next->back = newNode;
        // Enlazamos el nodo a insertar con el nodo anterior al de la posición pos (aux)
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
    void popBack() {
        if(this->_size == 0) throw "Cannot erase in empty list";
        if(this->_size == 1) {
            delete _start;
            _start = _end = nullptr;
            _size = 0;
            return;
        }
        _end = _end->back;
        _end->next->back = nullptr;
        delete _end->next;
        _end->next = nullptr;
        --_size;
    }
    void popFront() {
        if(this->_size == 0) throw "Cannot erase in empty list";
        if(this->_size == 1) {
            delete _start;
            _start = _end = nullptr;
            _size = 0;
            return;
        }
        _start = _start->next;
        _start->back->next = nullptr;
        delete _start->back;
        _start->back = nullptr;
        --_size;
    }
    void eraseAt(int pos) {
        if(pos < 0 || pos >= _size) throw "Cannot erase out of bounds";
        if(pos == 0) {
            popFront();
            return;
        }
        if(pos == _size - 1) {
            popBack();
            return;
        }
        Node* aux = _start;
        for(unsigned int i = 0; i < pos - 1; ++i) aux = aux->next;
        Node* toErase = aux->next;

        aux->next = aux->next->next;
        aux->next->back = aux->next->back->back;

        toErase->next = toErase->back = nullptr;

        delete toErase;
        --_size;
    }
    void modifyAt(int pos, std::function<void(T&)> modify) {
        if(pos < 0 || pos >= _size) throw "Oye >:V";
        Node* aux = _start;
        for(size_t i = 0; i < pos; ++i) aux = aux->next;
        modify(aux->value);
    }
    bool isEmpty() {
        return this->_size == 0;
    }
    size_t size() {
        return this->_size;
    }
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
};


#endif