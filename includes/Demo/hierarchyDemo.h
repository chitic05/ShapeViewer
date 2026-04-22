#pragma once
#include "Shape/shapes/rectangle.h"
#include "Shape/shapes/diamond.h"
#include "Shape/shapes/square.h"
#include <iostream>

void demonstrateInheritance()
{
    std::cout << "\n========== IS-A INHERITANCE HIERARCHY ==========\n" << std::endl;

    // Level 1: Rectangle (Shape -> Rectangle)
    std::cout << "--- Creating Rectangle ---" << std::endl;
    Rectangle rect(10.0f, 20.0f);
    std::cout << "  Width: " << rect.getWidth() << ", Height: " << rect.getHeight() << std::endl;
    std::cout << "  Area: " << rect.getArea() << std::endl;
    std::cout << std::endl;

    // Level 1: Diamond (Shape -> Diamond)
    std::cout << "--- Creating Diamond ---" << std::endl;
    Diamond diamond(12.0f, 8.0f);
    std::cout << "  Diagonal 1: " << diamond.getDiagonal1() << ", Diagonal 2: " << diamond.getDiagonal2() << std::endl;
    std::cout << "  Area: " << diamond.getArea() << std::endl;
    std::cout << "  Perimeter: " << diamond.getPerimeter() << std::endl;
    std::cout << std::endl;

    std::cout << "========== DIAMOND INHERITANCE PATTERN ==========\n" << std::endl;

    // Level 2: Square (Shape -> Rectangle + Diamond with virtual inheritance)
    std::cout << "--- Creating Square (extends both Rectangle and Diamond) ---" << std::endl;
    Square square(15.0f);
    std::cout << "  Side: " << square.getSide() << std::endl;
    std::cout << "  Area (Square formula): " << square.getArea() << std::endl;
    square.printInfo();
    std::cout << std::endl;

    // Copy constructor demonstration
    std::cout << "--- Copy Constructor: Square squareCopy = square ---" << std::endl;
    Square squareCopy = square;
    std::cout << std::endl;

    std::cout << "========== OBJECT DESTRUCTION (reverse order) ==========\n" << std::endl;
}
