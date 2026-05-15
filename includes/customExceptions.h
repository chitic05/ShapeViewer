#pragma once
#include <stdexcept>
#include <string>
#include <sstream>

// ============================================
// IERARHIE DE EXCEPTII CUSTOM - CERINTA 1
// ============================================

// Clasa de bază pentru toate excepţiile domeniului
class ShapeException : public std::runtime_error
{
protected:
    std::string details;  // Detalii suplimentare specifice domeniului
    int errorCode;        // Cod de eroare specific

public:
    ShapeException(const std::string& message, int code = -1)
        : std::runtime_error(message), errorCode(code)
    {
        details = message;
    }

    virtual ~ShapeException() noexcept = default;

    // Override what() cu noexcept
    const char* what() const noexcept override
    {
        return std::runtime_error::what();
    }

    // Getter pentru codul de eroare
    int getErrorCode() const noexcept
    {
        return errorCode;
    }

    // Getter pentru detalii
    const std::string& getDetails() const noexcept
    {
        return details;
    }
};

// ============================================
// EXCEPTIE 1: Coordonate invalide
// ============================================
class InvalidCoordinateException : public ShapeException
{
private:
    float invalidValue;  // Valoarea invalidă care a cauzat eroarea
    int coordinateIndex; // 0 pentru X, 1 pentru Y

public:
    InvalidCoordinateException(float value, int index, const std::string& message = "Invalid coordinate")
        : ShapeException(message, 1001), invalidValue(value), coordinateIndex(index)
    {
        std::ostringstream oss;
        oss << message << " - Invalid value: " << value
            << " at coordinate " << (index == 0 ? "X" : "Y");
        details = oss.str();
    }

    virtual ~InvalidCoordinateException() noexcept = default;

    const char* what() const noexcept override
    {
        return "InvalidCoordinateException: Invalid coordinate value detected";
    }

    // Getters specifici domeniului
    float getInvalidValue() const noexcept
    {
        return invalidValue;
    }

    int getCoordinateIndex() const noexcept
    {
        return coordinateIndex;
    }
};

// ============================================
// EXCEPTIE 2: Capacitate depășită
// ============================================
class CapacityException : public ShapeException
{
private:
    unsigned int currentCapacity;  // Capacitatea actuală
    unsigned int requestedSize;    // Dimensiunea cerută
    unsigned int affectedId;       // ID-ul formei/obiectului afectat (dacă e cazul)

public:
    CapacityException(unsigned int capacity, unsigned int requested, unsigned int id = 0,
                      const std::string& message = "Capacity limit exceeded")
        : ShapeException(message, 1002), currentCapacity(capacity), requestedSize(requested), affectedId(id)
    {
        std::ostringstream oss;
        oss << message << " - Capacity: " << capacity << ", Requested: " << requested;
        if (id != 0)
            oss << ", Affected ID: " << id;
        details = oss.str();
    }

    virtual ~CapacityException() noexcept = default;

    const char* what() const noexcept override
    {
        return "CapacityException: Container capacity limit exceeded";
    }

    // Getters specifici domeniului
    unsigned int getCurrentCapacity() const noexcept
    {
        return currentCapacity;
    }

    unsigned int getRequestedSize() const noexcept
    {
        return requestedSize;
    }

    unsigned int getAffectedId() const noexcept
    {
        return affectedId;
    }
};

// ============================================
// EXCEPTIE 3: Element negasit
// ============================================
class ElementNotFoundException : public ShapeException
{
private:
    unsigned int searchedId;       // ID-ul căutat
    std::string searchedName;      // Numele căutat (dacă e cazul)

public:
    ElementNotFoundException(unsigned int id, const std::string& message = "Element not found")
        : ShapeException(message, 1003), searchedId(id)
    {
        std::ostringstream oss;
        oss << message << " - Searched ID: " << id;
        details = oss.str();
    }

    ElementNotFoundException(const std::string& name, const std::string& message = "Element not found")
        : ShapeException(message, 1004), searchedId(0), searchedName(name)
    {
        std::ostringstream oss;
        oss << message << " - Searched name: " << name;
        details = oss.str();
    }

    virtual ~ElementNotFoundException() noexcept = default;

    const char* what() const noexcept override
    {
        return "ElementNotFoundException: Requested element not found in collection";
    }

    // Getters specifici domeniului
    unsigned int getSearchedId() const noexcept
    {
        return searchedId;
    }

    const std::string& getSearchedName() const noexcept
    {
        return searchedName;
    }
};
