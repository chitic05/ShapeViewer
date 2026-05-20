#include "Shape/shapes/rightTriangle.h"
#include <iostream>
#include <sstream>
#include <string>

RightTriangle::RightTriangle(float a, float b)
    : Shape(), legA(a), legB(b)
{
    std::cout << "    [2] RightTriangle::Constructor()" << std::endl;
    this->numVertices = 3;
    this->vertices.assign(3, Point());

    Point p0(0.0f, 0.0f);
    Point p1(a, 0.0f);
    Point p2(0.0f, b);

    Point centroid((p0[0] + p1[0] + p2[0]) / 3.0f,
                   (p0[1] + p1[1] + p2[1]) / 3.0f);

    this->vertices[0] = p0 - centroid;
    this->vertices[1] = p1 - centroid;
    this->vertices[2] = p2 - centroid;

    std::cout << "[RightTriangle] Constructed (" << a << ", " << b << ")" << std::endl;
}

RightTriangle::RightTriangle(const RightTriangle &other)
    : Shape(other), legA(other.legA), legB(other.legB)
{
    std::cout << "    [2] RightTriangle::CopyConstructor()" << std::endl;
    this->numVertices = 3;
    this->vertices.assign(3, Point());

    for (unsigned int i = 0; i < 3; ++i)
        this->vertices[i] = other.vertices[i];

    std::cout << "[RightTriangle] Copy constructor" << std::endl;
}

Shape *RightTriangle::clone() const
{
    return new RightTriangle(*this);
}

std::string RightTriangle::toString() const
{
    std::ostringstream out;
    out << "RightTriangle | " << Shape::toString()
        << " | a=" << legA << " | b=" << legB;
    return out.str();
}

RightTriangle::~RightTriangle() noexcept
{
    std::cout << "    [3] RightTriangle::Destructor()" << std::endl;
    std::cout << "[RightTriangle] Destructed" << std::endl;
}

RightTriangle &RightTriangle::operator=(const RightTriangle &other)
{
    if (this != &other)
    {
        Shape::operator=(other);
        legA = other.legA;
        legB = other.legB;

        this->numVertices = 3;
        this->vertices.assign(3, Point());

        for (unsigned int i = 0; i < 3; ++i)
            this->vertices[i] = other.vertices[i];
    }
    return *this;
}

Shape *RightTriangle::create()
{
    std::string line;

    std::cout << "Enter right triangle name: ";
    std::getline(std::cin, line);
    if (line.empty())
        line = "RightTriangle";
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

    std::cout << "Enter leg A length: ";
    std::getline(std::cin, line);
    float a = static_cast<float>(std::stod(line));

    std::cout << "Enter leg B length: ";
    std::getline(std::cin, line);
    float b = static_cast<float>(std::stod(line));

    RightTriangle *tri = new RightTriangle(a, b);
    tri->color = (Color)colorChoice;
    tri->name = nameInput;
    return tri;
}
