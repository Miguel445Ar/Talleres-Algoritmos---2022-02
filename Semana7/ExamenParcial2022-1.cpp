#include <iostream>
#include <functional>
#include <string>
#include <time.h>
#include "DLL.hpp"

using namespace std;

typedef unsigned int uint;

class Recluta {
public:
    Recluta(uint codigo, string nombre): _codigo(codigo), _nombre(nombre) {}
    string ToString() {
        return std::to_string(_codigo) + " " + _nombre;
    }
private:
    uint _codigo;
    string _nombre;
};

class Seleccion {
public:
    Seleccion() {
        auto show = [](Recluta r) -> void {
            cout << r.ToString() << "\n";
        };
        _dll = new DoublyLinkedList<Recluta>(show);
    }
    ~Seleccion() {
        delete _dll;
    }
private:
    DoublyLinkedList<Recluta>* _dll;
private:
    void _generarRecluta() {
        uint codigo = 10000 + rand()% (99999 - 10000 + 1);
        string s = "";
        char A = 'A'; // A -> 65, Z -> 90
        for(size_t i = 0; i <= 50; ++i) {

        }
        Recluta r = Recluta(codigo,s);
        _dll->pushBack(r);
    }
};

int main() {
    srand(time(0));
    return 0;
}