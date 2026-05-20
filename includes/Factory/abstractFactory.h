#pragma once
#include "Shape/shape.h"

class Patrulater : virtual public Shape
{
public:
    virtual ~Patrulater() noexcept = default;
};

class Triangle : virtual public Shape
{
public:
    virtual ~Triangle() noexcept = default;
};

class IShapeFactory
{
public:
    virtual ~IShapeFactory() noexcept = default;
    virtual Patrulater *createPatrulater() = 0;
    virtual Triangle *createTriangle() = 0;
};

class PerpendicularFactory : public IShapeFactory
{
public:
    Patrulater *createPatrulater() override;
    Triangle *createTriangle() override;
};

class EqualFactory : public IShapeFactory
{
public:
    Patrulater *createPatrulater() override;
    Triangle *createTriangle() override;
};

class RombFactory : public IShapeFactory
{
public:
    Patrulater *createPatrulater() override;
    Triangle *createTriangle() override;
};