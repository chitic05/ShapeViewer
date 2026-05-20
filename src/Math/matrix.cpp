#include "Math/matrix.h"
#include <cmath>
#include <stdexcept>

Matrix::Matrix(const Point &p) : rows(3), cols(1)
{
    data.assign(rows, std::vector<float>(cols, 0.0f));
    data[0][0] = p[0];
    data[1][0] = p[1];
    data[2][0] = 1.0f;
}

Matrix::Matrix() : rows(0), cols(0)
{
    data.clear();
}

Matrix::Matrix(unsigned int i, unsigned int j) : rows(i), cols(j)
{
    data.assign(rows, std::vector<float>(cols, 0.0f));
}

Matrix::Matrix(unsigned int i, unsigned int j, float val) : rows(i), cols(j)
{
    data.assign(rows, std::vector<float>(cols, val));
}

Matrix::Matrix(unsigned int n) : rows(n), cols(n)
{
    data.assign(rows, std::vector<float>(cols, 0.0f));
    for (unsigned int k = 0; k < rows; ++k)
        data[k][k] = 1.0f;
}

Matrix::~Matrix() noexcept = default;

Matrix::Matrix(const Matrix &other)
{
    rows = other.rows;
    cols = other.cols;
    data = other.data;
}

Matrix &Matrix::operator=(const Matrix &other)
{
    if (this == &other)
        return *this;
    rows = other.rows;
    cols = other.cols;
    data = other.data;
    return *this;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        throw std::invalid_argument("Matrix addition requires matching dimensions");
    }

    Matrix result = Matrix(rows, cols);
    if (!data.empty() && !other.data.empty())
    {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = this->data[i][j] + other.data[i][j];
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
    {
        throw std::invalid_argument("Matrix subtraction requires matching dimensions");
    }

    Matrix result = Matrix(rows, cols);
    if (!data.empty() && !other.data.empty())
    {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = this->data[i][j] - other.data[i][j];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (cols != other.rows)
    {
        throw std::invalid_argument("Matrix multiplication requires matching inner dimensions");
    }

    Matrix result = Matrix(rows, other.cols);
    if (!data.empty() && !other.data.empty())
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < other.cols; ++j)
            {
                float sum = 0;
                for (int k = 0; k < cols; ++k)
                {
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
    }
    return result;
}

Point Matrix::operator*(const Point &other) const
{
    Matrix v(3, 1);
    v[0][0] = other[0];
    v[1][0] = other[1];
    v[2][0] = 1.0f;

    Matrix res = (*this) * v;
    return Point(res[0][0], res[1][0]);
}

const float *Matrix::operator[](unsigned int index) const
{
    if (data.empty())
    {
        throw std::runtime_error("Matrix is uninitialized");
    }

    if (index >= rows)
    {
        throw std::out_of_range("Matrix row index out of bounds");
    }

    return data[index].data();
}

float *Matrix::operator[](unsigned int index)
{
    if (data.empty())
    {
        throw std::runtime_error("Matrix is uninitialized");
    }

    if (index >= rows)
    {
        throw std::out_of_range("Matrix row index out of bounds");
    }

    return data[index].data();
}

std::ostream &operator<<(std::ostream &out, const Matrix &other)
{
    for (int i = 0; i < other.rows; ++i)
    {
        for (int j = 0; j < other.cols; ++j)
            out << other.data[i][j] << ' ';
        out << '\n';
    }
    return out;
}

std::istream &operator>>(std::istream &in, Matrix &other)
{
    in >> other.rows >> other.cols;
    other.data.assign(other.rows, std::vector<float>(other.cols, 0.0f));
    for (int i = 0; i < other.rows; ++i)
        for (int j = 0; j < other.cols; ++j)
            in >> other.data[i][j];

    return in;
}

Matrix Matrix::genTranslateMatrix(float x, float y)
{
    Matrix transform(3);
    transform[0][2] = x;
    transform[1][2] = y;
    return transform;
}

Matrix Matrix::genRotateMatrix(float grade)
{
    Matrix rotate(3);
    const float PI = 3.14159265358979323846f;
    float rad = grade * PI / 180.0f;
    float c = cosf(rad);
    float s = sinf(rad);

    if (fabs(c) < 1e-6)
        c = 0.0f;
    if (fabs(s) < 1e-6)
        s = 0.0f;

    rotate[0][0] = c;
    rotate[0][1] = -s;
    rotate[1][0] = s;
    rotate[1][1] = c;
    return rotate;
}

Matrix Matrix::genScaleMatrix(float scale)
{
    Matrix result(3);
    for (int i = 0; i < 2; ++i)
        result[i][i] = scale;
    return result;
}

Matrix &Matrix::operator++()
{
    for (unsigned int i = 0; i < rows; ++i)
    {
        for (unsigned int j = 0; j < cols; ++j)
            data[i][j]++;
    }
    return *this;
}

Matrix Matrix::operator++(int)
{
    Matrix ret = *this;
    for (unsigned int i = 0; i < rows; ++i)
    {
        for (unsigned int j = 0; j < cols; ++j)
            data[i][j]++;
    }
    return ret;
}

bool Matrix::operator==(const Matrix &other) const
{
    return rows == other.rows && cols == other.cols;
}

bool Matrix::operator<(const Matrix &other) const
{
    return rows < other.rows || cols == other.cols;
}