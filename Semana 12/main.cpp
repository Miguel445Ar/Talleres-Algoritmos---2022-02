#include <iostream>
#include <vector>
#include "AVL.hpp"

int main() {
    AVLTree<int> avl(
        [](int value) -> void {
            std::cout << value << " ";
        },
        [](int a, int b) -> bool {
            return a > b;
        }
    );
    
    std::vector<int> numbers = {1,2,3,4,5,6};
    for(int number: numbers)
        avl.insert(number);
    avl.preOrder();
    std::cout << "\n";
    avl.IterativePreOrder();
    return 0; 
}