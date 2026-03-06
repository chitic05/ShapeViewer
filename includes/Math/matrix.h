#pragma once
#include <iostream>
#include "Math/point.h"
class Matrix{
    private:
        float **data;
        unsigned int rows, cols;
    public:
        Matrix();
        Matrix(const Point& p);//Matricea care reprezinta un punct pentru a-l putea transforma folosing alte matrici
        Matrix(unsigned int i, unsigned int j); // face o matrice de i randuri si j coloane umpluta cu 0
        Matrix(unsigned int i, unsigned int j, float val); //Face o matrice cu i randuri si j coloane si o umple cu val
        Matrix(unsigned int n); //Matrice identitate cu n coloane si n randrui
        ~Matrix();

        Matrix(const Matrix& other);
        Matrix& operator=(const Matrix& other);

        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;
        Point operator*(const Point& other) const;

        const float* operator[](unsigned int index) const;
        float* operator[](unsigned int index);

        friend std::ostream& operator<<(std::ostream& out, const Matrix& other);
        friend std::istream& operator>>(std::istream& in, Matrix& other);

        static Matrix genTranslateMatrix(float x,float y);
        static Matrix genRotateMatrix(float grade);
        static Matrix genScaleMatrix(float scale); // sa-l implementz
        //++, ==, <
};