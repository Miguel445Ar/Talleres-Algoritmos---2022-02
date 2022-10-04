#include <iostream>
#include <functional>

using std::cout;
using std::cin;
using std::function;


template<class T>
class Node {
public:
    T value;
    Node<T>* next;
    Node<T>* back;
    Node(T value, Node<T>* next = nullptr, Node<T>* back = nullptr): value(value), next(next), back(back){}
};

template<class T>
class CircularDoubleLinkedList{
    Node<T>* head; // Inicia de la lista;
    Node<T>* top; // Fin de la lista;
    size_t size;
    function<void(T)> show;
    Node<T>* aux;
public:
    CircularDoubleLinkedList(function<void(T)> show): show(show) {
        head = top = aux = nullptr;
        size = 0;
    }
    void pushFront(T value){
        Node<T>* newNode = new Node<T>(value);
        if(size == 0){
            head = top = newNode;
            head->back = top;
            top->next = head;
            ++size;
            return;
        }
        top->next = newNode;
        newNode->next = head;
        head->back = newNode;
        newNode->back = top;
        head = newNode;
        ++size;
    }
    void pushBack(T value){
        Node<T>* newNode = new Node<T>(value);
        if(size == 0){
            head = top = newNode;
            head->back = top;
            top->next = head;
            ++size;
            return;
        }
        head->back = newNode;
        top->next = newNode;
        newNode->back = top;
        newNode->next = head;
        top = newNode;
        ++size;
    }
    void popBack(){
        if(size == 0)
            return;
        if(size == 1){
            top->next = nullptr;
            head->back = nullptr;
            delete top;
            top = head = nullptr;
            --size;
            return;
        }
        top->next = nullptr;
        top = top->back;
        head->back = top;
        top->next->back = nullptr;
        delete top->next;
        top->next = head;
        --size;
    }
    void popFront(){
        if(size == 0)
            return;
        if(size == 1){
            top->next = nullptr;
            head->back = nullptr;
            delete top;
            top = head = nullptr;
            --size;
            return;
        }
        head->back = nullptr;
        head = head->next;
        top->next = head;
        head->back->next = nullptr;
        delete head->back;
        head->back = top;
        --size;
    }
    void insertInPos(T value, size_t pos){
        if(pos <= 0){
            pushFront(value);
            return;
        }
        if (pos >= size){
            pushBack(value);
            return;
        }
        aux = head;
        for(size_t i = 0; i<pos-1;++i)
            aux = aux->next;
        Node<T>* newNode = new Node<T>(value);
        newNode->back = aux;
        newNode->next = aux->next;
        aux->next = newNode;
        newNode->next->back = newNode;
        ++size;
    }
    void eraseInPos(int pos){
        if (pos == 0){
            popFront();
            return;
        }
        if (pos == size - 1){
            popBack();
            return;
        }
        if(pos >= size || pos < 0)
            throw "This is not possible";
        aux = head;
        for (size_t i = 0; i < pos - 1; ++i)
            aux = aux->next;
        Node<T>* nodeToErase = aux->next;
        // Preparamos a la lista
        aux->next = nodeToErase->next;
        nodeToErase->next->back = aux;
        // Desconectamos el nodo
        nodeToErase->next = nodeToErase->back = nullptr;
        delete nodeToErase;
        --size;
    }
    void print(){
        aux = head;
        for(size_t i = 0; i<size;++i){
            show(aux->value);
            aux = aux->next;
        }
        cout << "nullptr\n";
    }
};

int main(){
    auto show = [](int a) -> void {
        cout << a << "-->";
    };

    CircularDoubleLinkedList<int>* lista = new CircularDoubleLinkedList<int>(show);
    lista->pushFront(5);
    lista->pushFront(6);
    lista->pushFront(7);
    lista->pushFront(9);
    lista->pushFront(10);
    lista->pushFront(2);
    lista->print();
    lista->pushBack(12);
    lista->print();
    lista->popFront();
    lista->print();
    lista->popBack();
    lista->print();
    lista->insertInPos(4,2);
    lista->print();
    lista->eraseInPos(4);
    lista->print();
    delete lista;
    return 0;
}