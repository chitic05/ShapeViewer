#pragma once
#include "../shape.h"
#include "Factory/abstractFactory.h"

class RightTriangle : public Triangle
{
protected:
    float legA;
    float legB;

public:
    RightTriangle(float a = 0.0f, float b = 0.0f);
    RightTriangle(const RightTriangle &other);

    Shape *clone() const override;
    std::string toString() const override;

    ~RightTriangle() noexcept override;

    RightTriangle &operator=(const RightTriangle &other);

    float getLegA() const { return legA; }
    float getLegB() const { return legB; }
    float getArea() const { return (legA * legB) / 2.0f; }

    static Shape *create();
};
