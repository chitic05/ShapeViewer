#include "Shape/shapeRepository.h"
#include "Shape/shapes/rectangle.h"
#include "Shape/shapes/diamond.h"
#include "Shape/shapes/square.h"
#include <iostream>
#include <cstring>

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
    
    vectorShapes.push_back(shape);
    listShapes.push_back(shape);
    mapShapesById[shape->getId()] = shape;
}

// READ - Cauta forma dupa ID in map
Shape* ShapeRepository::findShapeById(unsigned int id) const
{
    auto it = mapShapesById.find(id);
    if (it == mapShapesById.end())
        throw std::runtime_error("Shape with ID " + std::to_string(id) + " not found");
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

// READ - Algoritm: find_if pentru a filtra dupa culoare
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
        throw std::runtime_error("Shape with ID " + std::to_string(id) + " not found");
    
    Shape* shapeToRemove = it->second;
    
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

int ShapeRepository::getTotalShapeCount() const
{
    return vectorShapes.size();
}

// Clone - Deep copy al repository-ului
ShapeRepository ShapeRepository::clone() const
{
    ShapeRepository cloned;
    for (const auto& shape : vectorShapes) {
        if (shape != nullptr) {
            cloned.addShape(shape->clone());
        }
    }
    return cloned;
}

// DEMONSTRATIE CRUD
void ShapeRepository::demonstrateCRUD()
{
    std::cout << "\n========== CERINTA 3: STL Containers & Algorithms - CRUD Demo ==========\n";
    
    std::cout << "\n[CREATE] Adding shapes...\n";
    Rectangle* rect1 = new Rectangle(4.0f, 3.0f);
    Rectangle* rect2 = new Rectangle(2.0f, 2.0f);
    Diamond* diamond1 = new Diamond(3.0f, 4.0f);
    Square* square1 = new Square(2.0f);
    
    addShape(rect1);
    addShape(rect2);
    addShape(diamond1);
    addShape(square1);
    
    std::cout << "Added 4 shapes.\n";
    
    std::cout << "\n[READ] All shapes in repository:\n";
    printAllShapes();
    
    std::cout << "\n[READ] Using find_if to find shape by ID:\n";
    try {
        Shape* found = findShapeById(rect1->getId());
        std::cout << "Found shape with ID " << found->getId() << ", Perimeter=" << found->getPerimeter() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    
    std::cout << "\n[READ] Using copy_if to find shapes by color (RED):\n";
    auto redShapes = findShapesByColor(Color::RED);
    std::cout << "Found " << redShapes.size() << " RED shapes\n";
    
    std::cout << "\n[READ] Using count_if to count shapes with perimeter > 8:\n";
    int count = countShapesWithAreaGreaterThan(8.0f);
    std::cout << "Shapes with perimeter > 8: " << count << "\n";
    
    std::cout << "\n[UPDATE] Sorting shapes by perimeter:\n";
    sortShapesByPerimeter();
    
    std::cout << "\n[DELETE] Removing shape by ID " << rect2->getId() << "...\n";
    try {
        removeShapeById(rect2->getId());
        std::cout << "Shape removed successfully.\n";
        std::cout << "Remaining shapes: " << getTotalShapeCount() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    
    std::cout << "\n[READ] Final repository state:\n";
    printAllShapes();
}

// DEMONSTRATIE ALGORITMI STL
void ShapeRepository::demonstrateAlgorithms()
{
    std::cout << "\n========== STL Algorithms Demonstration ==========\n";
    
    std::cout << "\n1. find_if - Find first shape with perimeter > 10:\n";
    auto it = std::find_if(vectorShapes.begin(), vectorShapes.end(),
                          [](Shape* s) { return s->getPerimeter() > 10.0f; });
    if (it != vectorShapes.end()) {
        std::cout << "   Found: ID=" << (*it)->getId() << ", Perimeter=" << (*it)->getPerimeter() << "\n";
    } else {
        std::cout << "   Not found\n";
    }
    
    std::cout << "\n2. count_if - Count shapes with perimeter > 7:\n";
    int cnt = std::count_if(vectorShapes.begin(), vectorShapes.end(),
                           [](Shape* s) { return s->getPerimeter() > 7.0f; });
    std::cout << "   Count: " << cnt << "\n";
    
    std::cout << "\n3. any_of - Check if any shape has perimeter < 5:\n";
    bool anySmall = std::any_of(vectorShapes.begin(), vectorShapes.end(),
                               [](Shape* s) { return s->getPerimeter() < 5.0f; });
    std::cout << "   Result: " << (anySmall ? "Yes" : "No") << "\n";
    
    std::cout << "\n4. all_of - Check if all shapes have perimeter > 0:\n";
    bool allPositive = std::all_of(vectorShapes.begin(), vectorShapes.end(),
                                  [](Shape* s) { return s->getPerimeter() > 0.0f; });
    std::cout << "   Result: " << (allPositive ? "Yes" : "No") << "\n";
    
    std::cout << "\n5. transform - Calculate all areas (with lambda):\n";
    std::vector<float> areas;
    std::transform(vectorShapes.begin(), vectorShapes.end(),
                  std::back_inserter(areas),
                  [](Shape* s) { return s->getPerimeter(); });
    
    std::cout << "   Areas: ";
    std::for_each(areas.begin(), areas.end(),
                 [](float area) { std::cout << area << " "; });
    std::cout << "\n";
    
    std::cout << "\n===== End of Algorithms Demo =====\n\n";
}
