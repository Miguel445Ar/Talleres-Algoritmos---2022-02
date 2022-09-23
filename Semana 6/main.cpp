#include <iostream>
#include "Vector.hpp"
#include "DLL.hpp"
#include <string>
#include <functional>
#include <list>

typedef unsigned int uint;

class Persona {
public:
    Persona(std::string dni, std::string name, uint age)
        :_dni(dni), _name(name), _age(age) {}
    ~Persona() {
        //std::cout << "Destroying\n";
    }
    std::string toString() {
        return this->_dni + ", " + this->_name + ", " + std::to_string(this->_age);
    }
    // Sobrecargando el cout :O
    /*friend std::ostream& operator<<(std::ostream& os, Persona p) {
        os << p._dni << ", " << p._name << ", " << p._age;
        return os;
    }*/
    // a > b
    bool operator>(Persona other) {
        return this->_age > other._age;
    }
    uint getAge() {
        return this->_age;
    }
private:
    std::string _dni;
    std::string _name;
    uint _age;
};

template<typename T>
void BubleSort(Vector<T>& arr, std::function<bool(T,T)> compare) {

}

template<typename T>
void selectionSort(Vector<T>& arr, bool (*compare)(T,T)) {

}

int main() {
    Vector<Persona> vec;
    vec.pushBack(Persona("12345","Miguel",19));
    vec.pushBack(Persona("12345","Ana",19));
    vec.pushBack(Persona("12345","Maria",19));
    for(uint i = 0; i < vec.size(); ++i) std::cout << vec[i].toString() << "\n";

    auto show = [](Persona p) -> void {
        std::cout << p.toString() << " --> ";
    };
    std::cout << "\nLista Doble\n";
    DoublyLinkedList<Persona> list(show);
    list.pushBack(Persona("12345","Miguel",20));
    list.pushBack(Persona("12345","Ana",9));
    list.pushBack(Persona("12345","María",19));
    list.pushBack(Persona("12345","María",2));
    list.pushBack(Persona("12345","María",15));

    std::cout << "\nBefore Bubble Sort\n";
    DoublyLinkedList<Persona>::Iterator it = list.begin();
    for(it;it != list.end(); ++it) 
        std::cout << (*it).toString() << "\n";

    auto compareCriteria = [](Persona a, Persona b) -> bool {
        return a.getAge() < b.getAge(); // Si a es mayor a b retorna verdadero, por ende, intercambia sus valores
    };
    list.bubleSort(compareCriteria);

    std::cout << "\nAfter Bubble Sort\n";
    for(Persona p: list) std::cout << p.toString() << "\n"; 
    //list.display();
    return 0;
}