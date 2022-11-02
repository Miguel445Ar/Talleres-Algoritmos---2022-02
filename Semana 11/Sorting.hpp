#ifndef __SORTING_HPP__
#define __SORTING_HPP__

#include <vector>

template<class T>
class SortingAlgorithms {
public:
    static void swap(T& a, T& b) {
        T c = a;
        a = b;
        b = c;
    }
    static void quickSelect(std::vector<T>& arr,bool(*compare1)(T,T), bool(*compare2)(T,T), int i, int& p, int f) {
        while(i < f) {
            //      a  <  b 
            while(compare1(arr[i],arr[p])) ++i;
            //     a > b 
            while(compare2(arr[f],arr[p])) --f;
            swap(arr[i],arr[f]);
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
    static void quickSort(std::vector<T>& arr, bool(*compare1)(T,T), bool(*compare2)(T,T), int i, int f) {
        if(i >= f) return;
        int p = (i + f) / 2;
        quickSelect(arr,compare1,compare2,i,p,f);
        quickSort(arr,compare1,compare2,i,p - 1);
        quickSort(arr,compare1,compare2,p + 1, f);
    }
};
#endif