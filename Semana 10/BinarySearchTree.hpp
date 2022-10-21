#ifndef __BINARY_SEARCH_TREE__
#define __BINARY_SEARCH_TREE__

template<class T>
class BinarySearchTree {
    using DisplayFunction = void (*)(T);
    using ComparisonCriteria = bool (*)(T,T);
public:
    BinarySearchTree(DisplayFunction show, ComparisonCriteria compare): _show(show), _compare(compare) {
        _root = nullptr;
        _size = 0ll;
    }
    void insert(T value) {
        _insert(_root,value);
    }
    void preOrder() {
        _preOrder(_root);
    }
private:
    struct Node {
        T value;
        Node* leftChild;
        Node* rightChild;
    };
    Node* _root;
    size_t _size;
    DisplayFunction _show;
    ComparisonCriteria _compare;
private:
    void _insert(Node*& n, T value) {
        if(n == nullptr) {
            n = new Node{value, nullptr, nullptr};
            return;
        }
        if(_compare(n->value,value)) _insert(n->leftChild,value);
        else _insert(n->rightChild,value);
    }
    void _preOrder(Node* n) {
        // if(n == nullptr) return;
        if(!n) return;
        _show(n->value); // N
        _preOrder(n->leftChild); // Izq
        _preOrder(n->rightChild); // Der
    }
};

#endif