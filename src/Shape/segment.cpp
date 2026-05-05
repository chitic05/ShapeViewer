#include "Shape/segment.h"
#include <iostream>
#include <cmath>

// Demonstrare INITIALIZER LIST - membrii se initializeaza IN ORDINEA DECLARATIEI din header
// start(s), end(e) initializeaza membrii INAINTE de a executa corpul constructorului
// Aceasta e cea mai eficienta cale de a initializa membri obiecti
Segment::Segment(Point s, Point e) : start(s), end(e)
{
    std::cout << "    [Segment] Constructor cu initializer list: start(" 
              << start[0] << "," << start[1] 
              << ") end(" << end[0] << "," << end[1] << ")" << std::endl;
}

// Constructor alternativ cu coordonate directe
// Apeleaza constructorul Point din lista de inițializare
Segment::Segment(int x1, int y1, int x2, int y2) : start(x1, y1), end(x2, y2)
{
    std::cout << "    [Segment] Constructor cu coordonate: (" 
              << x1 << "," << y1 << ") -> (" << x2 << "," << y2 << ")" << std::endl;
}

// Copy constructor - initializeaza membrii prin copiere
Segment::Segment(const Segment &other) : start(other.start), end(other.end)
{
    std::cout << "    [Segment] Copy constructor" << std::endl;
}

// Destructor
Segment::~Segment()
{
    std::cout << "    [Segment] Destructor" << std::endl;
}

// Getters
Point Segment::getStart() const
{
    return start;
}

Point Segment::getEnd() const
{
    return end;
}

// Calculate distance between two points
double Segment::getLength() const
{
    int dx = end[0] - start[0];
    int dy = end[1] - start[1];
    return std::sqrt(dx * dx + dy * dy);
}

// Assignment operator
Segment &Segment::operator=(const Segment &other)
{
    if (this != &other)
    {
        start = other.start;
        end = other.end;
        std::cout << "    [Segment] Assignment operator" << std::endl;
    }
    return *this;
}
