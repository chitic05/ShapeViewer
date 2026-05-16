#pragma once
#include "../shape.h"
#include "Factory/abstractFactory.h"
#include <cmath>

class EquilateralTriangle : public Triangle
{
protected:
    float side;

public:
    EquilateralTriangle(float s = 0.0f);
    EquilateralTriangle(const EquilateralTriangle &other);

    Shape *clone() const override;
    std::string toString() const override;

    ~EquilateralTriangle() override;

    EquilateralTriangle &operator=(const EquilateralTriangle &other);

    float getSide() const { return side; }
    float getArea() const { return (side * side * std::sqrt(3.0f)) / 4.0f; }

    static Shape *create();
};
