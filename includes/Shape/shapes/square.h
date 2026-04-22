#pragma once
#include "rectangle.h"
#include "diamond.h"

// DIAMOND INHERITANCE: Square extends both Rectangle and Diamond with virtual inheritance
// This solves the diamond problem: both Rectangle and Diamond inherit from Shape
// With virtual inheritance, Shape is constructed only once
class Square : public Rectangle, public Diamond
{
public:
    // Default constructor with initialization list - creates square vertices
    Square(float side = 0.0f);

    // Copy constructor with initialization list
    Square(const Square &other);

    // Virtual clone method for polymorphic deep copying
    virtual Shape* clone() const override;

    // Destructor
    virtual ~Square();

    // Assignment operator
    Square &operator=(const Square &other);

    // Getters
    float getSide() const { return Rectangle::getWidth(); }
    
    // Override getArea using Rectangle (since width == height for square)
    float getArea() const { return getSide() * getSide(); }

    // Print info showing properties from both parent classes
    void printInfo() const;

    // Static factory method - creates and initializes a Square dynamically
    static Shape *create();
};
