#include "Math/point.h"
#include <cmath>

int Point::contPct = 0;

Point::Point():id(++contPct){
    coord = new float[2]{0,0};
}

Point::Point(float x, float y):id(++contPct){
    coord = new float[2]{x,y};
}

Point::Point(float i):id(++contPct){
    coord = new float[2]{i, i};
}

Point::Point(int g):id(++contPct){
 const float PI = 3.14159265358979323846f;
    float rad = g * PI / 180.0f;
    
    float c = cosf(rad);
    float s = sinf(rad);

    // Aplicăm pragul (Epsilon) pentru a forța valorile mici la 0
    if (fabs(c) < 1e-6) c = 0.0f;
    if (fabs(s) < 1e-6) s = 0.0f;
    coord = new float[2]{c, s};
}

Point::~Point(){
    if(coord)
        delete[] coord;
}

Point::Point(const Point& other):id(other.id){
    coord = new float[2]{other.coord[0], other.coord[1]};
}

Point& Point::operator=(const Point& other){
    if(this == &other)
        return *this; //daca avem p1=p1 si nu folosim acest 'if' 
                    //vom avea probleme din cauza delete-ului de mai jos
    if(coord)
        delete[] coord;
     coord = new float[2]{other.coord[0], other.coord[1]};
     return *this;
}

Point Point::operator+(const Point& other) const{
    return Point(coord[0]+other.coord[0], coord[1]+other.coord[1]);
}
Point Point::operator-(const Point& other) const{
    return Point(coord[0]-other.coord[0], coord[1]-other.coord[1]);
}

float& Point::operator[](unsigned int index){
    if(index == 0) return coord[0];
    if(index == 1) return coord[1];
    else std::cerr << "This index doesn't exist";
    return coord[0];
}

float Point::operator[](unsigned int index) const{
    if(index == 0) return coord[0];
    if(index == 1) return coord[1];
    else std::cerr << "This index doesn't exist";
    return coord[0];
}


std::ostream& operator<<(std::ostream& out, const Point& other){
    out << "ID[" << other.id << "] x: " << other.coord[0] << ", y: " << other.coord[1];
    return out;
}
std::istream& operator>>(std::istream& in, Point& other){
    in >> other.coord[0] >> other.coord[1];
    return in;
}

const float* Point::getCoord() const{
    return coord;
}

void Point::setCoord(float x, float y){
    if(coord){
        coord[0] = x;
        coord[1] = y;
    }
}