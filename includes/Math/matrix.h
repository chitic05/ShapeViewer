#pragma once
#include "Math/point.h"
#include <iostream>

class Matrix
{
private:
    // Matricea de date [rows][cols]
    float **data;

    // Dimensiunile matricei
    unsigned int rows, cols;

public:
    // Face o matrice goala (0x0)
    Matrix();

    // Face un vector coloana din punct (x,y,1)
    Matrix(const Point &p);

    // Face o matrice i x j cu tot cu 0
    Matrix(unsigned int i, unsigned int j);

    // Face o matrice i x j plina cu val
    Matrix(unsigned int i, unsigned int j, float val);

    // Face o matrice identitate n x n
    Matrix(unsigned int n);

    // Destructorul pentru a nu avea pierderi de memorie
    ~Matrix();

    // Copy constructor
    Matrix(const Matrix &other);

    Matrix &operator=(const Matrix &other);

    // Aduna doua matrici
    Matrix operator+(const Matrix &other) const;

    // Scade doua matrici
    Matrix operator-(const Matrix &other) const;

    // Inmulteste doua matrici
    Matrix operator*(const Matrix &other) const;

    // Aplica transformarea pe un punct
    Point operator*(const Point &other) const;

    // Acces const la un rand din matrice
    const float *operator[](unsigned int index) const;

    // Acces modificabil la un rand din matrice
    float *operator[](unsigned int index);

    // Afiseaza matricea
    friend std::ostream &operator<<(std::ostream &out, const Matrix &other);

    // Citeste matricea
    friend std::istream &operator>>(std::istream &in, Matrix &other);

    // Genereaza matrice de translatie cu (x,y)
    static Matrix genTranslateMatrix(float x, float y);

    // Genereaza matrice de rotatie cu grade grade
    static Matrix genRotateMatrix(float grade);

    // Genereaza matrice de scalare cu factor scale
    static Matrix genScaleMatrix(float scale);

    // Incrementeaza toate elementele (prefixat)
    Matrix &operator++();

    // Incrementeaza toate elementele (postfixat)
    Matrix operator++(int);

    // Daca au aceleasi dimensiuni
    bool operator==(const Matrix &other) const;

    bool operator<(const Matrix &other) const;
};