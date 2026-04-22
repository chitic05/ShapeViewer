#pragma once
#include "../shape.h"
#include <cmath>

// IS-A: Diamond extends Shape (inheritance hierarchy) - VIRTUAL for diamond inheritance
class Diamond : virtual public Shape
{
protected:
    float diagonal1;  // First diagonal
    float diagonal2;  // Second diagonal

public:
    // Default constructor with initialization list - creates diamond vertices from diagonals
    Diamond(float d1 = 0.0f, float d2 = 0.0f);

    // Copy constructor with initialization list
    Diamond(const Diamond &other);

    // Virtual clone method for polymorphic deep copying
    virtual Shape* clone() const override;

    // Destructor
    virtual ~Diamond();

    // Assignment operator
    Diamond &operator=(const Diamond &other);

    float getDiagonal1() const { return diagonal1; }
    float getDiagonal2() const { return diagonal2; }
    float getArea() const { return (diagonal1 * diagonal2) / 2.0f; }
    
    float getPerimeter() const
    {
        float side = std::sqrt((diagonal1/2)*(diagonal1/2) + (diagonal2/2)*(diagonal2/2));
        return 4 * side;
    }

    // Static factory method - creates and initializes a Diamond dynamically
    static Shape *create();
};
