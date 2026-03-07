#pragma once
#include <iostream>
class Point{
    private:
        float* coord; // vector cu 2 element [0]=x [1]=y;
        static int contPct; // tine minte cate puncte s-au creat
        const unsigned int id; // id unic al fiecarui punct
    public:
        Point(); // creeaza un punct in (0,0)
        Point(float x, float y); //creeaza un punct P cu coordonatele (x,y)
        Point(float i); // creeaza un punct P cu coordonatele (i,i)
        Point(int g); // creeaza un punct P aflat la 1 u.m(unitate de masura) de centru astfel incat unghiul dintre OP si OX sa fie g grade
        ~Point();

        Point(const Point& other); // copy constructor
        Point& operator=(const Point& other);
        
        Point operator+(const Point& other) const;
        Point operator-(const Point& other) const;
        float& operator[](unsigned int index);
        float operator[](unsigned int index) const; // pentru a putea folosi in functii in care exista parametrul const Point&

        friend std::ostream& operator<<(std::ostream& out, const Point& other);
        friend std::istream& operator>>(std::istream& in,Point& other);
        
        const float* getCoord() const;
        void setCoord( float x, float y);

        Point& operator++(); // prefixat
        Point operator++(int); //postfixat

        bool operator==(const Point& other) const;
        bool operator<(const Point& other) const;
        
};