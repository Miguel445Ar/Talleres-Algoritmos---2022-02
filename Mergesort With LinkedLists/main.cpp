#include <iostream>
#include <ctime>
#include "LinkedList.hpp"

using std::cout;
using std::cin;

int main() {
    srand(time(0));
    LinkedList<int> l([](int value) -> void { cout << value << "-->";});
    for(int  i = 0; i < 10; ++i) {
        int number = 1 + rand()%(1000);
        l.pushBack(number);
    }
    /*
    l.pushBack(5);
    l.pushBack(6);
    l.pushBack(1);
    l.pushBack(4);
    l.pushBack(3);
    */
    l.display();
    std::cout << "\n";
    l.mergesort();
    l.display();
    return 0;
}