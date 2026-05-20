#include "Shape/shapes/equilateralTriangle.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

EquilateralTriangle::EquilateralTriangle(float s)
    : Shape(), side(s)
{
    std::cout << "    [2] EquilateralTriangle::Constructor()" << std::endl;
    this->numVertices = 3;
    this->vertices.assign(3, Point());

    float height = std::sqrt(3.0f) * s / 2.0f;

    Point p0(-s / 2.0f, -height / 3.0f);
    Point p1(s / 2.0f, -height / 3.0f);
    Point p2(0.0f, (2.0f * height) / 3.0f);

    this->vertices[0] = p0;
    this->vertices[1] = p1;
    this->vertices[2] = p2;

    std::cout << "[EquilateralTriangle] Constructed (side: " << s << ")" << std::endl;
}

EquilateralTriangle::EquilateralTriangle(const EquilateralTriangle &other)
    : Shape(other), side(other.side)
{
    std::cout << "    [2] EquilateralTriangle::CopyConstructor()" << std::endl;
    this->numVertices = 3;
    this->vertices.assign(3, Point());

    for (unsigned int i = 0; i < 3; ++i)
        this->vertices[i] = other.vertices[i];

    std::cout << "[EquilateralTriangle] Copy constructor" << std::endl;
}

Shape *EquilateralTriangle::clone() const
{
    return new EquilateralTriangle(*this);
}

std::string EquilateralTriangle::toString() const
{
    std::ostringstream out;
    out << "EquilateralTriangle | " << Shape::toString()
        << " | side=" << side;
    return out.str();
}

EquilateralTriangle::~EquilateralTriangle() noexcept
{
    std::cout << "    [3] EquilateralTriangle::Destructor()" << std::endl;
    std::cout << "[EquilateralTriangle] Destructed" << std::endl;
}

EquilateralTriangle &EquilateralTriangle::operator=(const EquilateralTriangle &other)
{
    if (this != &other)
    {
        Shape::operator=(other);
        side = other.side;

        this->numVertices = 3;
        this->vertices.assign(3, Point());

        for (unsigned int i = 0; i < 3; ++i)
            this->vertices[i] = other.vertices[i];
    }
    return *this;
}

Shape *EquilateralTriangle::create()
{
    std::string line;

    std::cout << "Enter equilateral triangle name: ";
    std::getline(std::cin, line);
    if (line.empty())
        line = "EquilateralTriangle";
    const std::string nameInput = line;

    std::cout << "Enter color (0-RED, 1-BLUE, 2-GREEN): ";
    std::getline(std::cin, line);
    int colorChoice = 0;
    try
    {
        colorChoice = std::stoi(line);
        if (colorChoice < 0 || colorChoice > 2)
        {
            colorChoice = 0;
            std::cout << "Invalid color, using RED.\n";
        }
    }
    catch (...)
    {
        colorChoice = 0;
        std::cout << "Invalid color, using RED.\n";
    }

    std::cout << "Enter side length: ";
    std::getline(std::cin, line);
    float s = static_cast<float>(std::stod(line));

    EquilateralTriangle *tri = new EquilateralTriangle(s);
    tri->color = (Color)colorChoice;
    tri->name = nameInput;
    return tri;
}
