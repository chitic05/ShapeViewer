#pragma once
#include <iostream>

class Point{
    private:
        //[0]=X [1]=Y
        float* coord; 
        
        //Tine minte cate puncte au fost create in total
        static int contPct;
        
        //Id-ul unic al fiecarui punct
        const unsigned int id;
        
    public:
        //Face un punct in (0,0)
        Point();
        
        //Face un punct in (x,y)
        Point(float x, float y);
        
        //Face un punct in (i,i)
        Point(float i);

        //Face un punct I astfel incat segmentul [OI] sa aiba lungimea 1 si unghiul XOI g grade
        Point(int g);
        
        //Destructorul pentru a nu avea pierderi de memorie
        ~Point();

        //Copy constructor
        Point(const Point& other);
        
        Point& operator=(const Point& other);
        
        //(x,y)+(a,b) => (x+a,y+b)
        Point operator+(const Point& other) const;
        //(x,y)-(a,b) => (x-a,y-b)
        Point operator-(const Point& other) const;
        
        //Ne o coordonata [0]-x [1]-y si putem modifica valorea
        float& operator[](unsigned int index);
        //Doar ne da coordonata nu putem modifica nimic
        float operator[](unsigned int index) const;
        //Afiseaza coordonatele si id-ul
        friend std::ostream& operator<<(std::ostream& out, const Point& other);
        //Citeste coordonatele
        friend std::istream& operator>>(std::istream& in,Point& other);
        //Getter pentru coordonate
        const float* getCoord() const;
        //Setter pentru coordonate
        void setCoord( float x, float y);
        //Incrementeaza ambele coordonate(prefixat)
        Point& operator++();
        //Incrementeaza ambele coordonate(postixat)
        Point operator++(int);
        //Daca punctele au aceleasi coordonate
        bool operator==(const Point& other) const;
    
        bool operator<(const Point& other) const;
};