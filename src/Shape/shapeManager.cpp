#include "Shape/shapeManager.h"
#include "Page/pageManager.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

#include "Shape/shapes/diamond.h"
#include "Shape/shapes/rectangle.h"
#include "Shape/shapes/square.h"

ShapeManager::ShapeManager()
{
    shapesNumber = 0;  
    name = new char[8];
    strcpy(name, "Default");
    maxCapacity = 1000;
    shapes = new Shape*[maxCapacity];
    for (unsigned int i = 0; i < maxCapacity; ++i) {
        shapes[i] = nullptr;
    }
}

ShapeManager::ShapeManager(const char *name, unsigned int capacity)
{
    shapesNumber = 0;  
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    maxCapacity = capacity;
    shapes = new Shape*[maxCapacity];
    for (unsigned int i = 0; i < maxCapacity; ++i) {
        shapes[i] = nullptr;
    }
}

ShapeManager::ShapeManager(const char *name)
{
    shapesNumber = 0;  
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    maxCapacity = 1000;
    shapes = new Shape*[maxCapacity];
    for (unsigned int i = 0; i < maxCapacity; ++i) {
        shapes[i] = nullptr;
    }
}

ShapeManager::ShapeManager(unsigned int capacity)
{
    shapesNumber = 0;  
    this->name = new char[8];
    strcpy(this->name, "Default");
    maxCapacity = capacity;
    shapes = new Shape*[maxCapacity];
    for (unsigned int i = 0; i < maxCapacity; ++i) {
        shapes[i] = nullptr;
    }
}

ShapeManager::ShapeManager(const ShapeManager &other)
{   
    shapesNumber = other.shapesNumber;
    maxCapacity = other.maxCapacity;
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    
    shapes = new Shape*[maxCapacity];
    for (unsigned int i = 0; i < maxCapacity; ++i) {
        shapes[i] = nullptr;
    }
    
    // Deep copy - create new Shape objects using clone() for polymorphic copying
    for (int i = 0; i < other.shapesNumber; ++i) {
        if (other.shapes[i] != nullptr) {
            shapes[i] = other.shapes[i]->clone();
        }
    }
}

ShapeManager &ShapeManager::operator=(const ShapeManager &other)
{
    if (this == &other)
        return *this;

    // Delete existing shapes
    for (int i = 0; i < shapesNumber; ++i) {
        if (shapes[i] != nullptr) {
            delete shapes[i];
            shapes[i] = nullptr;
        }
    }
    delete[] shapes;
    delete[] name;

    // Copy data from other
    shapesNumber = other.shapesNumber;
    maxCapacity = other.maxCapacity;
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    
    shapes = new Shape*[maxCapacity];
    for (unsigned int i = 0; i < maxCapacity; ++i) {
        shapes[i] = nullptr;
    }
    
    // Deep copy shapes using clone() for polymorphic copying
    for (int i = 0; i < other.shapesNumber; ++i) {
        if (other.shapes[i] != nullptr) {
            shapes[i] = other.shapes[i]->clone();
        }
    }

    return *this;
}

ShapeManager::~ShapeManager()
{
    // Delete all Shape objects
    for (int i = 0; i < shapesNumber; ++i) {
        if (shapes[i] != nullptr) {
            delete shapes[i];
            shapes[i] = nullptr;
        }
    }
    delete[] shapes;
    delete[] name;

    if (PageManager::getSM() == this)
        PageManager::getSM() = nullptr;
}

Shape *ShapeManager::operator[](unsigned int index)
{
    if (index >= shapesNumber)
    {
        throw std::out_of_range("ShapeManager index out of bounds");
    }

    return shapes[index];
}

const Shape *ShapeManager::operator[](unsigned int index) const
{
    if (index >= shapesNumber)
    {
        throw std::out_of_range("ShapeManager index out of bounds");
    }

    return shapes[index];
}

ShapeManager ShapeManager::operator+(Shape* shape) const
{
    ShapeManager result = *this;

    if (result.shapesNumber < result.maxCapacity) {
        result.shapes[result.shapesNumber++] = shape;
    }
    return result;
}

ShapeManager &ShapeManager::operator+=(Shape* shape)
{
    if (shapesNumber < maxCapacity) {
        shapes[shapesNumber++] = shape;
    }
    return *this;
}

ShapeManager ShapeManager::operator-(unsigned int id) const
{
    ShapeManager result;
    result.name = new char[strlen(this->name) + 1];
    strcpy(result.name, this->name);
    result.maxCapacity = this->maxCapacity;
    result.shapesNumber = 0;
    
    result.shapes = new Shape*[result.maxCapacity];
    for (unsigned int i = 0; i < result.maxCapacity; ++i) {
        result.shapes[i] = nullptr;
    }

    // Copy all shapes except the one with matching id using clone()
    for (int i = 0; i < this->shapesNumber; ++i) {
        if (this->shapes[i]->getId() != id) {
            result.shapes[result.shapesNumber++] = this->shapes[i]->clone();
        }
    }
    
    return result;
}

ShapeManager &ShapeManager::operator-=(unsigned int id)
{
    for (int i = 0; i < shapesNumber; ++i) {
        if (shapes[i]->getId() == id) {
            delete shapes[i];
            // Shift remaining shapes
            for (int j = i; j < shapesNumber - 1; ++j) {
                shapes[j] = shapes[j + 1];
            }
            shapes[shapesNumber - 1] = nullptr;
            shapesNumber--;
            break;
        }
    }
    return *this;
}

ShapeManager &ShapeManager::operator++()
{
    for (int i = 0; i < shapesNumber; ++i) {
        ++(*shapes[i]);
    }
    return *this;
}

ShapeManager ShapeManager::operator++(int)
{
    ShapeManager temp = *this;
    ++(*this);
    return temp;
}

bool ShapeManager::operator==(const ShapeManager &other) const
{
    if (shapesNumber != other.shapesNumber)
    {
        return false;
    }

    for (int i = 0; i < shapesNumber; ++i) {
        bool found = false;

        for (int j = 0; j < other.shapesNumber; ++j) {
            if (*shapes[i] == *other.shapes[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

bool ShapeManager::operator<(const ShapeManager &other) const
{
    return shapesNumber < other.shapesNumber;
}

std::ostream &operator<<(std::ostream &out, const ShapeManager &sm)
{
    out << "========================================\n";
    out << "Shape Manager: " << sm.name << "\n";

    out << "Total shapes: " << sm.shapesNumber << "\n";
    out << "========================================\n";

    if (sm.shapesNumber == 0)
    {
        out << "  (No shapes)\n";
    }
    else
    {
        out << "    ID | Name      | Color      | Vertices | Coordinates\n";
        out << "----------------------------------------\n";

        for (int i = 0; i < sm.shapesNumber; ++i) {
            out << "[" << (i + 1) << "] " << *sm.shapes[i] << "\n";
        }
    }
    out << "========================================\n";
    return out;
}

std::istream &operator>>(std::istream &in, ShapeManager &sm)
{
    std::cout << "Enter number of shapes: ";
    unsigned int newCount;

    in >> newCount;

    // Clear existing shapes
    for (int i = 0; i < sm.shapesNumber; ++i) {
        if (sm.shapes[i] != nullptr) {
            delete sm.shapes[i];
            sm.shapes[i] = nullptr;
        }
    }
    sm.shapesNumber = 0;

    for (unsigned int i = 0; i < newCount && i < sm.maxCapacity; ++i) {
        std::cout << "Shape " << (i + 1) << ":\n";

        Shape temp;
        in >> temp;

        sm.shapes[sm.shapesNumber++] = new Shape(temp);
    }

    return in;
}

unsigned int ShapeManager::getCount() const
{
    return shapesNumber;
}

const char *ShapeManager::getName() const
{
    return name;
}

void ShapeManager::printAllRectangles() const
{
    for (int i = 0; i < shapesNumber; ++i) {
        Rectangle* rect = dynamic_cast<Rectangle*>(shapes[i]);
        if (rect != nullptr) {
            std::cout << *shapes[i] << "\n";
        }
    }
}

void ShapeManager::printAllDiamonds() const
{
    for (int i = 0; i < shapesNumber; ++i) {
        Diamond* dia = dynamic_cast<Diamond*>(shapes[i]);
        if (dia != nullptr) {
            std::cout << *shapes[i] << "\n";
        }
    }
}

void ShapeManager::printAllSquares() const
{
    for (int i = 0; i < shapesNumber; ++i) {
        Square* sq = dynamic_cast<Square*>(shapes[i]);
        if (sq != nullptr) {
            std::cout << *shapes[i] << "\n";
        }
    }
}