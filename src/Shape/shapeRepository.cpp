#include "Shape/shapeRepository.h"
#include "customExceptions.h"
#include "Utility/logger.h"
#include <iostream>
#include <sstream>

ShapeRepository::ShapeRepository()
{
    std::cout << "[ShapeRepository] Constructed\n";
}

ShapeRepository::~ShapeRepository() noexcept
{
    std::cout << "[ShapeRepository] Destructed\n";
    for (auto shape : bufferShapes) {
        delete shape;
    }
    bufferShapes.clear();
    listShapes.clear();
    mapShapesById.clear();
}

// CREATE - Adauga forma in toate containerele
void ShapeRepository::addShape(Shape* shape)
{
    if (!shape)
        throw std::invalid_argument("Cannot add null shape");

    // Duplicat dupa operator== (in proiect, == compara ID-ul)
    for (const auto& existing : bufferShapes) {
        if (existing && (*existing == *shape))
            throw std::runtime_error("Duplicate shape detected: " + toDebugString(*shape));
    }
    
    bufferShapes.push(shape);
    listShapes.push_back(shape);
    mapShapesById[shape->getId()] = shape;

    std::ostringstream out;
    out << "Added shape ID=" << shape->getId() << ": " << shape->toString();
    Logger::getInstance().log(out.str());
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
    if (index >= bufferShapes.count())
        throw std::out_of_range("Shape index out of bounds");
    return bufferShapes.at(index);
}

// READ - Returneaza referinta la vector (pentru iterare)
const FixedBuffer<Shape*, ShapeRepository::bufferCapacity>& ShapeRepository::getAllShapes() const
{
    return bufferShapes;
}

// READ - Algoritm: copy_if pentru a filtra dupa culoare
std::vector<Shape*> ShapeRepository::findShapesByColor(Color color) const
{
    std::vector<Shape*> result;
    
    std::copy_if(bufferShapes.begin(), bufferShapes.end(),
                 std::back_inserter(result),
                 [color](Shape* shape) { return shape->getColor() == color; });
    
    return result;
}

// READ - Algoritm: count_if pentru a numara forme cu aria > minArea
int ShapeRepository::countShapesWithAreaGreaterThan(float minArea) const
{
    return std::count_if(bufferShapes.begin(), bufferShapes.end(),
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
    
    try {
        bufferShapes.eraseID(id);
    } catch (const ElementNotFoundException& e) {
        std::cout << "[ShapeRepository] " << e.what() << " (ID=" << id << ")\n";
    }
    
    // Remove_if pentru list
    listShapes.remove_if([id](Shape* s) { return s->getId() == id; });
    
    mapShapesById.erase(it);
    delete shapeToRemove;

    std::ostringstream out;
    out << "Removed shape ID=" << foundId;
    Logger::getInstance().log(out.str());
}

// READ - Algoritm: for_each pentru a afisa toate formele
void ShapeRepository::printAllShapes() const
{
    std::cout << "\n========== All Shapes in Repository ==========\n";
    std::cout << "Total shapes (buffer): " << bufferShapes.count() << "\n";
    std::cout << "Total shapes (list): " << listShapes.size() << "\n";
    std::cout << "Total shapes (map): " << mapShapesById.size() << "\n\n";
    
    std::cout << "Shapes (using for_each algoritm):\n";
    int index = 0;
    std::for_each(bufferShapes.begin(), bufferShapes.end(),
                  [&index](Shape* shape) {
                      std::cout << "[" << (++index) << "] ID=" << shape->getId() 
                                << ", Perimeter=" << shape->getPerimeter() << "\n";
                  });

    FixedBuffer<float, bufferCapacity> perimeters;
    for (const auto& shape : bufferShapes)
        perimeters.push(shape->getPerimeter());
    auto perimetersAsDouble = perimeters.convert<double>();
    std::cout << "Total perimeter: " << sumBuffer(perimetersAsDouble) << "\n";
}

// UPDATE - Algoritm: sort cu comparator lambda
void ShapeRepository::sortShapesByPerimeter()
{
    std::sort(bufferShapes.begin(), bufferShapes.end(),
              [](Shape* a, Shape* b) {
                  return a->getPerimeter() < b->getPerimeter();
              });
    
    std::cout << "\nShapes sorted by perimeter (ascending):\n";
    std::for_each(bufferShapes.begin(), bufferShapes.end(),
                  [](Shape* shape) {
                      std::cout << "  ID=" << shape->getId()
                                << ", Perimeter=" << shape->getPerimeter() << "\n";
                  });
}

int ShapeRepository::getTotalShapeCount() const
{
    return static_cast<int>(bufferShapes.count());
}

ShapeRepository ShapeRepository::clone() const
{
    ShapeRepository cloned;
    for (const auto& shape : bufferShapes) {
        if (shape != nullptr) {
            cloned.addShape(shape->clone());
        }
    }
    return cloned;
}
