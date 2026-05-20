#include "Shape/shapes/diamond.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

Diamond::Diamond(float d1, float d2)
    : Shape(), diagonal1(d1), diagonal2(d2)
{
    std::cout << "    [2] Diamond::Constructor()" << std::endl;
    this->numVertices = 4;
    this->vertices.assign(4, Point());
    
    this->vertices[0] = Point(0, d1 / 2.0f);
    this->vertices[1] = Point(d2 / 2.0f, 0);
    this->vertices[2] = Point(0, -d1 / 2.0f);
    this->vertices[3] = Point(-d2 / 2.0f, 0);
    
    std::cout << "[Diamond] Constructed (" << d1 << ", " << d2 << ")" << std::endl;
}

Diamond::Diamond(const Diamond &other)
    : Shape(other), diagonal1(other.diagonal1), diagonal2(other.diagonal2)
{
    std::cout << "    [2] Diamond::CopyConstructor()" << std::endl;
    this->numVertices = 4;
    this->vertices.assign(4, Point());
    
    this->vertices[0] = Point(0, diagonal1 / 2.0f);
    this->vertices[1] = Point(diagonal2 / 2.0f, 0);
    this->vertices[2] = Point(0, -diagonal1 / 2.0f);
    this->vertices[3] = Point(-diagonal2 / 2.0f, 0);
    
    std::cout << "[Diamond] Copy constructor" << std::endl;
}

Shape* Diamond::clone() const
{
    return new Diamond(*this);
}

std::string Diamond::toString() const
{
    std::ostringstream out;
    out << "Diamond | " << Shape::toString()
        << " | d1=" << diagonal1 << " | d2=" << diagonal2;
    return out.str();
}

Diamond::~Diamond() noexcept
{
    std::cout << "    [3] Diamond::Destructor()" << std::endl;
    std::cout << "[Diamond] Destructed" << std::endl;
}

Diamond &Diamond::operator=(const Diamond &other)
{
    if (this != &other)
    {
        Shape::operator=(other);
        diagonal1 = other.diagonal1;
        diagonal2 = other.diagonal2;

        this->numVertices = 4;
        this->vertices.assign(4, Point());
        
        this->vertices[0] = Point(0, diagonal1 / 2.0f);
        this->vertices[1] = Point(diagonal2 / 2.0f, 0);
        this->vertices[2] = Point(0, -diagonal1 / 2.0f);
        this->vertices[3] = Point(-diagonal2 / 2.0f, 0);
    }
    return *this;
}

Shape *Diamond::create()
{
    std::string line;
    
    std::cout << "Enter diamond name: ";
    std::getline(std::cin, line);
    if (line.empty())
        line = "Diamond";
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
    
    std::cout << "Enter first diagonal: ";
    std::getline(std::cin, line);
    float diag1 = static_cast<float>(std::stod(line));
    
    std::cout << "Enter second diagonal: ";
    std::getline(std::cin, line);
    float diag2 = static_cast<float>(std::stod(line));
    
    Diamond *diamond = new Diamond(diag1, diag2);
    diamond->color = (Color)colorChoice;
    diamond->name = nameInput;
    return diamond;
}
