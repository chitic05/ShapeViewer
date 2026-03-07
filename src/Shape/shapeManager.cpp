#include "Shape/shapeManager.h"
#include <stdexcept>
#include <iostream>
#include <SDL3/SDL.h>

ShapeManager::ShapeManager():count(0), capacity(100){
    shapes = new Shape[capacity];
}

ShapeManager::ShapeManager(const Shape* shapes, unsigned int c, unsigned int cap){
    this->shapes = new Shape[c];
    count = c;
    if(cap < c) capacity = c+1;

    for(unsigned int i = 0; i<count;++i){
        this->shapes[i] = shapes[i];
    }
}

ShapeManager::ShapeManager(const Shape* shapes, unsigned int c){
    this->shapes = new Shape[c];
    count = c;
    capacity = c+1;

    for(unsigned int i = 0; i<count;++i){
        this->shapes[i] = shapes[i];
    }
}

ShapeManager::ShapeManager(unsigned int c){
    this->shapes = new Shape[c];
    count = c;
    capacity = c+1;
}

ShapeManager::ShapeManager(const ShapeManager& other){
    this->count = other.count;
    this->capacity = other.capacity;
    this->shapes = new Shape[this->capacity];
    for(unsigned int i = 0; i<count;++i){
        this->shapes[i] = other.shapes[i];
    }
}

ShapeManager& ShapeManager::operator=(const ShapeManager& other){
    if(this == &other) return *this;

    if(shapes) delete[] shapes;
    this->count = other.count;
    this->capacity = other.capacity;
    this->shapes = new Shape[this->capacity];
    for(unsigned int i = 0; i<count;++i){
        this->shapes[i] = other.shapes[i];
    }
    return *this;
}

ShapeManager::~ShapeManager(){
    if(shapes) delete[] shapes;
}

// Operator [] - accesare element
Shape& ShapeManager::operator[](unsigned int index){
    if(index >= count){
        throw std::out_of_range("ShapeManager index out of bounds");
    }
    return shapes[index];
}

const Shape& ShapeManager::operator[](unsigned int index) const{
    if(index >= count){
        throw std::out_of_range("ShapeManager index out of bounds");
    }
    return shapes[index];
}

// Operator + - adauga un Shape in lista
ShapeManager ShapeManager::operator+(const Shape& shape) const{
    ShapeManager result = *this;
    
    // Verificam daca mai avem capacitate
    if(result.count >= result.capacity){
        // Realocam cu mai mult spatiu
        unsigned int newCapacity = result.capacity * 2;
        Shape* newShapes = new Shape[newCapacity];
        
        for(unsigned int i = 0; i < result.count; ++i){
            newShapes[i] = result.shapes[i];
        }
        
        delete[] result.shapes;
        result.shapes = newShapes;
        result.capacity = newCapacity;
    }
    
    // Adaugam noul shape
    result.shapes[result.count] = shape;
    result.count++;
    
    return result;
}

// Operator - - sterge elementul cu ID-ul dat
ShapeManager ShapeManager::operator-(unsigned int id) const{
    ShapeManager result;
    result.capacity = this->capacity;
    delete[] result.shapes;
    result.shapes = new Shape[this->capacity];
    result.count = 0;
    
    // Copiem toate shape-urile cu excepția celui cu ID-ul dat
    for(unsigned int i = 0; i < this->count; ++i){
        if(this->shapes[i].getId() != id){
            result.shapes[result.count] = this->shapes[i];
            result.count++;
        }
    }
    
    return result;
}

// Operator ++ (pre-incrementare) - incrementeaza toate shape-urile
ShapeManager& ShapeManager::operator++(){
    for(unsigned int i = 0; i < count; ++i){
        ++shapes[i];
    }
    return *this;
}

// Operator ++ (post-incrementare)
ShapeManager ShapeManager::operator++(int){
    ShapeManager temp = *this;
    ++(*this);
    return temp;
}

// Operator == - verifica daca au acelasi numar de shape-uri si aceleasi puncte
bool ShapeManager::operator==(const ShapeManager& other) const{
    if(this->count != other.count){
        return false;
    }
    
    for(unsigned int i = 0; i < count; ++i){
        bool found = false;
        for(unsigned int j = 0; j < other.count; ++j){
            if(this->shapes[i] == other.shapes[j]){
                found = true;
                break;
            }
        }
        if(!found){
            return false;
        }
    }
    
    return true;
}

// Operator < - verifica daca are mai putine shape-uri
bool ShapeManager::operator<(const ShapeManager& other) const{
    return this->count < other.count;
}

// Operator << - afisare
std::ostream& operator<<(std::ostream& out, const ShapeManager& sm){
    out << "========================================\n";
    out << "Shape Manager - Total shapes: " << sm.count << "\n";
    out << "Capacity: " << sm.capacity << "\n";
    out << "========================================\n";
    for(unsigned int i = 0; i < sm.count; ++i){
        out << sm.shapes[i] << "\n";
    }
    out << "========================================\n";
    return out;
}

// Operator >> - citire
std::istream& operator>>(std::istream& in, ShapeManager& sm){
    std::cout << "Introduceti numarul de shape-uri: ";
    unsigned int newCount;
    in >> newCount;
    
    if(sm.shapes){
        delete[] sm.shapes;
    }
    
    sm.shapes = new Shape[newCount];
    sm.count = newCount;
    sm.capacity = newCount;
    
    for(unsigned int i = 0; i < sm.count; ++i){
        std::cout << "Shape " << (i+1) << ":\n";
        in >> sm.shapes[i];
    }
    
    return in;
}