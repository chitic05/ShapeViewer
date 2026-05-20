#include "Shape/shapeManager.h"
#include "Page/pageManager.h"
#include "customExceptions.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "Shape/shapes/diamond.h"
#include "Shape/shapes/rectangle.h"
#include "Shape/shapes/square.h"

ShapeManager::ShapeManager()
    : name("Default"), maxCapacity(1000)
{
    std::cout << "[ShapeManager] Constructed (Default, capacity=" << maxCapacity << ")\n";
}

ShapeManager::ShapeManager(const std::string& n, unsigned int capacity)
    : name(n), maxCapacity(capacity)
{
    std::cout << "[ShapeManager] Constructed (" << name << ", capacity=" << maxCapacity << ")\n";
}

ShapeManager::ShapeManager(const std::string& n)
    : name(n), maxCapacity(1000)
{
    std::cout << "[ShapeManager] Constructed (" << name << ", capacity=" << maxCapacity << ")\n";
}

ShapeManager::ShapeManager(unsigned int capacity)
    : name("Default"), maxCapacity(capacity)
{
    std::cout << "[ShapeManager] Constructed (Default, capacity=" << maxCapacity << ")\n";
}

ShapeManager::ShapeManager(const ShapeManager &other)
    : name(other.name), maxCapacity(other.maxCapacity)
{
    std::cout << "[ShapeManager] Copy constructed (" << name << ")\n";
    repository = other.repository.clone();
}

ShapeManager &ShapeManager::operator=(const ShapeManager &other)
{
    if (this == &other)
        return *this;

    name = other.name;
    maxCapacity = other.maxCapacity;
    repository = other.repository.clone();

    return *this;
}

ShapeManager::~ShapeManager() noexcept
{
    std::cout << "[ShapeManager] Destructed (" << name << ")\n";
    if (PageManager::getInstance().getSM() == this)
        PageManager::getInstance().getSM() = nullptr;
}

Shape *ShapeManager::operator[](unsigned int index)
{
    return repository.getShapeAt(index);
}

const Shape *ShapeManager::operator[](unsigned int index) const
{
    return repository.getShapeAt(index);
}

ShapeManager ShapeManager::operator+(Shape* shape) const
{
    ShapeManager result = *this;

    if (!shape)
        throw std::invalid_argument("Cannot add null shape");

    if (result.repository.getTotalShapeCount() >= result.maxCapacity)
        throw CapacityException(result.maxCapacity, result.repository.getTotalShapeCount() + 1,
                                shape->getId(), "ShapeManager capacity exceeded");

    result.repository.addShape(shape);
    return result;
}

ShapeManager &ShapeManager::operator+=(Shape* shape)
{
    if (!shape)
        throw std::invalid_argument("Cannot add null shape");

    if (repository.getTotalShapeCount() >= maxCapacity)
        throw CapacityException(maxCapacity, repository.getTotalShapeCount() + 1,
                                shape->getId(), "ShapeManager capacity exceeded");

    repository.addShape(shape);
    return *this;
}

ShapeManager ShapeManager::operator-(unsigned int id) const
{
    ShapeManager result(name, maxCapacity);
    
    for (const auto& shape : repository.getAllShapes()) {
        if (shape->getId() != id) {
            result.repository.addShape(shape->clone());
        }
    }
    
    return result;
}

ShapeManager &ShapeManager::operator-=(unsigned int id)
{
    try {
        repository.removeShapeById(id);
    } catch (const ElementNotFoundException&) {
        // Ignore if shape not found
    }
    
    return *this;
}

ShapeManager &ShapeManager::operator++()
{
    std::for_each(repository.getAllShapes().begin(), repository.getAllShapes().end(),
                 [](Shape* s) { ++(*s); });
    return *this;
}

ShapeManager ShapeManager::operator++(int)
{
    ShapeManager temp = *this;
    ++(*this);
    return temp;
}

bool ShapeManager::operator==(const ShapeManager &other) const
{
    if (repository.getTotalShapeCount() != other.repository.getTotalShapeCount())
    {
        return false;
    }

    for (const auto& shape : repository.getAllShapes()) {
        auto found = std::find_if(other.repository.getAllShapes().begin(), 
                                 other.repository.getAllShapes().end(),
                                 [shape](Shape* s) { return *shape == *s; });
        if (found == other.repository.getAllShapes().end()) {
            return false;
        }
    }

    return true;
}

bool ShapeManager::operator<(const ShapeManager &other) const
{
    return repository.getTotalShapeCount() < other.repository.getTotalShapeCount();
}

std::ostream &operator<<(std::ostream &out, const ShapeManager &sm)
{
    out << "========================================\n";
    out << "Shape Manager: " << sm.name << "\n";

    out << "Total shapes: " << sm.repository.getTotalShapeCount() << "\n";
    out << "========================================\n";

    if (sm.repository.getTotalShapeCount() == 0)
    {
        out << "  (No shapes)\n";
    }
    else
    {
        out << "    ID | Name      | Color      | Vertices | Coordinates\n";
        out << "----------------------------------------\n";

        int i = 1;
        for (const auto& shape : sm.repository.getAllShapes()) {
            out << "[" << i++ << "] " << *shape << "\n";
        }
    }
    out << "========================================\n";
    return out;
}

std::istream &operator>>(std::istream &in, ShapeManager &sm)
{
    std::cout << "Enter number of shapes: ";
    unsigned int newCount;

    in >> newCount;

    // Clear by creating new repository
    sm.repository = ShapeRepository();

    for (unsigned int i = 0; i < newCount && i < sm.maxCapacity; ++i) {
        std::cout << "Shape " << (i + 1) << ":\n";

        Shape temp;
        in >> temp;

        sm.repository.addShape(new Shape(temp));
    }

    return in;
}

unsigned int ShapeManager::getCount() const
{
    return repository.getTotalShapeCount();
}

const std::string& ShapeManager::getName() const
{
    return name;
}

ShapeRepository& ShapeManager::getRepository()
{
    return repository;
}

const ShapeRepository& ShapeManager::getRepository() const
{
    return repository;
}

void ShapeManager::printAllRectangles() const
{
    std::for_each(repository.getAllShapes().begin(), repository.getAllShapes().end(),
                 [](const Shape* shape) {
                     Rectangle* rect = dynamic_cast<Rectangle*>(const_cast<Shape*>(shape));
                     if (rect != nullptr) {
                         std::cout << *shape << "\n";
                     }
                 });
}

void ShapeManager::printAllDiamonds() const
{
    std::for_each(repository.getAllShapes().begin(), repository.getAllShapes().end(),
                 [](const Shape* shape) {
                     Diamond* dia = dynamic_cast<Diamond*>(const_cast<Shape*>(shape));
                     if (dia != nullptr) {
                         std::cout << *shape << "\n";
                     }
                 });
}

void ShapeManager::printAllSquares() const
{
    std::for_each(repository.getAllShapes().begin(), repository.getAllShapes().end(),
                 [](const Shape* shape) {
                     Square* sq = dynamic_cast<Square*>(const_cast<Shape*>(shape));
                     if (sq != nullptr) {
                         std::cout << *shape << "\n";
                     }
                 });
}