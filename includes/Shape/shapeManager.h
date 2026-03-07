#pragma once
#include "Shape/shape.h"

struct SDL_Renderer;

class ShapeManager{
    private:
        Shape* shapes;
        unsigned int count;
        unsigned int capacity;
    public:
        ShapeManager();
        ShapeManager(const Shape* shapes, unsigned int c, unsigned int cap);
        ShapeManager(const Shape* shapes, unsigned int c);
        ShapeManager(unsigned int c);
        
        ShapeManager(const ShapeManager& other);
        ShapeManager& operator=(const ShapeManager& other);

        ~ShapeManager();

        // Operators
        Shape& operator[](unsigned int index);
        const Shape& operator[](unsigned int index) const;
        
        ShapeManager operator+(const Shape& shape) const;
        ShapeManager operator-(unsigned int id) const;
        
        ShapeManager& operator++();
        ShapeManager operator++(int);
        
        bool operator==(const ShapeManager& other) const;
        bool operator<(const ShapeManager& other) const;
        
        friend std::ostream& operator<<(std::ostream& out, const ShapeManager& sm);
        friend std::istream& operator>>(std::istream& in, ShapeManager& sm);
        
};