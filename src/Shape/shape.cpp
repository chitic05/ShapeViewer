#include "Shape/shape.h"
#include <cstring>
#include <stdexcept>
#include <iostream>
unsigned int Shape::newestId = 0;
Shape::Shape()
    :id(++newestId), color(Color::RED), numVertices(0){
        vertices = nullptr;
        name = new char[9];
        strcpy(name, "Polygone");
}

Shape::Shape(unsigned int num,Point* vertices, Color color, const char* name)
    :numVertices(num), color(color), id(++newestId){
        this->vertices = new Point[num];
        for(unsigned int i=0; i<num;++i){
            this->vertices[i] = vertices[i];
        }
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
}
Shape::Shape(unsigned int num,Point* vertices)
    :numVertices(num), color(Color::RED), id(++newestId){
        this->vertices = new Point[num];
        for(unsigned int i=0; i<num;++i){
            this->vertices[i] = vertices[i];
        }
        this->name = new char[9];
        strcpy(this->name, "Polygone");
}

Shape::Shape(unsigned int num,Point* vertices, const char* name)
    :numVertices(num), color(Color::RED), id(++newestId){
        this->vertices = new Point[num];
        for(unsigned int i=0; i<num;++i){
            this->vertices[i] = vertices[i];
        }
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
}

Shape::~Shape(){
    delete[] vertices;
    delete[] name;
}

Shape::Shape(const Shape& other):id(++newestId){
    if(other.numVertices>0 && other.vertices){
        numVertices = other.numVertices;
        vertices = new Point[numVertices];
        for(unsigned int i = 0; i<numVertices;++i)
            vertices[i] = other.vertices[i];
    }else{
        numVertices=0;
        vertices=nullptr;
    }
    
    color = other.color;
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

Shape& Shape::operator=(const Shape& other){
    if(this == &other)
        return *this;
    
    // Delete old memory
    delete[] vertices;
    delete[] name;
    
    // Copy vertices
    if(other.numVertices>0 && other.vertices){
        numVertices = other.numVertices;
        vertices = new Point[numVertices];
        for(unsigned int i = 0; i<numVertices;++i)
            vertices[i] = other.vertices[i];
    }else{
        numVertices=0;
        vertices=nullptr;
    }
    
    color = other.color;
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    
    return *this;
}

Point& Shape::operator[](unsigned int index){
    if(vertices && index<numVertices){
        return vertices[index];
    }
    throw std::out_of_range("Shape index out of bounds");

}

const Point& Shape::operator[](unsigned int index) const{
    if(vertices && index<numVertices){
        return vertices[index];
    }
    throw std::out_of_range("Shape index out of bounds");

}

Shape operator*(const Matrix& matrix, const Shape& shape){
    Shape result = shape;
    for(unsigned int i=0; i<result.numVertices;++i){
        result[i] = matrix*result[i];
    }
    return result;
}

std::ostream& operator<<(std::ostream& out,const Shape& shape){
    out << "========================================\n";
    out << "Forma geometrica: " << shape.name << "\n";
    out << "ID: " << shape.id << "\n";
    out << "Culoare: ";
    switch(shape.color){
        case Color::RED:
            out << "ROSU";
            break;
        case Color::BLUE:
            out << "ALBASTRU";
            break;
        case Color::GREEN:
            out << "VERDE";
            break;
    }
    out << "\n";
    out << "Numar de varfuri: " << shape.numVertices << "\n";
    out << "Coordonatele varfurilor:\n";
    for(unsigned int i=0; i<shape.numVertices;++i){
        out << "  Varf " << (i+1) << ": " << shape[i] << '\n';
    }
    out << "========================================\n";
    return out;
}
std::istream& operator>>(std::istream& in, Shape& shape){
    std::cout << "Introduceti numele formei: ";
    char tempName[100];
    in >> tempName;
    delete[] shape.name;
    shape.name = new char[strlen(tempName) + 1];
    strcpy(shape.name, tempName);
    
    std::cout << "Introduceti culoarea (0-ROSU, 1-ALBASTRU, 2-VERDE): ";
    int colorChoice;
    in >> colorChoice;
    shape.color = static_cast<Color>(colorChoice);
    
    std::cout << "Introduceti numarul de varfuri: ";
    in >> shape.numVertices;
    if(shape.vertices)
        delete[] shape.vertices;
    shape.vertices = new Point[shape.numVertices];
    
    for(unsigned int i=0; i<shape.numVertices; ++i){
        std::cout << "Introduceti coordonatele varfului " << (i+1) << ":\n";
        in >> shape.vertices[i];
    }
    
    return in;
    
}
