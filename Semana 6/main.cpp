#include <iostream>
#include "Vector.hpp"
#include <string>
#include <functional>

typedef unsigned int uint;

class Persona {
public:
    Persona(std::string dni, std::string name, uint age)
        :_dni(dni), _name(name), _age(age) {}
    ~Persona() {
        std::cout << "Destroying\n";
    }
    std::string toString() {
        return this->_dni + ", " + this->_name + ", " + std::to_string(this->_age);
    }
    // Sobrecargando el cout :O
    friend std::ostream& operator<<(std::ostream& os, Persona p) {
        os << p._dni << ", " << p._name << ", " << p._age;
        return os;
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
    Vector<Persona*> vec([](Persona* p) -> void {delete p;});
    vec.pushBack(new Persona("12345","Miguel",19));
    vec.pushBack(new Persona("12345","Ana",19));
    vec.pushBack(new Persona("12345","Maria",19));
    for(uint i = 0; i < vec.size(); ++i) std::cout << (*vec[i]) << "\n";
    return 0;
}