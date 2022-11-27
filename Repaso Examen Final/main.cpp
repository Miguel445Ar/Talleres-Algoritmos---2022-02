#include <iostream>
#include <fstream>
#include "BST_AVL.hpp"
#include <string>

using namespace std;

void primeraPregunta() {
    Tree* t = new Tree;
    ifstream arch("input1.txt");
    string line;
    while (getline(arch,line,','))
        t->insert(stoi(line));
    t->IterativePreOrder();
    cout << "\nLa distancia minima es: " << t->encontrarDistanciaMinima();
    arch.close();
    delete t;
}

void segundaPregunta() {
    Tree* t = new Tree;
    ifstream arch("input2.txt");
    string line;
    while (getline(arch,line,','))
        t->insert(stoi(line));
    t->IterativePreOrder();
    cout << "\nEl camino más largo es: " << t->encontrarCaminoMasLargo();
    arch.close();
    delete t;
}

int main() {
    //primeraPregunta();
    segundaPregunta();
    return 0;
}