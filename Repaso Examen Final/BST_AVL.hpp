#ifndef __AVL_HPP__
#define __AVL_HPP__
#include <functional>
#include <stack>
#include <vector>
#include <iostream>

class Tree {
public:
    Tree() {
        _root = nullptr;
        _size = 0ll;
    }
    ~Tree() {
        /*while(_size > 0) {
            int rootValue = _root->value;
            // remove(rootValue);
        }*/
    }
    void insert(int value) {
        _insert(_root,value);
    }
    void IterativePreOrder() {
        std::stack<Node*> s;
        s.push(this->_root);
        while(s.empty() == false) {
            // Saco un nodo de la pila
            Node* n = s.top();
            s.pop();
            // Lo muestro en consola
            std::cout << n->value << " ";
            // Inserto en la pila a sus hijos derecho e izquierdo,
            // en ese orden, en la pila (si es que no son nulos, claro)
            if(n->rightChild)
                s.push(n->rightChild);
            if(n->leftChild)
                s.push(n->leftChild);
        }
    }
    int encontrarDistanciaMinima() {
        int minDistance = INT_MAX;
        Node* prev = nullptr;
        _modifiedInOrder(this->_root,prev,minDistance);
        return minDistance;
    }
    int encontrarCaminoMasLargo() {
        int* results = roadTree(this->_root);
        return std::max(results[0],results[1]);
    }
private:
    struct Node {
        int value;
        Node* leftChild;
        Node* rightChild;
        int height;
    };
    Node* _root;
    size_t _size;
private:
    void _insert(Node*& n, int value) {
        if(n == nullptr) {
            n = new Node{value, nullptr, nullptr, 0};
            ++_size;
            return;
        }
        if(n->value > value) _insert(n->leftChild,value);
        else _insert(n->rightChild,value);
        _setHeight(n);
        //_balanceSubTree(n);
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
    void _modifiedInOrder(Node* n, Node*& prev, int& minDistance) {
        if(n == nullptr) return;
        _modifiedInOrder(n->leftChild,prev,minDistance);
        if(prev != nullptr)
            minDistance = std::min(std::abs(n->value - prev->value), minDistance);
        prev = n;
        _modifiedInOrder(n->rightChild,prev,minDistance);
    }
    int* roadTree(Node* n) {
        if(_isLeafNode(n) == true)
            return new int[2]{0, 0};
        int* leftResults = (n->leftChild == nullptr)? nullptr: roadTree(n->leftChild);
        int* rightResults = (n->rightChild == nullptr)? nullptr : roadTree(n->rightChild);
        if(leftResults != nullptr && rightResults == nullptr) { // Si es que tengo solo a mi hijo izquierdo
            if(_isLeafNode(n->leftChild) == true) return new int[2]{1,1};
            if(_hasOneChild(n->leftChild) == true) return new int[2]{leftResults[1] + 1, leftResults[0] + 1};
            return new int[2]{ leftResults[1] + 1, leftResults[0]};
        }
        if(rightResults != nullptr && leftResults == nullptr) { // Si es que tengo solo a mi hijo derecho
            if(_isLeafNode(n->rightChild) == true) return new int[2]{1,1};
            if(_hasOneChild(n->rightChild) == true) return new int[2]{rightResults[1] + 1, rightResults[0] + 1};
            return new int[2]{rightResults[1] + 1,rightResults[0]};
        }
        // Si es que tengo a mis dos hijos
        if(_isLeafNode(n->leftChild) == true || _hasOneChild(n->leftChild) == true) {
            leftResults[0] += 1;
            leftResults[1] += 1;
        } else leftResults[1] += 1;
        if(_isLeafNode(n->rightChild) == true || _hasOneChild(n->rightChild) == true) {
            rightResults[0] += 1;
            rightResults[1] += 1;
        } else rightResults[1] += 1;
        return new int[2]{leftResults[1] + rightResults[1], std::max(leftResults[0],rightResults[0])};
    }
    bool _isLeafNode(Node* n) { // Si es que es nodo hoja
        return n->leftChild == nullptr && n->rightChild == nullptr;
    }
    bool _hasOneChild(Node* n) { // Si es que tiene un solo hijo
        return (n->leftChild != nullptr && n->rightChild == nullptr) || (n->leftChild == nullptr && n->rightChild != nullptr);
    }
    bool _hasTwoChilds(Node* n) {
        return n->leftChild != nullptr && n->rightChild != nullptr;
    }
};
#endif