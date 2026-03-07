#pragma once
#include "Math/point.h"
#include "Math/matrix.h"

struct SDL_Renderer;

enum class Color{
    RED,
    BLUE,
    GREEN
};
class Shape{
    private:
        Point* vertices; // Un array cu toate punctele care definesc forma
        unsigned int numVertices; // Numarul de puncte din array
        Color color;
        static unsigned int newestId;
        unsigned int id;
        char* name;
        Point getCentre() const;
    public:
        Shape();
        Shape(unsigned int num,Point* vertices, Color color, const char* name);
        Shape(unsigned int num,Point* vertices);
        Shape(unsigned int num,Point* vertices, const char* name);
        
        // Constructors with center position
        Shape(unsigned int num, Point* vertices, Color color, const char* name, float centerX, float centerY);
        Shape(unsigned int num, Point* vertices, float centerX, float centerY);
        Shape(unsigned int num, Point* vertices, const char* name, float centerX, float centerY);
        
        ~Shape();

        Shape(const Shape& other);
        Shape& operator=(const Shape& other);

        Point& operator[](unsigned int index);// read+write
        const Point& operator[](unsigned int index) const; //read only

        Shape operator+(const float) const; //s-o fac comutativa;
        friend Shape operator*(const Matrix& matrix,const Shape& shape);
        
        friend std::ostream& operator<<(std::ostream& out, const Shape& shape);
        friend std::istream& operator>>(std::istream& in, Shape& shape);

        Shape& operator++(); // prefixat
        Shape operator++(int); //postfixat

        bool operator==(const Shape& other) const;
        bool operator<(const Shape& other) const;

        unsigned int getId() const;
};