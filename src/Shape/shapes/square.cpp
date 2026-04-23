#include "Shape/shapes/square.h"
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>

Square::Square(float side)
    : Rectangle(side, side), Diamond(side * std::sqrt(2.0f), side * std::sqrt(2.0f))
{
    // Override to ensure square vertices (90 degrees - axis aligned)
    if (this->vertices)
        delete[] this->vertices;
    this->vertices = new Point[4];
    this->numVertices = 4;
    
    // Square vertices at 90 degrees (axis-aligned)
    float halfSide = side / 2.0f;
    this->vertices[0] = Point(-halfSide, -halfSide);  // Bottom-left
    this->vertices[1] = Point(halfSide, -halfSide);   // Bottom-right
    this->vertices[2] = Point(halfSide, halfSide);    // Top-right
    this->vertices[3] = Point(-halfSide, halfSide);   // Top-left
    
    std::cout << "[Square] Constructed (side: " << side << ")" << std::endl;
}

Square::Square(const Square &other)
    : Shape(other), Rectangle(other), Diamond(other)
{
    std::cout << "[Square] Copy constructor" << std::endl;
}

Shape* Square::clone() const
{
    return new Square(*this);
}

Square::~Square()
{
    std::cout << "[Square] Destructed" << std::endl;
}

Square &Square::operator=(const Square &other)
{
    if (this != &other)
    {
        Shape::operator=(other);
        Rectangle::width = other.Rectangle::width;
        Rectangle::height = other.Rectangle::height;
        Diamond::diagonal1 = other.Diamond::diagonal1;
        Diamond::diagonal2 = other.Diamond::diagonal2;
    }
    return *this;
}

void Square::printInfo() const
{
    std::cout << "  [Square] As Rectangle - Area: " << Rectangle::getArea() << std::endl;
    std::cout << "  [Square] As Diamond - Area: " << Diamond::getArea() << std::endl;
    std::cout << "  [Square] As Diamond - Perimeter: " << Diamond::getPerimeter() << std::endl;
}

Shape *Square::create()
{
    std::string line;
    
    std::cout << "Enter square name: ";
    std::getline(std::cin, line);
    if (line.empty())
        line = "Square";
    
    std::cout << "Enter color (0-RED, 1-BLUE, 2-GREEN): ";
    std::getline(std::cin, line);
    int colorChoice = 0;
    try {
        colorChoice = std::stoi(line);
        if (colorChoice < 0 || colorChoice > 2) {
            colorChoice = 0;
            std::cout << "Invalid color, using RED.\n";
        }
    } catch (...) {
        colorChoice = 0;
        std::cout << "Invalid color, using RED.\n";
    }
    
    std::cout << "Enter square side length: ";
    std::getline(std::cin, line);
    float side = std::stof(line);
    
    Square *square = new Square(side);
    square->color = (Color)colorChoice;
    square->name = new char[7];
    strcpy(square->name, "Square");
    return square;
}
