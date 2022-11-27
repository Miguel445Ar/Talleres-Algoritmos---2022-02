#include <iostream>
#include <functional>
#include <stack>
#include <vector>
#include <string>
#include <ctime>

using std::cout;
using std::cin;
using std::function;
using std::stack;
using std::pair;
using std::vector;
using std::max;
using std::string;
using std::srand;
using std::time;


template<class T>
class Tree {
    class Node
    {
    public:
        T value;
        Node* left;
        Node* right;
        Node* parent;
        struct XD {
            int value;
            XD(int value): value(value) {}
        };
        Node(T value, Node* parent) : value(value), left(nullptr), right(nullptr), parent(parent) {}
        ~Node() {
            left = right = nullptr;
        }
        Node() = default;
        static XD get(int value){
            return XD(value);
        }
        // Kill Self Method for erase a BST or AVL
        void killSelf() {
            if (left)
                left->killSelf();
            if (right)
                right->killSelf();
            parent = nullptr;
            delete this;
        }
    };
    Node* root;
    size_t size;
    function<void(T)> show;
    function<bool(T, T)> comp;
    function<bool(T, T)> equals;
    function<T(void)> defaultValue;
public:
    Tree(function<void(T)> show, function<bool(T, T)> comp, function<bool(T, T)> equals, function<T(void)> defaultValue) : show(show), comp(comp), equals(equals), defaultValue(defaultValue) {
        root = nullptr;
        size = 0;
    }
    ~Tree() {
        // Method for rasing a BST or AVL
        root->killSelf();
    }
    void IterativeInsertion(T value) {
        if (!root) {
            root = new Node(value, nullptr);
            ++size;
            return;
        }
        Node* current = root;
        while (true) {
            if (comp(value, current->value))
                if (!current->left) { current->left = new Node(value, current); ++size; break; }
                else current = current->left;
            else
                if (!current->right) { current->right = new Node(value, current); ++size; break; }
                else current = current->right;
        }
    }
    void IterativePrintPreOrder() {
        if (!root)
            return;
        stack<Node*>* pila = new stack<Node*>;
        pila->push(root);
        while (pila->size() > 0) {
            Node* n = pila->top();
            pila->pop();
            show(n->value);
            if (n->right)
                pila->push(n->right);
            if (n->left)
                pila->push(n->left);
        }
        delete pila;
    }
    void IterativePrintInOrder() {
        Node* current = root;
        stack<Node*>* pila = new stack<Node*>;
        while (current != nullptr || pila->empty() == false) {
            while (current != nullptr) {
                pila->push(current);
                current = current->left;
            }
            current = pila->top();
            pila->pop();
            show(current->value);
            current = current->right;
        }
        delete pila;
    }
    void printWithRecursion() {
        _print(root);
    }
    void postOrderRecursive() {
        _postOrder(root);
    }
    void IterativePostOrder() {
        stack<pair<Node*, int>*>* s = new stack<pair<Node*, int>*>;
        Node* current = root;
        while (current || !s->empty()) {
            while (current != nullptr) {
                s->push(new pair<Node*, int>(current, 1));
                current = current->left;
            }
            if (s->top()->second == 2) {
                cout << s->top()->first->value << " ";
                s->pop();
                continue;
            }
            s->top()->second = 2;
            current = s->top()->first->right;
        }
        delete s;
    }
    T lowestElement() {
        Node* p = nullptr;
        return getLowestElement(root, p)->value;
    }
    void IterativeErasing(T value) {
        Node* nodeToErase = getNode(value);
        if (nodeToErase)
            eraseNode(nodeToErase);
        else cout << "\nThis value doesn't exists in the tree\n";
    }
    T KthElement(size_t k) {
        if (k > size || k == 0)
            return T();
        stack<Node*>* s = new stack<Node*>;
        Node* current = root;
        size_t counter = 0;
        while (current != nullptr || s->empty() == false) {
            while (current) {
                s->push(current);
                current = current->left;
            }
            ++counter;
            current = s->top();
            s->pop();
            if (counter == k) {
                delete s;
                return current->value;
            }
            current = current->right;
        }
        return T();
    }
    T kthElementRecursive(size_t k) {
        if (k > size || k == 0)
            return T();
        T value = T();
        size_t pos = 0;
        bool stop = false;
        _kth(root, pos, k, value, stop);
        return value;
    }
    int height() {
        return _height(root);
    }
    int HeightWithoutRecursion() {
        if (!root)
            return -1;
        stack<Node*>* s = new stack<Node*>;
        vector<int> s2;
        Node* current = root;
        while (current != nullptr || s->empty() == false) {
            while (s2.size() >= 2) {
                if (s2[0] != -2 && s2[1] != -2 && s2[2] == -2) {
                    s2[2] = max(s2[0], s2[1]) + 1;
                    s2.erase(s2.begin());
                    s2.erase(s2.begin());
                }
                else break;
            }
            while (current != nullptr) {
                s->push(current);
                s2.insert(s2.begin(), -2);
                current = current->left;
            }
            current = s->top();
            if (current->left == nullptr && current->right == nullptr) {
                s2[0] = 0;
            }
            else if (current->left == nullptr || current->right == nullptr) {
                s2.insert(s2.begin(), -1);
            }
            s->pop();
            current = current->right;
        }
        while (s2.size() >= 2) {
            if (s2[0] != -2 && s2[1] != -2 && s2[2] == -2) {
                s2[2] = max(s2[0], s2[1]) + 1;
                s2.erase(s2.begin());
                s2.erase(s2.begin());
            }
            else break;
        }
        int h = s2[0];
        s2.clear();
        delete s;
        return s2[0];
    }
    T SuccesorValue(T value) {
        Node* current = getNode(value); // log(n)
        if (!current) return defaultValue();
        Node* p = nullptr;
        Node* heighest = getHighestElement(root); // log(n)
        // If has a right child
        if (current->right != nullptr)
            return getLowestElement(current->right, p)->value;
        if (heighest == current)
            return defaultValue();
        // If has a left child or if has no childs
        if (current == current->parent->left)
            return current->parent->value;
        else {
            current = current->parent;
            while (current != current->parent->left) // log (n)
                current = current->parent;
            return current->parent->value;
        }
    }
    T PredeccesorValue(T value) {
        Node* current = getNode(value); // log(n)
        if (!current) return defaultValue();
        Node* p = nullptr;
        Node* smallest = getLowestElement(root, p); // log(n)
        // If has a left child
        if (current->left != nullptr)
            return getHighestElement(current->left)->value;
        if (smallest == current)
            return defaultValue();
        // If has a right child or if has no childs
        if (current == current->parent->right)
            return current->parent->value;
        else {
            current = current->parent;
            while (current != current->parent->right) // log(n)
                current = current->parent;
            return current->parent->value;
        }
    }
private:
    void _print(Node* n) {
        if (!n)
            return;
        show(n->value);
        _print(n->left);
        _print(n->right);
    }
    void _postOrder(Node* n) {
        if (!n)
            return;
        _postOrder(n->left);
        _postOrder(n->right);
        show(n->value);
    }
    void eraseNode(Node* e) {
        Node* n = e;
        while (n) {
            if (n->left == nullptr && n->right == nullptr) {
                if (n == root) {
                    delete root;
                    root = nullptr;
                    --size;
                }
                else if (n->parent->left == n) {
                    Node* nodeToErase = n;
                    n->parent->left = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                else if (n->parent->right == n) {
                    Node* nodeToErase = n;
                    n->parent->right = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                n = nullptr;
            }
            else if (n->left == nullptr && n->right != nullptr) {
                if (n == root) {
                    Node* nodeToErase = root;
                    n->right->parent = nullptr;
                    root = n->right;
                    nodeToErase->right = nullptr;
                    delete nodeToErase;
                    --size;
                }
                else if (n->parent->left == n) {
                    n->parent->left = n->right;
                    n->right->parent = n->parent;
                    n->right = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                else if (n->parent->right == n) {
                    n->parent->right = n->right;
                    n->right->parent = n->parent;
                    n->right = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                n = nullptr;
            }
            else if (n->left != nullptr && n->right == nullptr) {
                if (n == root) {
                    Node* nodeToErase = root;
                    n->left->parent = nullptr;
                    root = n->left;
                    nodeToErase->left = nullptr;
                    delete nodeToErase;
                    --size;
                }
                else if (n->parent->left == n) {
                    n->parent->left = n->left;
                    n->left->parent = n->parent;
                    n->left = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                else if (n->parent->right == n) {
                    n->parent->right = n->left;
                    n->left->parent = n->parent;
                    n->left = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                n = nullptr;
            }
            else {
                Node* aux = getLowestElement(n->right);
                n->value = aux->value;
                n = aux;
            }
        }
    }
public:
    void remove(T value) {
        Node* parent = nullptr;
        Node* current = root;
        while (current) {
            if (equals(value, current->value))
                break;
            parent = current;
            if (comp(value, current->value))
                current = current->left;
            else
                current = current->right;
        }
        if (!current)
            cout << "\nThe element doesn't exists\n";
        while (current) {
            if (current->left == nullptr && current->right == nullptr) {
                if (root == current) {
                    delete current;
                    root = nullptr;
                    --size;
                    break;
                }
                else if (parent->left == current)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
                delete current;
                current = nullptr;
                --size;
            }
            else if (current->left != nullptr && current->right != nullptr) {
                Node* lowestParent = nullptr;
                Node* lowest = getLowestElement(current->right, lowestParent);
                current->value = lowest->value;
                if (lowestParent == lowest)
                    parent = current;
                else
                    parent = lowestParent;
                current = lowest;
            }
            else if (current->left != nullptr) {
                if (root == current)
                    root = root->left;
                else if (parent->left == current)
                    parent->left = current->left;
                else
                    parent->right = current->left;
                delete current;
                current = nullptr;
                --size;
            }
            else if (current->right != nullptr) {
                if (root == current)
                    root = root->right;
                else if (parent->left == current)
                    parent->left = current->right;
                else
                    parent->right = current->right;
                delete current;
                current = nullptr;
                --size;
            }
        }
    }
private:
    int _height(Node* node) {
        if (!node)
            return -1;
        return max(_height(node->left), _height(node->right)) + 1;
    }
    void _kth(Node* n, size_t& pos, const size_t& k, T& value, bool& stop) {
        if (!n || stop == true)
            return;
        _kth(n->left, pos, k, value, stop);
        ++pos;
        if (pos == k) {
            value = n->value;
            stop = true;
            return;
        }
        _kth(n->right, pos, k, value, stop);
    }
    Node* getLowestElement(Node* start, Node*& parent) {
        Node* current = start;
        parent = start;
        while (current->left != nullptr) {
            parent = current;
            current = current->left;
        }
        return current;
    }
    Node* getHighestElement(Node* start) {
        Node* current = start;
        while (current->right != nullptr)
            current = current->right;
        return current;
    }
    Node* getNode(T value) {
        Node* current = root;
        while (true) {
            if (equals(current->value, value))
                break;
            if (comp(value, current->value))
                if (!current->left) { return nullptr; }
                else current = current->left;
            else
                if (!current->right) { return nullptr; }
                else current = current->right;

        }
        return current;
    }
public:
    class PreOrder {
    public:
        PreOrder() = delete;
        PreOrder(const Tree<T>::PreOrder&) = delete;
        PreOrder(Tree<T>::PreOrder&&) = delete;
        /*PreOrder() {} */
        class Iterator {
            Node* node;
            stack<Node*>* s;
        public:
            Iterator(Node* node): node(node) {
                s = new stack<Node*>;
                if (this->node)
                    s->push(this->node);
            }
            ~Iterator(){
                node = nullptr;
                delete s;
            }
            void operator++() {
                if (!node)
                    throw("Cannot move with an null pointer");
                s->pop();
                if (this->node->right)
                    s->push(this->node->right);
                if (this->node->left)
                    s->push(this->node->left);
                this->node = (s->size() > 0)? s->top(): nullptr;
            }
            T operator*() {
                if (!node)
                    throw("Cannot return a value of an empty pointer");
                return this->node->value;
            }
            bool operator!=(Iterator a) {
                return s->size() != a.s->size();
            }
        };
    private:
        static Iterator begin(Node* node){
            return Iterator(node);
        }
        static Iterator end(){
            return Iterator(nullptr);
        }
        friend class Tree;
    };
    class InOrder {
    public:
        InOrder() = delete;
        InOrder(const Tree<T>::InOrder&) = delete;
        InOrder(Tree<T>::InOrder&&) = delete;
        class Iterator {
            Node* node;
            Node* current;
            stack<Node*>* s;
        public:
            Iterator(Node* node): node(node), current(node) {
                s = new stack<Node*>;
                if(this->node){
                    while(this->node){
                        s->push(this->node);
                        this->current = this->node;
                        this->node = this->node->left;
                    }
                }
            }
            ~Iterator(){
                node = current = nullptr;
                delete s;
            }
            void operator++(){
                if(!current)
                    throw("Cannot move with an null pointer");
                node = s->top();
                s->pop();
                if (s->empty() == true && node->right == nullptr){
                    this->current = nullptr; return;
                }
                if(node->right){
                    node = node->right;
                    while(this->node){
                        s->push(this->node);
                        this->current = this->node;
                        this->node = this->node->left;
                    }
                    return;
                }
                current = s->top();
                node = node->right;
            }
            T operator*(){
                if(!current)
                    throw("Cannot return a value of a empty pointer");
                return current->value;
            }
            bool operator!=(Iterator a){
                return current != a.current;
            }
        };
    private:
        static Iterator begin(Node* node){
            // No podemos acceder a los atributos o métodos propios (this) 
            // por ser estático pero si podemos instanciar clases embebidas 
            // porque la clase embebida no es un atributo es una definición que
            // pertenece a la clase padre pero que puede ser accedida globalmente
            // si es que es pública
            return Iterator(node);
        }
        static Iterator end(){
            return Iterator(nullptr);
        }
        friend class Tree;
    };
    class PostOrder {
    public:
        PostOrder() = delete;
        PostOrder(const Tree<T>::PostOrder&) = delete;
        PostOrder(Tree<T>::PostOrder&&) = delete;
        class Iterator {
            typedef pair<Node*,int> par;
            Node* node;
            Node* current;
            stack<par*>* s;
        public:
            Iterator(Node* node): node(node), current(current) {
                s = new stack<par*>;
                if(current){
                    while(this->node){
                        while(this->node){
                            s->push(new par(this->node,1));
                            this->current = this->node;
                            this->node = this->node->left;
                        }
                        this->node = this->current;
                        this->node = this->node->right;
                        s->top()->second = 2;
                    }
                }
            }
            ~Iterator(){
                node = current = nullptr;
                delete s;
            }
            void operator++(){
                if(!current)
                    throw("Cannot move with an null pointer");
                if(s->top()->second == 2){
                    s->pop();
                    if (s->empty() == true && node == nullptr){
                        this->current = nullptr; return;
                    }
                    current = s->top()->first;
                    if(s->top()->second == 2) return;
                }
                node = s->top()->first;
                node = node->right;
                if(!node){
                    s->top()->second = 2;
                    return;
                }
                s->top()->second = 2;
                while(this->node){
                    while(this->node){
                        s->push(new par(this->node,1));
                        this->current = this->node;
                        this->node = this->node->left;
                    }
                    this->node = this->current;
                    this->node = this->node->right;
                    s->top()->second = 2;
                }
            }
            T operator*(){
                if(!current)
                    throw("Cannot return a value of a empty pointer");
                return current->value;
            }
            bool operator!=(Iterator a) {
                return current != a.current;
            }
        };
    private:
        static Iterator begin(Node* node) {
            return Iterator(node);
        }
        static Iterator end(){
            return Iterator(nullptr);
        }
        friend class Tree;
    };

    typename PreOrder::Iterator PreOrderBegin() {
        return PreOrder::begin(root);
    }
    typename PreOrder::Iterator PreOrderEnd() {
        return PreOrder::end();
    }

    typename InOrder::Iterator InOrderBegin(){
        return InOrder::begin(root);
    }
    // Yo como se que Iterator es un tipo y no una función estática, el compilador se confunde
    // Por eso necesito typename

    // Del mismo modo no puedo hacer InOrder::Iterator(nullptr);
    // Ya que InOrder hereda el tipo asociado (T) de Tree<T>, por eso puedo retornar Node* o node
    // (o PreOrder si es q no hubieramos eliminado sus constructores) 
    // porque Node hereda el tipo de Tree<T>
    // Sin embargo, Iterator hereda el tipo de InOrder, pero InOrder no tiene un tipo Propio porque
    // el que tiene es heredado. Entonces, Iterator no tiene tipo, por eso si invocas al constructor
    // el compilador se confunde y no sabe que tipo T tiene tu iterador

    typename InOrder::Iterator InOrderEnd(){
        return InOrder::end();
    }

    typename PostOrder::Iterator PostOrderBegin(){
        return PostOrder::begin(root);
    }
    typename PostOrder::Iterator PostOrderEnd(){
        return PostOrder::end();
    }

    /*
    typename Node::XD Root(){
        return Node::get(int{10});
    }
    
    Node R(){
        return *(this->root);
    }*/
    /*PreOrder p(){
        return PreOrder();
    }*/
};

class Bloque {
    string name;
public:
    Bloque(size_t n = 0) {
        for (size_t i = 0; i < n; ++i) {
            // inicio + rand()% + (fin - inicio + 1)
            size_t opc = 1 + rand() % 2;
            if (opc == 1) name.push_back(char(65 + rand() % +26));
            else name.push_back(char(97 + rand() % +26));
        }
    }
    Bloque(string name) : name(name) {}
    string getName() {
        return this->name;
    }
};

struct Nota
{
    int nota;
    char* nombre = nullptr;
    // An operator overloading for a class can be declared inside the class
    bool operator<(Nota dos) {
        return nota < dos.nota;
    }
};

// An operator overloading for a class can be declared out the class
/*bool operator<(Nota uno, Nota dos) {
    return uno.nota < dos.nota;
}*/


int main() {
    Nota n1, n2;
    n1.nota = 16;
    n2.nota = 20;
    if (n1 < n2)
        cout << "\nEs menor \n";
    auto defaultValue = []() -> int {
        return -1;
    };
    Tree<int>* tree = new Tree<int>([](int a)->void {cout << a << " "; }, [](int a, int b) -> bool {return a < b; }, [](int a, int b) -> bool {return a == b; }, defaultValue);
    tree->IterativeInsertion(9);
    tree->IterativeInsertion(5);
    tree->IterativeInsertion(12);
    tree->IterativeInsertion(3);
    tree->IterativeInsertion(7);
    tree->IterativeInsertion(2);
    tree->IterativeInsertion(4);
    tree->IterativeInsertion(8);
    tree->IterativeInsertion(10);
    tree->IterativeInsertion(14);

    tree->IterativePrintPreOrder();
    cout << "\n";
    tree->IterativePrintInOrder();
    //cout << "\n";
    //tree->printWithRecursion();
    cout << "\nPost Order (with recursion)\n";
    tree->postOrderRecursive();
    cout << "\nPost Order (without recursion)\n";
    tree->IterativePostOrder();
    cout << "\nThe succesor of 4 is " << tree->SuccesorValue(4) << "\n";
    cout << "\nthe predeccesor of 7 is " << tree->PredeccesorValue(7) << "\n";
    tree->remove(5);
    cout << "\n";
    tree->IterativePrintInOrder();
    cout << "\n";
    tree->IterativePrintPreOrder();
    cout << "\nIterative PostOrder\n";
    tree->IterativePostOrder();

    /*srand(time(0));
    auto show = [](Bloque a) -> void { cout << a.getName() << " ";};
    auto comp = [](Bloque a, Bloque b) -> bool { return a.getName() < b.getName(); };
    auto equals = [](Bloque a, Bloque b) -> bool { return a.getName() == b.getName();};
    auto defaultValue = []() -> Bloque { return Bloque(); };

    Tree<Bloque>* tree = new Tree<Bloque>(show,comp,equals,defaultValue);
    tree->IterativeInsertion(Bloque(8));
    tree->IterativeInsertion(Bloque(8));
    tree->IterativeInsertion(Bloque(8));
    tree->IterativeInsertion(Bloque(8));
    tree->IterativeInsertion(Bloque(8));
    tree->IterativePrintPreOrder();*/
    cout << "\nPreOrder with Iterators\n";
    Tree<int>::PreOrder::Iterator it = tree->PreOrderBegin();
    for(it; it != tree->PreOrderEnd(); ++it)
        cout << "\n" << *it << "\n";
    cout << "\nInOrder with Iterators\n";
    Tree<int>::InOrder::Iterator it2 = tree->InOrderBegin();
    for(it2; it2 != tree->InOrderEnd(); ++it2)
        cout << "\n" << *it2 << "\n";
    cout << "\nPostOrder with Iterators\n";
    Tree<int>::PostOrder::Iterator it3 = tree->PostOrderBegin();
    for(it3; it3 != tree->PostOrderEnd(); ++it3)
        cout << "\n" << *it3 << "\n";
    //cout << "\nRoot " << tree->Root().value << "\n";
    delete tree;
    return 0;
}
