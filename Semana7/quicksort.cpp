#include <iostream>
#include <functional>

template<class T>
class SortingAlgorithms {
public:
    SortingAlgorithms(size_t n): _size(n){
        this->_arr = new T[n];
    }
    SortingAlgorithms(size_t n, T* arr): _size(n), _arr(arr) {}
    void quickSort(){
        _quickSort(0, _size - 1);
    }
    void display(std::function<void(T)> show) {
        for(int i = 0; i < _size; ++i)
            show(_arr[i]);
        std::cout << "\n";
    }
private:
    T* _arr;
    size_t _size;
private:
    void _quickSelect(int i, int& p, int f) {
        while(i < f) {
            while(_arr[i] < _arr[p]) ++i;
            while(_arr[f] > _arr[p]) --f;
            std::swap(_arr[i],_arr[f]);
            if(p == i) {
                p = f;
                ++i;
            }else if (p == f) {
                p = i;
                --f;
            }else{
                ++i; --f;
            }
        }
    }
    void _quickSort(int i, int f) {
        if(i >= f) return;
        int p = (i + f) / 2;
        _quickSelect(i,p,f);
        _quickSort(i,p - 1);
        _quickSort(p + 1, f);
    }
};

int main() {
    int arr[] {4,6,7,9,1,3,16,9};
    size_t n = sizeof(arr)/sizeof(arr[0]);
    SortingAlgorithms<int> s(n,arr);
    s.display([](int value) -> void {
        std::cout << value << " ";
    });
    s.quickSort();
    s.display([](int value) -> void {
        std::cout << value << " ";
    });
    return 0;
}