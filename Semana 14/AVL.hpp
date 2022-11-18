#ifndef __AVL_HPP__
#define __AVL_HPP__
#include <functional>
#include <stack>
#include <vector>

template<class T>
class AVLTree {
public:
    AVLTree(std::function<void(T)> show, std::function<bool(T,T)> compare, std::function<bool(T,T)> equals): _show(show), _compare(compare), _equals(equals) {
        _root = nullptr;
        _size = 0ll;
    }
    void insert(T value) {
        _insert(_root,value);
    }
    void preOrder() {
        _preOrder(_root);
    }
    // Rightmost element
    T max() {
        Node* aux = _root;
        while(aux->rightChild != nullptr) aux = aux->rightChild;
        return aux->value;
    }
    // Leftmost element
    T min() {
        Node* aux = _root;
        while(aux->leftChild != nullptr) aux = aux->leftChild;
        return aux->value;
    }
    void IterativePreOrder() {
        std::stack<Node*> s;
        s.push(this->_root);
        while(s.empty() == false) {
            // Saco un nodo de la pila
            Node* n = s.top();
            s.pop();
            // Lo muestro en consola
            _show(n->value);
            // Inserto en la pila a sus hijos derecho e izquierdo,
            // en ese orden, en la pila (si es que no son nulos, claro)
            if(n->rightChild)
                s.push(n->rightChild);
            if(n->leftChild)
                s.push(n->leftChild);
        }
    }
    void remove(T value) {
        std::vector<Node*> path;
        Node* parent  = nullptr; //  Parent of n 
        Node* n = _findToRemove(parent,value,path); // actual Nodo
        if(n == nullptr){
            std::cout << "\nThe requested element was not found";
            return;
        }
        while(n != nullptr) {
            // Si es que el nodo n no tiene hijos
            if(n->leftChild == nullptr && n->rightChild == nullptr){
                if(n == _root) {
                    delete n;
                    n = nullptr;
                    _root = nullptr;
                    --_size;
                    break;
                }else if(parent->leftChild == n) parent->leftChild = nullptr;
                else parent->rightChild = nullptr;
                delete n;
                n = nullptr;
                --_size;
                continue;
            }
            if(n->leftChild != nullptr && n->rightChild != nullptr) {
                path.push_back(n);
                Node* lowestParent = nullptr;
                Node* lowestNode = _getLowestElement(n->rightChild,lowestParent,path);
                this->_swap(n->value,lowestNode->value);
                if(lowestNode == lowestParent) parent = n;
                else parent = lowestParent;
                n = lowestNode;
                continue;
            }
            if(n->leftChild != nullptr) {
                if(n == _root) _root = n->leftChild;
                else if(parent->rightChild == n) parent->rightChild = n->leftChild;
                else parent->leftChild = n->leftChild;
                delete n;
                --_size;
                n = nullptr;
                continue;
            }
            if(n->rightChild != nullptr) {
                if(n == _root) _root = n->rightChild;
                else if(parent->leftChild == n) parent->leftChild = n->rightChild;
                else parent->rightChild = n->rightChild;
                delete n;
                --_size;
                n = nullptr;
            } 
        }
        _balanceInRemoving(path);
        path.clear();
    }
private:
    struct Node {
        T value;
        Node* leftChild;
        Node* rightChild;
        int height;
    };
    Node* _root;
    size_t _size;
    std::function<void(T)> _show;
    std::function<bool(T,T)> _compare;
    std::function<bool(T,T)> _equals;
private:
    void _insert(Node*& n, T value) {
        if(n == nullptr) {
            n = new Node{value, nullptr, nullptr, 0};
            ++_size;
            return;
        }
        if(_compare(n->value,value)) _insert(n->leftChild,value);
        else _insert(n->rightChild,value);
        _setHeight(n);
        _balanceSubTree(n);
    }
    void _preOrder(Node* n) {
        // if(n == nullptr) return;
        if(!n) return;
        _show(n->value); // 
        _preOrder(n->leftChild); // Izq
        _preOrder(n->rightChild); // Der
    }
    void _leftRotation(Node*& n){
        Node* rightChild = n->rightChild;
        // El hijo derecho del nodo apunta al hijo izquierdo del hijo derecho del nodo
        n->rightChild = rightChild->leftChild;
        rightChild->leftChild = n;
        _setHeight(n);
        _setHeight(rightChild);
        n = rightChild;
    }
    void _rightRotation(Node*& n) {
        Node* leftChild = n->leftChild;
        n->leftChild = leftChild->rightChild;
        leftChild->rightChild = n;
        _setHeight(n);
        _setHeight(leftChild);
        n = leftChild;
    }
    void _balanceSubTree(Node*& n) {
        int heightDifference = _getHeight(n->leftChild) - _getHeight(n->rightChild);
        if(heightDifference <= -2){// Desbalanceado por la derecha
            if(n->rightChild->rightChild) {
                // Left rotation
                _leftRotation(n);
            }else {
                // Right-Left Rotation
                _rightRotation(n->rightChild);
                _leftRotation(n);
            }

        } else if (heightDifference >= 2) { // Desbalanceado por la izquierda
            if(n->leftChild->leftChild) {
                // RightRotation
                _rightRotation(n);
            }else {
                // Left-Right Rotation
                _leftRotation(n->leftChild);
                _rightRotation(n);
            }
        }
    }
    void _setHeight(Node* n) {
        n->height = std::max(_getHeight(n->leftChild),_getHeight(n->rightChild)) + 1;
    }
    int _getHeight(Node* n) {
        return (n)?n->height: -1;
    }
    Node* _findToRemove(Node*& parent, T value, std::vector<Node*>& path) {
        Node* aux = _root;
        while(aux) {
            if(_equals(aux->value,value))
                break;
            path.push_back(aux);
            parent = aux;
            if(_compare(aux->value, value))
                aux = aux->leftChild;
            else
                aux = aux->rightChild;
        }
        return aux;
    }
    Node* _getLowestElement(Node* start, Node*& parent, std::vector<Node*>& path) {
        Node* aux = start;
        parent = start;
        while(aux->leftChild != nullptr) {
            parent = aux;
            path.push_back(aux);
            aux = aux->leftChild;
        }
        return aux;
    }
    void _swap(T& a, T& b) {
        T c = a;
        a = b;
        b = c;
    }
    void _balanceInRemoving(std::vector<Node*>& path){
        if(path.size() == 1){
            Node* c = path[path.size() - 1];
            _setHeight(c);
            _balanceSubTree(c);
            c = nullptr;
            return;
        }
        int index = path.size() - 1;
        Node* child = nullptr;
        Node* parent = path[index];
        while(true){
            --index;
            if(index < 0)
                break;
            child = parent;
            parent = path[index];
            _setHeight(child);
            if(parent->leftChild == child){
                _balanceSubTree(child);
                parent->leftChild = child;
            }else{
                _balanceSubTree(child);
                parent->rightChild = child;
            }
        }
        child = parent = nullptr;
    }
};
#endif