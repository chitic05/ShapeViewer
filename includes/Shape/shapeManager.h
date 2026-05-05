#pragma once
#include "Shape/shape.h"

class ShapeManager
{
// PRIVATE: Doar ShapeManager poate accesa
private:
    // VALID: ShapeManager::operator[] poate accesa shapes
    // INVALID: Codul extern NU poate accesa shapes direct
    // INVALID: PrintPage NU poate modifica shapes array
    Shape** shapes;
    
    // VALID: ShapeManager::getCount() citeste shapesNumber
    // INVALID: Extern code NU poate citi shapesNumber direct
    int shapesNumber;
    
    // VALID: ShapeManager constructor initializeaza name
    // INVALID: Extern code NU poate modifica name direct
    char *name;
    
    // VALID: ShapeManager::operator+ foloseste maxCapacity
    // INVALID: Codul extern NU poate verifica capacity
    unsigned int maxCapacity;

// PUBLIC: Accesibil din oriunde
public:
    // Face un manager cu nume "Default" si capacitate 100
    ShapeManager();

    // Face un manager cu nume si capacitate specificate
    ShapeManager(const char *name, unsigned int capacity);

    // Face un manager cu nume specificat si capacitate 100
    ShapeManager(const char *name);

    // Face un manager cu nume "Default" si capacitate specificata
    ShapeManager(unsigned int capacity);

    // Copy constructor
    ShapeManager(const ShapeManager &other);

    ShapeManager &operator=(const ShapeManager &other);

    // Destructorul pentru a nu avea pierderi de memorie
    ~ShapeManager();

    // Access Shape pointer by index
    Shape *operator[](unsigned int index);

    // Const access Shape pointer by index
    const Shape *operator[](unsigned int index) const;

    // Creeaza un manager nou cu forma adaugata (takes ownership of pointer)
    ShapeManager operator+(Shape* shape) const;

    // Adauga o forma in manager (takes ownership of pointer)
    ShapeManager &operator+=(Shape* shape);

    // Creeaza un manager nou fara forma cu id-ul dat
    ShapeManager operator-(unsigned int id) const;

    // Sterge forma cu id-ul dat din manager
    ShapeManager &operator-=(unsigned int id);

    // Incrementeaza toate formele (prefixat)
    ShapeManager &operator++();

    // Incrementeaza toate formele (postfixat)
    ShapeManager operator++(int);

    // Daca au acelasi numar de forme
    bool operator==(const ShapeManager &other) const;

    // Compara dupa numar de forme
    bool operator<(const ShapeManager &other) const;

    // Afiseaza toate formele din manager
    friend std::ostream &operator<<(std::ostream &out, const ShapeManager &sm);

    // Citeste manager de la utilizator
    friend std::istream &operator>>(std::istream &in, ShapeManager &sm);

    // Returneaza numarul de forme
    unsigned int getCount() const;

    // Returneaza numele managerului
    const char *getName() const;

    // Filter methods using dynamic_cast for type-safe filtering
    void printAllRectangles() const;
    void printAllDiamonds() const;
    void printAllSquares() const;
};