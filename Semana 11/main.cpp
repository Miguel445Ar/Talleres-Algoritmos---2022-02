#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>
#include <sstream>
#include <ctime>
#include "BinarySearchTree.hpp"

using namespace std;

enum Sexo {
    HOMBRE,
    MUJER
};

class Registro {
    int id;
    int edad;
    string educacion;
    string statusMarital;
    string ocupacion;
    string parentesco;
    string sexo;
    int ingresos;
    int egresos;
    size_t horasDeTrabajoALaSemana;
    string paisNatal;
public:
    Registro(int id, int edad, string educacion,
        string statusMatiral, string ocupacion, string parentesco,
        string sexo, int ingresos, int egresos,
        size_t horasDeTrabajoALaSemana, string paisNatal)
        :id(id), edad(edad), educacion(educacion),
        statusMarital(statusMarital), ocupacion(ocupacion),
        parentesco(parentesco), sexo(sexo), ingresos(ingresos),
        egresos(egresos), horasDeTrabajoALaSemana(horasDeTrabajoALaSemana),
        paisNatal(paisNatal) {}
    int getId() {
        return this->id;
    }
    friend ostream& operator<<(ostream& os, Registro r) {
        os << r.id << " " << r.edad << " " << r.educacion << " " << r.ingresos;
        return os;
    }
};

class BaseDeDatos {
    ifstream lectura;
    ofstream escritura;
    BinarySearchTree<Registro>* arbol;
    vector<Registro> datos;
public:
    BaseDeDatos() {
        arbol = new BinarySearchTree<Registro>(
            [](Registro value) -> void {
                cout << value << "\n";
            },
            [](Registro a, Registro b) -> bool {
                return a.getId() < b.getId();
            }
        );
        // 1. leer los datos y guardamos en un arreglo
        // 2. Desordenamos con Fisher yates shuffle
        // 3. Insertar en el BST
    }
    void leerLosDatos() {
        lectura.open("ingresos.csv");
        string line;
        while(getline(lectura,line,'\n')) {
            stringstream s(line);
            string aux;

            int id;
            int edad;
            string educacion;
            string statusMarital;
            string ocupacion;
            string parentesco;
            string sexo;
            int ingresos;
            int egresos;
            size_t horasDeTrabajoALaSemana;
            string paisNatal;

            getline(s,aux,',');
            id = stoi(aux);
            getline(s,aux,',');
            edad = stoi(aux);
            getline(s,aux,',');
            educacion = aux;
            getline(s,aux,',');
            statusMarital = aux;
            getline(s,aux,',');
            ocupacion = aux;
            getline(s,aux,',');
            sexo = aux;
            getline(s,aux,',');
            ingresos = stoi(aux);
            getline(s,aux,',');
            egresos = stoi(aux);
            getline(s,aux,',');
            horasDeTrabajoALaSemana = stoi(aux);
            getline(s,aux,',');
            paisNatal = aux;

            datos.push_back(Registro(id,edad,educacion,statusMarital,ocupacion,parentesco,sexo,ingresos,egresos,horasDeTrabajoALaSemana,paisNatal));
        }
        shuffle();
        guardarEnBST();
    }
    int buscarIdsEnUnRango(int low, int high) {
        int count = 0;
        this->arbol->roadTree(
            [&](Registro r) -> void {
                if(r.getId() >= low && r.getId() <= high) ++count;
            }
        );
        return count;
    }
    void addToList() {
        list<Registro> lista;
        this->arbol->roadTree(
            [&lista](Registro r) -> void {
                lista.push_back(r);
            }
        );
        for(Registro& r: lista) {
            std::cout << r << "\n";
        }
    }
private:
    void guardarEnBST() {
        for(Registro& r: datos)
            this->arbol->insert(r);
    }
    void shuffle() {
        for(int i = datos.size() - 1; i > 0 ; --i) {
            // [0,i> => 0 + rand() % ( (i - 1) - 0 + 1);
            int pos = 0 + rand()% i;
            this->swap(datos[i],datos[pos]);
        }
    }
    void swap(Registro& a, Registro& b) {
        Registro c = a;
        a = b;
        b = c;
    }
};

int main() {
    return 0;
}