#include <iostream>


template<class A, class B>
auto sum(A a, B b) -> decltype(a + b){
    return a + b;
}


auto main() -> int {
    return 0;
}