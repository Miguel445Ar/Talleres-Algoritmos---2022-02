#include <iostream>
#include "Vector.hpp"
#include "LinkedList.hpp"

class Functor {
    int value;
public:
    Functor(int value): value(value) {}
    const int operator()(int param) const {
        return value + param;
    }
};

struct Node {
    Node(int value = 0): value(value), next(nullptr) {}
    int value;
    Node* next;
};

int getMiddleElement(Node* head) {
    Node* fast = head;
    Node* slow = head;
    while(fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return (slow)? slow->value: -1000000;
}

int getKthFromThEndOfTheList(Node* n, int k) {
    static Node* head = n;
    static bool hasAnswer = false;
    if(k <= 0) return -100000;
    if(!n) return k - 1;
    int res = getKthFromThEndOfTheList(n->next, k);
    if(hasAnswer) return res;
    if(res == 0) {
        hasAnswer = true;
        return n->value;
    }
    if(n == head) return -100000;
    return res - 1;
}

int main() {
    /*Functor f(5);
    std::cout << f(5);*/
    /*
    // Reverse a Sinlgy Linked List
    auto show = [](int value) -> void { std::cout << value << "-->"; };
    LinkedList<int> list(show);
    list.pushBack(5);
    list.pushBack(8);
    list.pushBack(9);
    list.pushBack(1);
    list.pushBack(4);
    list.display();
    std::cout << "\n";
    try {
        list.reverseList();
        list.display();
    }catch (const char* msg) {
        std::cout << msg << "\n";
    }
    */
    Node* head = new Node(5);
    head->next = new Node(7);
    head->next->next = new Node(8);
    head->next->next->next = new Node(1);
    head->next->next->next->next = new Node(10);
    std::cout << getMiddleElement(head) << "\n";
    std::cout << getKthFromThEndOfTheList(head,1) << "\n";
    return 0;
}