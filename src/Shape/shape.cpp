#include "Shape/shape.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <math.h>

Shape::Shape() : color(Color::RED), numVertices(0)
{
    std::cout << "  [1] Shape::Constructor()" << std::endl;
    vertices.clear();
    name = "Polygone";
}

Shape::Shape(unsigned int num, Point *vertices, Color color, const std::string& name)
    : numVertices(num), color(color)
{
    this->vertices.assign(vertices, vertices + num);

    this->name = name;
}

Shape::Shape(unsigned int num, Point *vertices)
    : numVertices(num), color(Color::RED)
{
    this->vertices.assign(vertices, vertices + num);

    this->name = "Polygone";
}

Shape::Shape(unsigned int num, Point *vertices, const std::string& name)
    : numVertices(num), color(Color::RED)
{
    this->vertices.assign(vertices, vertices + num);

    this->name = name;
}

Shape::Shape(unsigned int num, Point *vertices, Color color, const std::string& name, float centerX,
             float centerY)
    : numVertices(num), color(color)
{
    this->vertices.resize(num);
    for (unsigned int i = 0; i < num; ++i)
        this->vertices[i] = vertices[i] + Point(centerX, centerY);

    this->name = name;
}

Shape::Shape(unsigned int num, Point *vertices, float centerX, float centerY)
    : numVertices(num), color(Color::RED)
{
    this->vertices.resize(num);
    for (unsigned int i = 0; i < num; ++i)
        this->vertices[i] = vertices[i] + Point(centerX, centerY);

    this->name = "Polygone";
}

Shape::Shape(unsigned int num, Point *vertices, const std::string& name, float centerX, float centerY)
    : numVertices(num), color(Color::RED)
{
    this->vertices.resize(num);
    for (unsigned int i = 0; i < num; ++i)
        this->vertices[i] = vertices[i] + Point(centerX, centerY);

    this->name = name;
}

Shape::~Shape() noexcept
{
    std::cout << "  [4] Shape::Destructor()" << std::endl;
}

Shape::Shape(const Shape &other)
{
    std::cout << "  [1] Shape::CopyConstructor()" << std::endl;
    numVertices = other.numVertices;
    vertices = other.vertices;

    color = other.color;
    name = other.name;
}

Shape* Shape::clone() const
{
    return new Shape(*this);
}

Shape &Shape::operator=(const Shape &other)
{
    if (this == &other)
        return *this;

    numVertices = other.numVertices;
    vertices = other.vertices;

    color = other.color;
    name = other.name;

    return *this;
}

Point &Shape::operator[](unsigned int index)
{
    if (index < numVertices)
    {
        return vertices[index];
    }

    throw std::out_of_range("Shape index out of bounds");
}

const Point &Shape::operator[](unsigned int index) const
{
    if (index < numVertices)
    {
        return vertices[index];
    }

    throw std::out_of_range("Shape index out of bounds");
}

Shape Shape::operator+(const float val) const
{
    Shape copie = *this;

    for (unsigned int i = 0; i < copie.numVertices; ++i)
    {
        copie.vertices[i] = copie.vertices[i] + Point(val, val);
    }

    return copie;
}

Shape operator*(const Matrix &matrix, const Shape &shape)
{
    Shape result = shape;

    for (unsigned int i = 0; i < result.numVertices; ++i)
    {
        result[i] = matrix * result[i];
    }
    return result;
}

std::ostream &operator<<(std::ostream &out, const Shape &shape)
{
    out << shape.getId() << " | " << shape.name << " | ";

    switch (shape.color)
    {
    case Color::RED:
        out << "RED";
        break;
    case Color::BLUE:
        out << "BLUE";
        break;
    case Color::GREEN:
        out << "GREEN";
        break;
    }

    out << " | " << shape.numVertices << " | ";
    for (unsigned int i = 0; i < shape.numVertices; ++i)
    {

        if (i > 0)
            out << ", ";
        out << "(" << shape[i].getCoord()[0] << "," << shape[i].getCoord()[1] << ")";
    }
    return out;
}

std::istream &operator>>(std::istream &in, Shape &shape)
{
    std::string line;

    std::cout << "Enter shape name: ";
    std::getline(in, line);

    if (line.empty())
        line = "Polygone";

    size_t pos = line.find('_');
    while (pos != std::string::npos) {
        line.replace(pos, 1, " ");
        pos = line.find('_', pos + 1);
    }

    if (line.size() > 24)
        line = line.substr(0, 24);

    shape.name = line;

    std::cout << "Enter color (0-RED, 1-BLUE, 2-GREEN): ";
    std::getline(in, line);

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
    shape.color = (Color)colorChoice;

    std::cout << "Enter number of vertices: ";
    std::getline(in, line);

    try
    {
        shape.numVertices = std::stoi(line);

        if (shape.numVertices == 0 || shape.numVertices > 1000)
        {
            shape.numVertices = 3;
            std::cout << "Invalid number, using " << std::to_string(shape.numVertices)
                      << " vertices.\n";
        }
    }
    catch (...)
    {
        shape.numVertices = 3;
        std::cout << "Invalid number, using " << std::to_string(shape.numVertices)
                  << " vertices.\n";
    }

    shape.vertices.assign(shape.numVertices, Point());

    for (unsigned int i = 0; i < shape.numVertices; ++i)
    {
        std::cout << "Enter coordinates for vertex " << (i + 1) << " (x y): ";

        std::getline(in, line);
        try
        {
            size_t pos;

            double x = std::stod(line, &pos);
            double y = std::stod(line.substr(pos));
            shape.vertices[i] = Point(static_cast<float>(x), static_cast<float>(y));
        }
        catch (...)
        { // prinde toate erorile
            shape.vertices[i] = Point(0, 0);
            std::cout << "Invalid coordinates, using (0, 0).\n";
        }
    }
    return in;
}

Shape &Shape::operator++()
{
    *this = *this + 1;
    return *this;
}

Shape Shape::operator++(int)
{
    Shape ret = *this;
    *this = *this + 1;
    return ret;
}

Point Shape::getCentre() const
{
    if (numVertices == 0)
    {
        return Point(0, 0);
    }

    float sumX = 0.0f;
    float sumY = 0.0f;

    for (unsigned int i = 0; i < numVertices; ++i)
    {
        sumX += vertices[i].getCoord()[0];
        sumY += vertices[i].getCoord()[1];
    }

    return Point(sumX / numVertices, sumY / numVertices);
}

bool Shape::operator==(const Shape &other) const
{
    return getId() == other.getId();
}

bool Shape::operator<(const Shape &other) const
{
    return getId() < other.getId();
}

unsigned int Shape::getCount() const
{
    return numVertices;
}

Color Shape::getColor() const
{
    return color;
}

const std::string& Shape::getName() const
{
    return name;
}

std::string Shape::toString() const
{
    std::ostringstream out;
    out << getId() << " | " << name << " | ";
    switch (color)
    {
    case Color::RED:
        out << "RED";
        break;
    case Color::BLUE:
        out << "BLUE";
        break;
    case Color::GREEN:
        out << "GREEN";
        break;
    }

    out << " | " << numVertices << " | ";
    for (unsigned int i = 0; i < numVertices; ++i)
    {
        if (i > 0)
            out << ", ";
        out << "(" << (*this)[i].getCoord()[0] << "," << (*this)[i].getCoord()[1] << ")";
    }
    return out.str();
}

float Shape::getPerimeter(){
    if (numVertices < 2) {
        return 0.0f;
    }

    float perimeter = 0.0f;

    for (int i = 0; i < numVertices; ++i) {
        int next_i = (i + 1) % numVertices;

        float dx = vertices[i][0] - vertices[next_i][0];
        float dy = vertices[i][1] - vertices[next_i][1];

        perimeter += sqrtf((dx * dx) + (dy * dy));
    }

    return perimeter;
}

Shape *Shape::create() {
    Shape *shape = new Shape();
    std::cin >> *shape;
    return shape;
}
