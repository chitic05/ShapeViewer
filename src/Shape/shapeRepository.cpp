#include "Shape/shapeRepository.h"
#include "customExceptions.h"
#include <iostream>

ShapeRepository::~ShapeRepository()
{
    for (auto shape : vectorShapes) {
        delete shape;
    }
    vectorShapes.clear();
    listShapes.clear();
    mapShapesById.clear();
}

// CREATE - Adauga forma in toate containerele
void ShapeRepository::addShape(Shape* shape)
{
    if (!shape)
        throw std::invalid_argument("Cannot add null shape");

    // Duplicat dupa operator== (in proiect, == compara ID-ul)
    for (const auto& existing : vectorShapes) {
        if (existing && (*existing == *shape))
            throw std::runtime_error("Duplicate shape detected");
    }
    
    vectorShapes.push_back(shape);
    listShapes.push_back(shape);
    mapShapesById[shape->getId()] = shape;
}

// READ - Cauta forma dupa ID in map
Shape* ShapeRepository::findShapeById(unsigned int id) const
{
    auto it = mapShapesById.find(id);
    if (it == mapShapesById.end())
        throw ElementNotFoundException(id, "Shape with ID not found");
    return it->second;
}

// READ - Acceseaza forma la index din vector
Shape* ShapeRepository::getShapeAt(unsigned int index) const
{
    if (index >= vectorShapes.size())
        throw std::out_of_range("Shape index out of bounds");
    return vectorShapes[index];
}

// READ - Returneaza referinta la vector (pentru iterare)
const std::vector<Shape*>& ShapeRepository::getAllShapes() const
{
    return vectorShapes;
}

// READ - Algoritm: copy_if pentru a filtra dupa culoare
std::vector<Shape*> ShapeRepository::findShapesByColor(Color color) const
{
    std::vector<Shape*> result;
    
    std::copy_if(vectorShapes.begin(), vectorShapes.end(),
                 std::back_inserter(result),
                 [color](Shape* shape) { return shape->getColor() == color; });
    
    return result;
}

// READ - Algoritm: count_if pentru a numara forme cu aria > minArea
int ShapeRepository::countShapesWithAreaGreaterThan(float minArea) const
{
    return std::count_if(vectorShapes.begin(), vectorShapes.end(),
                         [minArea](Shape* shape) { 
                             return shape->getPerimeter() > minArea; 
                         });
}

// DELETE - Idiomul erase-remove_if pentru vector
// si remove_if pentru list
void ShapeRepository::removeShapeById(unsigned int id)
{
    auto it = mapShapesById.find(id);
    if (it == mapShapesById.end())
        throw ElementNotFoundException(id, "Shape with ID not found");
    
    const std::pair<const unsigned int, Shape*>& entry = *it;
    auto [foundId, shapeToRemove] = entry;
    
    // Erase-remove idiom pentru vector
    vectorShapes.erase(
        std::remove_if(vectorShapes.begin(), vectorShapes.end(),
                      [id](Shape* s) { return s->getId() == id; }),
        vectorShapes.end()
    );
    
    // Remove_if pentru list
    listShapes.remove_if([id](Shape* s) { return s->getId() == id; });
    
    mapShapesById.erase(it);
    delete shapeToRemove;
}

// READ - Algoritm: for_each pentru a afisa toate formele
void ShapeRepository::printAllShapes() const
{
    std::cout << "\n========== All Shapes in Repository ==========\n";
    std::cout << "Total shapes (vector): " << vectorShapes.size() << "\n";
    std::cout << "Total shapes (list): " << listShapes.size() << "\n";
    std::cout << "Total shapes (map): " << mapShapesById.size() << "\n\n";
    
    std::cout << "Shapes (using for_each algoritm):\n";
    int index = 0;
    std::for_each(vectorShapes.begin(), vectorShapes.end(),
                  [&index](Shape* shape) {
                      std::cout << "[" << (++index) << "] ID=" << shape->getId() 
                                << ", Perimeter=" << shape->getPerimeter() << "\n";
                  });
}

// UPDATE - Algoritm: sort cu comparator lambda
void ShapeRepository::sortShapesByPerimeter()
{
    std::sort(vectorShapes.begin(), vectorShapes.end(),
              [](Shape* a, Shape* b) {
                  return a->getPerimeter() < b->getPerimeter();
              });
    
    std::cout << "\nShapes sorted by perimeter (ascending):\n";
    std::for_each(vectorShapes.begin(), vectorShapes.end(),
                  [](Shape* shape) {
                      std::cout << "  ID=" << shape->getId()
                                << ", Perimeter=" << shape->getPerimeter() << "\n";
                  });
}
