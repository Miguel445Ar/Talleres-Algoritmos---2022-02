#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "LinkedList.hpp"

// formula pro B-) i * m + j;

template<class T>
class Matrix2d {
public:
    Matrix2d(short rows, short columns): _rows(rows), _columns(columns) {
       this->_matrix.resize(rows * columns);
    }
    void insert(T value, short row, short col)  {
        short pos = row * _columns + col;
        if(this->_isInvalidPosition(pos))
            throw "Invalid index :(";
        this->_matrix[pos] = value;
    }
    T getValue(short row, short col) {
        short pos = row * _columns + col;
        if(this->_isInvalidPosition(pos))
            throw "Invalid index :(";
        return this->_matrix[pos];
    }
    void display() {
        short cont = -1;
        for(size_t i = 0; i < _rows; ++i) {
            for(size_t j = 0; j < _columns; ++j) {
                ++cont;
                std::cout << this->_matrix[cont] << " ";
            }
            std::cout << "\n";
        }
    }
private:
    std::vector<T> _matrix;
    //uint16_t _rows; // filas
    //uint16_t _columns; // columnas
    short _rows;
    short _columns;
private:
    bool _isInvalidPosition(short pos) {
        return pos < 0 || pos >= this->_matrix.size();
    }
};

class Solution {
public:
    Solution() {
        _list = new LinkedList<int>;
        _show = [](int value) -> void { std::cout << value << "-->";};
        _readInput();
    }
    ~Solution() {
        delete _list;
    }
    void exchange() {
        this->_list->exchangeByTwo();
        this->_saveInFile();
    }
    void displayList() {
        std::cout << "\n";
        this->_list->display(_show);
    }
private:
    LinkedList<int>* _list;
    std::function<void(int)> _show;
private:
    void _readInput() {
        std::ifstream arch("input.txt");
        std::string s;
        while(arch >> s) {
            int number = std::stoi(s);
            this->_list->pushBack(number);
        }
        arch.close();
    }
    void _saveInFile() {
        std::ofstream arch("input.txt");
        this->_list->display(
            [&arch](int value) -> void {
                arch << value << " ";
            }
        );
        arch.close();
    }
};

int main() {
    /*Matrix2d<short> matrix(5,3);
    matrix.insert(5,1,2);
    matrix.display();*/
    Solution sol;
    sol.displayList();
    sol.exchange();
    sol.displayList();
    return 0;
}