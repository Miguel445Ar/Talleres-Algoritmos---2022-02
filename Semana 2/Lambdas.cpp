#include <iostream>
#include <functional>
#include <vector>
#include <array>
#include <any>



int main() {
    std::array<int,5> arr = {6,7};
    int i = 2;
    

    std::any anyType;
    anyType = 7;
    anyType = "jgdjg";
    anyType = new char{'c'};

    /*std::function<bool(int,int)> comp = [&arr,&i](int a, int b) -> bool {
        arr[i] = a + b;
        ++i;
        return a > b;
    };*/

    auto comp = [&arr,&i](int a, int b) -> bool {
        arr[i] = a + b;
        ++i;
        return a > b;
    };

    std::cout << ((comp(5,6))?"5 es mayor": "6 es mayor");
    std::cout << ((comp(5,6))?"5 es mayor": "6 es mayor");
    std::cout << ((comp(5,6))?"5 es mayor": "6 es mayor");
    std::cout << "\nArreglo: ";

    for(int& v: arr) {
        std::cout << v << " ";
    }
    int res = [](int a, int b) -> int { return a + b; }(10,20);
    std::cout << "\n" << res << "\n";

    return 0;
}