#include "Shape/shapeManager.h"
#include <stdexcept>
#include <iostream>
#include <cstring>
#include "Page/pageManager.h"

ShapeManager::ShapeManager(){
    name = new char[8];
    strcpy(name, "Default");
    maxCapacity = 100;
}

ShapeManager::ShapeManager(const char* name, unsigned int capacity){
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    maxCapacity = capacity;
}

ShapeManager::ShapeManager(const char* name){
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    maxCapacity = 100;
}

ShapeManager::ShapeManager(unsigned int capacity){
    this->name = new char[8];
    strcpy(this->name, "Default");
    maxCapacity = capacity;
}

ShapeManager::ShapeManager(const ShapeManager& other){
    shapes = other.shapes;
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    maxCapacity = other.maxCapacity;
}

ShapeManager& ShapeManager::operator=(const ShapeManager& other){
    if(this == &other) return *this;

    delete[] name;
    shapes = other.shapes;
    
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    maxCapacity = other.maxCapacity;
    
    return *this;
}

ShapeManager::~ShapeManager(){
    delete[] name;
    
    if(PageManager::getSM() == this)
        PageManager::getSM() = nullptr;
}

Shape& ShapeManager::operator[](unsigned int index){
    if(index >= shapes.size()){
        throw std::out_of_range("ShapeManager index out of bounds");
    }
    
    return shapes[index];
}

const Shape& ShapeManager::operator[](unsigned int index) const{
    if(index >= shapes.size()){
        throw std::out_of_range("ShapeManager index out of bounds");
    }
    
    return shapes[index];
}

ShapeManager ShapeManager::operator+(const Shape& shape) const{
    ShapeManager result = *this;
    
    result.shapes.push_back(shape);
    return result;
}

ShapeManager& ShapeManager::operator+=(const Shape& shape){
    shapes.push_back(shape);
    return *this;
}

ShapeManager ShapeManager::operator-(unsigned int id) const{
    ShapeManager result = *this;
    
    for(size_t i = 0; i < result.shapes.size(); ++i){
        if(result.shapes[i].getId() == id){
            
            result.shapes.erase(result.shapes.begin() + i);
            break;
        }
    }
    return result;
}

ShapeManager& ShapeManager::operator-=(unsigned int id){
    for(size_t i = 0; i < shapes.size(); ++i){
        if(shapes[i].getId() == id){
            
            shapes.erase(shapes.begin() + i);
            break;
        }
    }
    return *this;
}

ShapeManager& ShapeManager::operator++(){
    for(size_t i = 0; i < shapes.size(); ++i){
        ++shapes[i];
    }
    return *this;
}

ShapeManager ShapeManager::operator++(int){
    ShapeManager temp = *this;
    ++(*this);
    return temp;
}

bool ShapeManager::operator==(const ShapeManager& other) const{
    if(shapes.size() != other.shapes.size()){
        return false;
    }
    
    for(size_t i = 0; i < shapes.size(); ++i){
        bool found = false;
        
        for(size_t j = 0; j < other.shapes.size(); ++j){
            if(shapes[i] == other.shapes[j]){
                
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

bool ShapeManager::operator<(const ShapeManager& other) const{
    return shapes.size() < other.shapes.size();
}

std::ostream& operator<<(std::ostream& out, const ShapeManager& sm){
    out << "========================================\n";
    out << "Shape Manager: " << sm.name << "\n";
    
    out << "Total shapes: " << sm.shapes.size() << "\n";
    out << "========================================\n";
    
    if(sm.shapes.empty()){
        out << "  (No shapes)\n";
    } else {
        
        out << "    ID | Nume      | Culoare    | Vertices | Coordonate\n";
        out << "----------------------------------------\n";
        
        for(size_t i = 0; i < sm.shapes.size(); ++i){
            out << "[" << (i+1) << "] " << sm.shapes[i] << "\n";
        }
    }
    out << "========================================\n";
    return out;
}

std::istream& operator>>(std::istream& in, ShapeManager& sm){
    std::cout << "Introduceti numarul de shape-uri: ";
    unsigned int newCount;
    
    in >> newCount;
    
    sm.shapes.clear();
    
    for(unsigned int i = 0; i < newCount; ++i){
        std::cout << "Shape " << (i+1) << ":\n";
        
        Shape temp;
        in >> temp;
        
        sm.shapes.push_back(temp);
    }
    
    return in;
}

unsigned int ShapeManager::getCount() const{
    return shapes.size();
}

const char* ShapeManager::getName() const{
    return name;
}