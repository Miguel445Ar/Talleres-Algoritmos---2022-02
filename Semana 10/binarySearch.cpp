#include <iostream>
#include <vector>
#include "BinarySearchTree.hpp"


bool binarySearch(std::vector<int>& arr, int i, int f, int val) {
    if(i == f) return arr[i] == val;
    int mid = (i + f) / 2;
    if(arr[mid] == val) return true;
    if(arr[mid] > val) return binarySearch(arr,i,mid,val);
    return binarySearch(arr,mid + 1, f,val);
}

int main() {
    std::vector<int> arr = {1,2,3,4,5,6,7,8};
    std::cout << binarySearch(arr, 0, arr.size() - 1,6) << "\n";
    BinarySearchTree<int> tree(
        [](int value) -> void {
            std::cout << value << " ";
        },
        [](int a, int b) -> bool {
            return a > b;
        }
    );
    tree.insert(5);
    tree.insert(4);
    tree.insert(8);
    tree.insert(2);
    tree.insert(7);
    tree.insert(12);
    tree.insert(10);
    tree.preOrder();
    return 0;
}