#include "Math/matrix.h"
#include <cmath>
Matrix::Matrix(const Point& p):rows(3),cols(1){
    data = new float*[rows];
    for(int i=0;i<rows;++i){
        data[i] = new float[cols];
    }
    data[0][0]=p[0]; // sa fac un getter;
    data[1][0]=p[1]; // sa fac un getter
    data[2][0]=1.0f;
}

Matrix::Matrix():rows(0),cols(0){
    data = nullptr;
}

Matrix::Matrix(unsigned int i, unsigned int j):rows(i),cols(j){
    data = new float*[rows];
    for(unsigned int k = 0; k<rows;++k){
        data[k] = new float[cols]{}; //{} initializeaza cu 0
    }
}

Matrix::Matrix(unsigned int i, unsigned int j, float val):rows(i),cols(j){
    data = new float*[rows];
    for(unsigned int k = 0; k<rows;++k){
        data[k] = new float[cols];
        for(unsigned int l = 0;l<cols; l++){
            data[k][l] = val;
        }
    }
}

Matrix::Matrix(unsigned int n):rows(n),cols(n){
    data = new float*[rows];
    for(unsigned int k = 0; k<rows;++k){
        data[k] = new float[cols]{};
        data[k][k] = 1;
    }
}

Matrix::~Matrix(){
    if(data){
        for(int i=0;i<rows;++i)
            if(data[i])
                delete[] data[i];
        delete[] data;
    }
    
}

Matrix::Matrix(const Matrix& other){
    rows = other.rows;
    cols = other.cols;
    data=new float*[other.rows];
    for(int i = 0;i<other.rows;++i){
        data[i] = new float[cols];
        for(int j=0;j<other.cols;++j)
            data[i][j] = other.data[i][j];
    }
}

Matrix& Matrix::operator=(const Matrix& other){
    if(this == &other) // verifica daca sunt aceleasi obiecte
        return *this;
    if(data){
        for(int i=0;i<rows;++i)
            if(data[i])
                delete[] data[i];
        delete[] data;
    }//stergem data veche si o rescriem cu valorile din other
    rows = other.rows;
    cols = other.cols;
    data=new float*[other.rows];
    for(int i = 0;i<other.rows;++i){
        data[i] = new float[cols];
        for(int j=0;j<other.cols;++j)
            data[i][j] = other.data[i][j];
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const{
    if(rows != other.rows || cols != other.cols){
        std::cerr << "Nu se poate face aceasta adunare\n";
        return Matrix();
    }
    Matrix result = Matrix(rows,cols);//facem matricea resultata(este initializata cu 0)
    if(data && other.data){
        for(int i=0;i<rows;++i)
            for(int j=0;j<cols;++j)
                result.data[i][j] = this->data[i][j] + other.data[i][j];
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const{
    if(rows != other.rows || cols != other.cols){
        std::cerr << "Nu se poate face aceasta scadere\n";
        return Matrix();
    }
    Matrix result = Matrix(rows,cols);//facem matricea resultata(este initializata cu 0)
    if(data && other.data){
        for(int i=0;i<rows;++i)
            for(int j=0;j<cols;++j)
                result.data[i][j] = this->data[i][j] - other.data[i][j];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const{
    if(cols != other.rows){
        std::cerr << "Nu se poate face aceasta inmultire\n";
        return Matrix();
    }
    Matrix result = Matrix(rows, other.cols);
    if(data && other.data){
        for (int i = 0; i < rows; ++i) { // parcurgem randurile lui A
            for (int j = 0; j < other.cols; ++j) { // parcurgem coloanele lui B
                // Aici calculam elementul result[i][j]
                float sum = 0;
                for (int k = 0; k < cols; ++k) { // k merge pe "latimea" comuna
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
    }
    return result;
}

Point Matrix::operator*(const Point& other) const {
    // 1. Cream vectorul coloana omogen (x, y, 1)
    Matrix v(3,1);
    v[0][0] = other[0]; // x
    v[1][0] = other[1]; // y
    v[2][0] = 1.0f;                // 1

    // 2. Inmultim Matricea (3x3) cu Vectorul (3x1)
    // Rezultatul 'res' va fi o matrice 3x1
    Matrix res = (*this) * v;

    // 3. Extragem noile coordonate si returnam un Punct NOU
    return Point(res[0][0], res[1][0]);
}

const float* Matrix::operator[](unsigned int index) const {
    // 1. Verificăm dacă matricea are memorie alocată
    if (data == nullptr) {
        std::cerr << "Eroare: Matrice neinitializata!\n";
        return nullptr; 
    }

    // 2. Verificăm dacă indexul cerut este valid (nu ieșim din matrice)
    if (index >= rows) {
        std::cerr << "Eroare: Indexul " << index << " este in afara limitelor (rows: " << rows << ")\n";
        return nullptr;
    }

    // 3. Returnăm rândul direct
    return data[index];
}

float* Matrix::operator[](unsigned int index){
    // 1. Verificăm dacă matricea are memorie alocată
    if (data == nullptr) {
        std::cerr << "Eroare: Matrice neinitializata!\n";
        return nullptr; 
    }

    // 2. Verificăm dacă indexul cerut este valid (nu ieșim din matrice)
    if (index >= rows) {
        std::cerr << "Eroare: Indexul " << index << " este in afara limitelor (rows: " << rows << ")\n";
        return nullptr;
    }

    // 3. Returnăm rândul direct
    return data[index];
}

std::ostream& operator<<(std::ostream& out, const Matrix& other){
    for(int i=0;i<other.rows;++i){
        for(int j=0;j<other.cols;++j)
            out << other.data[i][j] << ' ';
        out << '\n';
    }
    return out;
}
std::istream& operator>>(std::istream& in, Matrix& other){
    if(other.data){
        for(int i=0;i<other.rows;++i)
            if(other.data[i]) delete[] other.data[i];
    }
    if(other.data)
        delete[] other.data;

    in >> other.rows >> other.cols;
    other.data = new float*[other.rows];
    for(int i=0;i<other.rows;++i){
        other.data[i] = new float[other.cols];
        for(int j=0;j<other.cols;++j)
                    in >> other.data[i][j];
    }
        
    return in;
}

Matrix Matrix::genTranslateMatrix(float x, float y){
    Matrix transform(3);
    transform[0][2] = x;
    transform[1][2] = y;
    return transform;
}

Matrix Matrix::genRotateMatrix(float grade){
    Matrix rotate(3);
    const float PI = 3.14159265358979323846f;
    float rad = grade * PI / 180.0f;
    
    float c = cosf(rad);
    float s = sinf(rad);

    // Aplicăm pragul (Epsilon) pentru a forța valorile mici la 0
    if (fabs(c) < 1e-6) c = 0.0f;
    if (fabs(s) < 1e-6) s = 0.0f;
    
    rotate[0][0] = c;
    rotate[0][1] = -s;
    rotate[1][0] = s;
    rotate[1][1] = c;
    return rotate;
}

Matrix Matrix::genScaleMatrix(float scale){
    Matrix result(3);
    for(int i = 0;i<2;++i)
        result[i][i] = scale;
    return result;
}

Matrix& Matrix::operator++(){
    for(unsigned int i = 0; i<rows;++i){
        for(unsigned int j = 0;j<cols;++j)
            data[i][j]++;
    }
    return *this;
}
Matrix Matrix::operator++(int){
    Matrix ret = *this;
    for(unsigned int i = 0; i<rows;++i){
        for(unsigned int j = 0;j<cols;++j)
            data[i][j]++;
    }
    return ret;
}

bool Matrix::operator==(const Matrix& other) const{
    return rows == other.rows && cols == other.cols;
}
bool Matrix::operator<(const Matrix& other) const{
    return rows < other.rows || cols == other.cols;

}