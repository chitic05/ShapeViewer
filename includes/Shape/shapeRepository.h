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
    // vector: O(1) push_back, O(n) remove/erase, O(1) indexed access
    std::vector<Shape*> vectorShapes;
    // list: O(1) insert/erase with iterator, O(n) search
    std::list<Shape*> listShapes;
    // map: O(log n) find/insert/erase by id, keeps keys ordered
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
};
