#include <iostream>
#include "Page/pageManager.h"
#include "Shape/shape.h"

int main(){
    Point* vertices = new Point[3]{
        Point(1,0),
        Point(0,1),
        Point(-1,0)
    };
    Shape s(3, vertices);

    Matrix m = Matrix::genRotateMatrix(180);
    s=m*s;

    std::cout << s;
}