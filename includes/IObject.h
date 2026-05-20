#pragma once
#include <ostream>
#include <string>

class IObject
{
protected:
    inline static unsigned int nextId = 0;
    unsigned int id;

public:
    IObject() : id(++nextId)
    {
    }

    IObject(const IObject&) : id(++nextId)
    {
    }

    IObject& operator=(const IObject&)
    {
        return *this;
    }

    virtual ~IObject() noexcept = default;

    unsigned int getId() const noexcept
    {
        return id;
    }

    virtual std::string toString() const = 0;

    friend bool operator<(const IObject& left, const IObject& right)
    {
        return left.getId() < right.getId();
    }

    friend bool operator==(const IObject& left, const IObject& right)
    {
        return left.getId() == right.getId();
    }

    friend std::ostream& operator<<(std::ostream& out, const IObject& obj)
    {
        out << obj.toString();
        return out;
    }
};
