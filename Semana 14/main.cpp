#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <ctime>
#include "AVL.hpp"

struct Persona {
    std::string id;
    std::string name;
    int age;
    std::string phoneNumber;
};

class DatasetGenerator {
    std::ifstream readFile;
    std::ofstream writeFile;
public:
    DatasetGenerator() {

    }
    void generateInFile(int c) {
        std::ofstream arch("input.csv");
        for(int i = 0; i < c; ++i) {
            Persona p = _generatePersona();
            arch << p.id << "," << p.name << "," << p.age << "," << p.phoneNumber << "\n"; 
        }
        arch.close();
    }
private:
    Persona _generatePersona() {
        std::string id = _randomStringCode(3);
        std::string name = _randomStringCode(10);
        int age = 20 + rand()%(80 - 20 + 1);
        std::string phoneNumber = std::to_string(100000000 + rand()%(999999999 - 100000000 + 1));
        return Persona{id, name, age, phoneNumber};
    }
    std::string _randomStringCode(int length) {
        // A -> 65
        // Z -> 90
        std::string result;
        for(int i = 0; i < length; ++i) {
            int randomAscii = 65 + rand() % (90 - 65 + 1);
            result.push_back(static_cast<char>(randomAscii));
        }
        return result;
    }
};

int main() {
    srand(time(0));
    AVLTree<int> tree(
        [](int value ) -> void {
            std::cout << value << " ";
        },
        [] (int a, int b) -> bool {
            return a > b;
        },
        [](int a, int b) -> bool {
            return a == b;
        }
    );
    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    tree.insert(2);
    tree.insert(4);
    tree.insert(7);
    tree.IterativePreOrder();
    tree.remove(3);
    std::cout << "\n";
    tree.IterativePreOrder();
    DatasetGenerator ds;
    ds.generateInFile(10);
    return 0;
}