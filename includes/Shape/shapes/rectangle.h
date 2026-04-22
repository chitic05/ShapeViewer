#pragma once
#include "../shape.h"

// IS-A: Rectangle extends Shape (inheritance hierarchy) - VIRTUAL for diamond inheritance
class Rectangle : virtual public Shape
{
protected:
    float width;
    float height;

public:
    // Default constructor with initialization list - creates rectangle vertices from dimensions
    Rectangle(float w = 0.0f, float h = 0.0f);

    // Copy constructor with initialization list
    Rectangle(const Rectangle &other);

    // Virtual clone method for polymorphic deep copying
    virtual Shape* clone() const override;

    // Destructor
    virtual ~Rectangle();

    // Assignment operator
    Rectangle &operator=(const Rectangle &other);

    float getWidth() const { return width; }
    float getHeight() const { return height; }
    float getArea() const { return width * height; }

    // Static factory method - creates and initializes a Rectangle dynamically
    static Shape *create();
};
