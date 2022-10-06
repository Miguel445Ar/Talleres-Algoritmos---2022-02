#include <iostream>
#include <functional>
#include <string>
#include <time.h>
#include "DLL.hpp"

using namespace std;

typedef unsigned int uint;

class Recluta {
public:
    Recluta(uint codigo, string nombre): _codigo(codigo), _nombre(nombre) {
        _sweepedBarracksTimes = _cleanedBathroomsTimes = _paintedWallTimes = 0;
    }
    string ToString() {
        return std::to_string(_codigo) + " " + _nombre;
    }
    // Barrió una barraca de nuevo
    void addNewBarrackSweeped() {
        _sweepedBarracksTimes += 1;
    }
    // Limpió un baño de nuevo
    void addNewcleanedBathrooms() {
        _cleanedBathroomsTimes += 1;
    }
    // Pintó una muralla de nuevo
    void addNewpaintedWall() {
        _paintedWallTimes += 1;
    }
    // Ha terminado su castigo?
    bool hasFinishedPunishment() {
        return _cleanedBathroomsTimes == 500;
    }
private:
    uint _codigo;
    string _nombre;
    uint _sweepedBarracksTimes;
    uint _cleanedBathroomsTimes;
    uint _paintedWallTimes;
};

class Seleccion {
public:
    Seleccion() {
        auto show = [](Recluta r) -> void {
            cout << r.ToString() << "\n";
        };
        _dll = new DoublyLinkedList<Recluta>(show);
        _generarCantidadDeReclutas(1420);
    }
    ~Seleccion() {
        delete _dll;
    }
    void display() {
        _dll->display();
    }
    void selection() {
        int lastPositionSelected = 0;
        while (_dll->isEmpty() == false) {
            uint moves = 1200 + rand()% (12000 - 1200 + 1);
            uint diff = _dll->size() - lastPositionSelected;
            uint pos = (lastPositionSelected == 0)?moves % _dll->size(): (moves - diff) % _dll->size();
            cout << "\nSe ha seleccionado al recluta en la posicion " << pos << "\n\n";
            char opc;
            do {
                cout << "\nIngrese la tarea del recluta: (B, C o P) ";
                cin >> opc;
            }while(!(opc == 'B' || opc == 'C' || opc == 'P'));
            bool hasFinishedPunishment = false;
            switch(opc) {
                case 'B':
                _dll->modifyAt(pos,[&](Recluta& r)-> void {
                    r.addNewBarrackSweeped();
                    cout << "\nEl recluta en la posicion " << pos << " ha barrido una barraca\n";
                });
                break;
                case 'C':
                _dll->modifyAt(pos,[&](Recluta& r)-> void {
                    r.addNewcleanedBathrooms();
                    if(r.hasFinishedPunishment()) hasFinishedPunishment = true;
                    cout << "\nEl recluta en la posicion " << pos << " ha limpiado un baño\n";
                });
                break;
                case 'P':
                _dll->modifyAt(pos,[&](Recluta& r)-> void {
                    r.addNewpaintedWall();
                    cout << "\nEl recluta en la posicion " << pos << " ha pintado una muralla\n";
                });
                break;
            }
            if(hasFinishedPunishment){
                _dll->eraseAt(pos);
                cout << "\nEl recluta en la posicion " << pos << " ha terminado su castigo \n";
                system("pause");
            }
            cout << "\nDesea continuar: (S, N) ";
            cin >> opc;
            if(opc == 'N') break;
            uint cant = 1000 + rand()%(7500 - 1000 + 1);
            _generarCantidadDeReclutas(cant);
            lastPositionSelected = pos;
        }
    }
private:
    DoublyLinkedList<Recluta>* _dll;
private:
    void _generarRecluta() {
        uint codigo = 10000 + rand()% (99999 - 10000 + 1);
        string s = "";
        char A = 'A'; // A -> 65, Z -> 90
        for(size_t i = 0; i <= 10; ++i) {
            char c = 65 + rand()% (90 - 65 + 1);
            s.push_back(c);
        }
        Recluta r = Recluta(codigo,s);
        if(_dll->size() <= 1) _dll->pushBack(r);
        else {
            int pos = 0 + rand() % (_dll->size() - 1);
            _dll->insertAt(r,pos);
        }
    }
    void _generarCantidadDeReclutas(uint cant) {
        for(uint i = 0; i < cant; ++i) _generarRecluta();
    }
};

int main() {
    srand(time(0));
    Seleccion s;
    s.display();
    s.selection();
    return 0;
}