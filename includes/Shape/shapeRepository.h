#pragma once
#include "shape.h"
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <stdexcept>

class ShapeRepository
{
private:
    std::vector<Shape*> vectorShapes;
    std::list<Shape*> listShapes;
    std::map<unsigned int, Shape*> mapShapesById;

public:
    ShapeRepository() = default;
    ~ShapeRepository();

    void addShape(Shape* shape);
    Shape* findShapeById(unsigned int id) const;
    Shape* getShapeAt(unsigned int index) const;
    const std::vector<Shape*>& getAllShapes() const;
    std::vector<Shape*> findShapesByColor(Color color) const;
    int countShapesWithAreaGreaterThan(float minArea) const;
    void removeShapeById(unsigned int id);
    void printAllShapes() const;
    void sortShapesByPerimeter();
    int getTotalShapeCount() const;
    ShapeRepository clone() const;
    
    void demonstrateCRUD();
    void demonstrateAlgorithms();
};
