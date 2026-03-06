#pragma once
#include "Math/point.h"
#include "Math/matrix.h"
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
    public:
        Shape();
        Shape(unsigned int num,Point* vertices, Color color, const char* name);
        Shape(unsigned int num,Point* vertices);
        Shape(unsigned int num,Point* vertices, const char* name);
        ~Shape();

        Shape(const Shape& other);
        Shape& operator=(const Shape& other);

        Point& operator[](unsigned int index);

        const Point& operator[](unsigned int index) const;
        friend Shape operator*(const Matrix& matrix,const Shape& shape);

        friend std::ostream& operator<<(std::ostream& out, const Shape& shape);
        friend std::istream& operator>>(std::istream& in, Shape& shape);
        //+, ++, ==, <

};