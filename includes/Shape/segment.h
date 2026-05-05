#pragma once

#include "Math/point.h"

// Demonstrare compunere (HAS-A) cu inițializare prin lista de inițializare
// Segment CONTINE doua obiecte Point (not pointeri)
class Segment
{
private:
    Point start; 
    Point end;    

public:

    // Lista de inițializare: start(s), end(e) - initializeaza membrii INAINTE de corp
    Segment(Point s, Point e);

    // Constructor cu coordonate directe
    Segment(int x1, int y1, int x2, int y2);

    // Copy constructor cu inițializare prin lista
    Segment(const Segment &other);

    // Destructor
    ~Segment();

    // Getters
    Point getStart() const;
    Point getEnd() const;

    // Calculate length
    double getLength() const;

    // Assignment operator
    Segment &operator=(const Segment &other);
};

