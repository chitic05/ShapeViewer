#include "Shape/shapes/rectangle.h"
#include <iostream>
#include <cstring>
#include <string>

Rectangle::Rectangle(float w, float h)
    : Shape(), width(w), height(h)
{
    // Initialize 4 vertices based on width and height
    if (this->vertices)
        delete[] this->vertices;
    this->vertices = new Point[4];
    this->numVertices = 4;
    
    // Top-left
    this->vertices[0] = Point(-w / 2.0f, h / 2.0f);
    // Top-right
    this->vertices[1] = Point(w / 2.0f, h / 2.0f);
    // Bottom-right
    this->vertices[2] = Point(w / 2.0f, -h / 2.0f);
    // Bottom-left
    this->vertices[3] = Point(-w / 2.0f, -h / 2.0f);
    
    std::cout << "[Rectangle] Constructed (" << w << " x " << h << ")" << std::endl;
}

Rectangle::Rectangle(const Rectangle &other)
    : Shape(other), width(other.width), height(other.height)
{
    std::cout << "[Rectangle] Copy constructor" << std::endl;
}

Shape* Rectangle::clone() const
{
    return new Rectangle(*this);
}

Rectangle::~Rectangle()
{
    std::cout << "[Rectangle] Destructed" << std::endl;
}

Rectangle &Rectangle::operator=(const Rectangle &other)
{
    if (this != &other)
    {
        Shape::operator=(other);
        width = other.width;
        height = other.height;
    }
    return *this;
}

Shape *Rectangle::create()
{
    std::string line;
    
    std::cout << "Enter rectangle name: ";
    std::getline(std::cin, line);
    if (line.empty())
        line = "Rectangle";
    
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
    
    std::cout << "Enter rectangle width: ";
    std::getline(std::cin, line);
    float width = std::stof(line);
    
    std::cout << "Enter rectangle height: ";
    std::getline(std::cin, line);
    float height = std::stof(line);
    
    Rectangle *rect = new Rectangle(width, height);
    rect->color = (Color)colorChoice;
    rect->name = new char[10];
    strcpy(rect->name, "Rectangle");
    return rect;
}
