#include "Math/point.h"
#include "customExceptions.h"
#include <cmath>
#include <stdexcept>

static void validateCoord(float value, int index)
{
    if (!std::isfinite(value))
        throw InvalidCoordinateException(value, index, "Coordinate must be finite");
}

int Point::contPct = 0;

Point::Point() : id(++contPct), coord{0.0f, 0.0f}
{
}

Point::Point(float x, float y) : id(++contPct), coord{0.0f, 0.0f}
{
    validateCoord(x, 0);
    validateCoord(y, 1);
    coord[0] = x;
    coord[1] = y;
}

Point::Point(float i) : id(++contPct), coord{0.0f, 0.0f}
{
    validateCoord(i, 0);
    validateCoord(i, 1);
    coord[0] = i;
    coord[1] = i;
}

Point::Point(int g) : id(++contPct), coord{0.0f, 0.0f}
{
    const float PI = 3.14159265358979323846f;
    float rad = g * PI / 180.0f;
    float c = cosf(rad);
    float s = sinf(rad);

    if (fabs(c) < 1e-6)
        c = 0.0f;
    if (fabs(s) < 1e-6)
        s = 0.0f;

    coord[0] = c;
    coord[1] = s;
}

Point::~Point() noexcept = default;

Point::Point(const Point &other) : id(other.id), coord(other.coord)
{
}

Point &Point::operator=(const Point &other)
{
    if (this == &other)
        return *this;

    coord = other.coord;
    return *this;
}

Point Point::operator+(const Point &other) const
{
    return Point(coord[0] + other.coord[0], coord[1] + other.coord[1]);
}

Point Point::operator-(const Point &other) const
{
    return Point(coord[0] - other.coord[0], coord[1] - other.coord[1]);
}

float &Point::operator[](unsigned int index)
{
    if (index == 0)
        return coord[0];
    if (index == 1)
        return coord[1];
    throw std::out_of_range("Point index out of bounds");
}
float Point::operator[](unsigned int index) const
{
    if (index == 0)
        return coord[0];

    if (index == 1)
        return coord[1];
    throw std::out_of_range("Point index out of bounds");
}

std::ostream &operator<<(std::ostream &out, const Point &other)
{
    out << "ID[" << other.id << "] x: " << other.coord[0] << ", y: " << other.coord[1];
    return out;
}

std::istream &operator>>(std::istream &in, Point &other)
{
    in >> other.coord[0] >> other.coord[1];
    return in;
}

const float *Point::getCoord() const
{
    return coord.data();
}

void Point::setCoord(float x, float y)
{
    validateCoord(x, 0);
    validateCoord(y, 1);
    coord[0] = x;
    coord[1] = y;
}

Point &Point::operator++()
{
    coord[0]++;
    coord[1]++;
    return *this;
}

Point Point::operator++(int)
{
    Point ret = *this;
    coord[0]++;
    coord[1]++;
    return ret;
}

bool Point::operator==(const Point &other) const
{
    return coord[0] == other.coord[0] && coord[1] == other.coord[1];
}

bool Point::operator<(const Point &other) const
{
    if (coord[0] != other.coord[0])
        return coord[0] < other.coord[0];
    else
        return coord[1] < other.coord[1];
}