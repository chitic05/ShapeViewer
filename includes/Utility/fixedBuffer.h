#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

#include "Math/point.h"
#include "customExceptions.h"

template <typename T, std::size_t N>
class FixedBuffer
{
private:
    std::vector<T> data;

public:
    FixedBuffer()
    {
        data.reserve(N);
    }

    ~FixedBuffer() noexcept = default;

    void push(const T &value)
    {
        if (data.size() >= N)
            throw std::overflow_error("FixedBuffer overflow: capacity exceeded");
        data.push_back(value);
    }

    T pop()
    {
        if (data.empty())
            throw std::underflow_error("FixedBuffer underflow: buffer is empty");
        T value = data.back();
        data.pop_back();
        return value;
    }

    T &at(std::size_t index)
    {
        if (index >= data.size())
            throw std::out_of_range("FixedBuffer index out of range");
        return data[index];
    }

    const T &at(std::size_t index) const
    {
        if (index >= data.size())
            throw std::out_of_range("FixedBuffer index out of range");
        return data[index];
    }

    T &operator[](std::size_t index)
    {
        return data[index];
    }

    const T &operator[](std::size_t index) const
    {
        return data[index];
    }

    std::size_t capacity() const
    {
        return N;
    }

    std::size_t count() const
    {
        return data.size();
    }

    bool empty() const
    {
        return data.empty();
    }

    void clear()
    {
        data.clear();
    }

    void eraseID(unsigned int id)
    {
        auto oldSize = data.size();
        auto newEnd = std::remove_if(data.begin(), data.end(),
                                     [id](const T &value) {
                                         return value && value->getId() == id;
                                     });
        data.erase(newEnd, data.end());
        if (data.size() == oldSize)
            throw ElementNotFoundException(id, "FixedBuffer id not found");
    }

    T *begin()
    {
        return data.data();
    }

    T *end()
    {
        return data.data() + data.size();
    }

    const T *begin() const
    {
        return data.data();
    }

    const T *end() const
    {
        return data.data() + data.size();
    }

    template <typename U>
    FixedBuffer<U, N> convert() const
    {
        FixedBuffer<U, N> result;
        for (const auto &value : data)
            result.push(static_cast<U>(value));
        return result;
    }
};

template <typename T, std::size_t N>
T sumBuffer(const FixedBuffer<T, N> &buffer)
{
    T sum{};
    for (const auto &value : buffer)
        sum = sum + value;
    return sum;
}

template <typename Container, typename T>
int findIndex(const Container &container, const T &value)
{
    int index = 0;
    for (const auto &item : container)
    {
        if (item == value)
            return index;
        ++index;
    }
    return -1;
}

template <typename T>
std::string toDebugString(const T &value)
{
    std::ostringstream out;
    out << value;
    return out.str();
}

// Specialization
template <>
inline std::string toDebugString<Point>(const Point &value)
{
    std::ostringstream out;
    out << "Point(x=" << value.getCoord()[0] << ", y=" << value.getCoord()[1] << ")";
    return out.str();
}
