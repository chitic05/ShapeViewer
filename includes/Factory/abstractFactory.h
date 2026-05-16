#pragma once
#include "Shape/shapes/square.h"
//Produse Abstracte
class Patrulater : virtual public Shape{

};

class Triangle : virtual public Shape{

};

//Proudse concrete Dreptunghi, Romb, Patrat, Triunghi drept, echilateral si nu stiu care i a treia varianta pentru romb

//Abstract Factory
class ShapeFactory{
    public:
        virtual Patrulater* createPatrulater() = 0;
        virtual Triangle* createTriangle() = 0;
};

//concrete Factory
class FormeDrepteFactory : public ShapeFactory{
    public:
        Patrulater* createPatrulater() override {return new Rectangle();};
        //Patrulater* createTriangle() override {return new Rectangle();};
};

class FormeEgaleFactory : public ShapeFactory{
    public:
        Patrulater* createPatrulater() override {return new Square();};
        //Patrulater* createTriangle() override {return new Rectangle();};
};



//SA RENUNT LA ROMB IN MENIURI
class RombFactory : ShapeFactory{
    public:
        Patrulater* createPatrulater() override {return new Diamond;};
        //Patrulater* createTriangle() override {return new Rectangle();};
};