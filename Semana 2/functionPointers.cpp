#include <iostream>
#include <vector>
#include <functional>

// Function pointer

template<typename T>
void func(const std::vector<T>& arr) {
    // Do some stuff
    // Tener cuidado porque el editor o IDE no va a poder 
    // identificar los errores de sintaxis del tipo
    T res = 0;
    for(const T& v: arr)
        res += v;
    std::cout << res;
}

void printNumbers(int n, bool (*&compare)(int)) { // Function pointer by reference
    for(size_t i = 0; i < n; ++i){
        if(compare(i)) std::cout << i << " ";
    }
}

bool compare(int n) {
    return n % 2 == 0;
}

int compareValues(const void* a, const void* b) {
    /*int* ap = (int*)a;
    int av = *ap;*/
    int av = *((int*)a);
    int bv = *((int*)b);
    return av - bv;
}

typedef int (*compareQsort)(const void*, const void*);


int main() {
    //void (*ptr)(const std::vector<int>&) = func<int>;
    void  (*ptr)(int, bool (*&)(int)) = printNumbers;
    bool (*comp)(int) = compare;
    ptr(5,comp);
    
    int a[] = {7,6,9,3,2,4,1};
    // Parece un tipo funcion
    compareQsort compQ = compareValues;
    qsort(a,sizeof(a)/sizeof(a[0]),sizeof(int),compQ);
    std::cout << "\n";
    for(size_t i = 0; i < 7; ++i) std::cout << a[i] << " ";

    std::cout << "\n";
    func<int>(std::vector<int>({1,3,4,5}));
    return 0;
}