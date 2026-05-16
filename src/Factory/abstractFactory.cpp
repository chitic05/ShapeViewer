#include "Factory/abstractFactory.h"
#include "Shape/shapes/rectangle.h"
#include "Shape/shapes/square.h"
#include "Shape/shapes/diamond.h"
#include "Shape/shapes/rightTriangle.h"
#include "Shape/shapes/equilateralTriangle.h"
#include <stdexcept>

static Patrulater *safePatrulater(Shape *shape, const char *factoryName)
{
    Patrulater *patr = dynamic_cast<Patrulater *>(shape);
    if (!patr)
    {
        delete shape;
        throw std::runtime_error(std::string(factoryName) + " failed to create a patrulater");
    }
    return patr;
}

static Triangle *safeTriangle(Shape *shape, const char *factoryName)
{
    Triangle *tri = dynamic_cast<Triangle *>(shape);
    if (!tri)
    {
        delete shape;
        throw std::runtime_error(std::string(factoryName) + " failed to create a triangle");
    }
    return tri;
}

Patrulater *PerpendicularFactory::createPatrulater()
{
    return safePatrulater(Rectangle::create(), "PerpendicularFactory");
}

Triangle *PerpendicularFactory::createTriangle()
{
    return safeTriangle(RightTriangle::create(), "PerpendicularFactory");
}

Patrulater *EqualFactory::createPatrulater()
{
    return safePatrulater(Square::create(), "EqualFactory");
}

Triangle *EqualFactory::createTriangle()
{
    return safeTriangle(EquilateralTriangle::create(), "EqualFactory");
}

Patrulater *RombFactory::createPatrulater()
{
    return safePatrulater(Diamond::create(), "RombFactory");
}

Triangle *RombFactory::createTriangle()
{
    return safeTriangle(EquilateralTriangle::create(), "RombFactory");
}
