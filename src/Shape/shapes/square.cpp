#include "Shape/shapes/square.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

Square::Square(float side)
    : Rectangle(side, side), Diamond(side * std::sqrt(2.0f), side * std::sqrt(2.0f))
{
    std::cout << "      [4] Square::Constructor()" << std::endl;
    if (this->vertices)
        delete[] this->vertices;
    this->vertices = new Point[4];
    this->numVertices = 4;
    
    float halfSide = side / 2.0f;
    this->vertices[0] = Point(-halfSide, -halfSide);
    this->vertices[1] = Point(halfSide, -halfSide);
    this->vertices[2] = Point(halfSide, halfSide);
    this->vertices[3] = Point(-halfSide, halfSide);
    
    std::cout << "[Square] Constructed (side: " << side << ")" << std::endl;
}

Square::Square(const Square &other)
    : Shape(other), Rectangle(other), Diamond(other)
{
    std::cout << "      [4] Square::CopyConstructor()" << std::endl;
    if (this->vertices)
        delete[] this->vertices;
    this->vertices = new Point[4];
    this->numVertices = 4;
    
    float halfSide = Rectangle::width / 2.0f;
    this->vertices[0] = Point(-halfSide, -halfSide);
    this->vertices[1] = Point(halfSide, -halfSide);
    this->vertices[2] = Point(halfSide, halfSide);
    this->vertices[3] = Point(-halfSide, halfSide);
    
    std::cout << "[Square] Copy constructor" << std::endl;
}

Shape* Square::clone() const
{
    return new Square(*this);
}

std::string Square::toString() const
{
    std::ostringstream out;
    out << "Square | " << Shape::toString()
        << " | side=" << getSide();
    return out.str();
}

Square::~Square() noexcept
{
    std::cout << "      [5] Square::Destructor()" << std::endl;
    std::cout << "[Square] Destructed" << std::endl;
}

Square &Square::operator=(const Square &other)
{
    if (this != &other)
    {
        Shape::operator=(other);
        Rectangle::operator=(other);
        Diamond::operator=(other);
        
        if (this->vertices)
            delete[] this->vertices;
        this->vertices = new Point[4];
        this->numVertices = 4;
        
        float halfSide = Rectangle::width / 2.0f;
        this->vertices[0] = Point(-halfSide, -halfSide);
        this->vertices[1] = Point(halfSide, -halfSide);
        this->vertices[2] = Point(halfSide, halfSide);
        this->vertices[3] = Point(-halfSide, halfSide);
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
    const std::string nameInput = line;
    
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
    float side = static_cast<float>(std::stod(line));
    
    Square *square = new Square(side);
    square->color = (Color)colorChoice;
    square->name = nameInput;
    return square;
}
