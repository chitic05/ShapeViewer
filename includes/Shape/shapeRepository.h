#pragma once
#include "shape.h"
#include "Utility/fixedBuffer.h"
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <cstddef>
#include <stdexcept>

class ShapeRepository
{
private:
    static constexpr std::size_t bufferCapacity = 1024;

    // FixedBuffer: capacitate fixa, acces O(1), cu exceptii la overflow/underflow
    FixedBuffer<Shape*, bufferCapacity> bufferShapes;
    // list: O(1) insert/erase with iterator, O(n) search
    std::list<Shape*> listShapes;
    // map: O(log n) find/insert/erase by id, keeps keys ordered
    std::map<unsigned int, Shape*> mapShapesById;

public:
    ShapeRepository();
    ~ShapeRepository() noexcept;

    void addShape(Shape* shape);
    Shape* findShapeById(unsigned int id) const;
    Shape* getShapeAt(unsigned int index) const;
    const FixedBuffer<Shape*, bufferCapacity>& getAllShapes() const;
    std::vector<Shape*> findShapesByColor(Color color) const;
    int countShapesWithAreaGreaterThan(float minArea) const;
    void removeShapeById(unsigned int id);
    void printAllShapes() const;
    void sortShapesByPerimeter();
    int getTotalShapeCount() const;
    ShapeRepository clone() const;
};
