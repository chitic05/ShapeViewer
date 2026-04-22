#pragma once
#include "Math/matrix.h"
#include "Math/point.h"

struct SDL_Renderer;

// Culorile disponibile pentru forme
enum class Color
{
    RED,
    BLUE,
    GREEN
};

class Shape
{
protected:
    // Array-ul de varfuri ale formei
    Point *vertices;

    // Cate varfuri are forma
    unsigned int numVertices;

    // Culoarea formei
    Color color;

    // Id-ul ultimei forme create
    static unsigned int newestId;

    // Id-ul unic al acestei forme
    unsigned int id;

    // Numele formei (alocat dinamic)
    char *name;

    // Calculeaza centrul formei
    Point getCentre() const;

public:
    // Face o forma default rosie fara varfuri
    Shape();

    // Face o forma cu toate proprietatile specificate
    Shape(unsigned int num, Point *vertices, Color color, const char *name);

    // Face o forma rosie cu nume default
    Shape(unsigned int num, Point *vertices);

    // Face o forma rosie cu nume specificat
    Shape(unsigned int num, Point *vertices, const char *name);

    // Face o forma cu toate proprietatile si o muta in (centerX, centerY)
    Shape(unsigned int num, Point *vertices, Color color, const char *name, float centerX,
          float centerY);

    // Face o forma rosie cu nume default si o muta
    Shape(unsigned int num, Point *vertices, float centerX, float centerY);

    // Face o forma rosie cu nume specificat si o muta
    Shape(unsigned int num, Point *vertices, const char *name, float centerX, float centerY);

    // Virtual destructor for proper polymorphic cleanup
    virtual ~Shape();

    // Copy constructor
    Shape(const Shape &other);

    // Virtual clone method for polymorphic deep copying
    virtual Shape* clone() const;

    Shape &operator=(const Shape &other);

    // Acces la un varf al formei (modificabil)
    Point &operator[](unsigned int index);

    // Acces const la un varf al formei
    const Point &operator[](unsigned int index) const;

    // Adauga un offset la toate varfurile
    Shape operator+(const float) const;

    // Aplica o transformare matriceala pe forma
    friend Shape operator*(const Matrix &matrix, const Shape &shape);

    // Afiseaza forma (nume, culoare, varfuri)
    friend std::ostream &operator<<(std::ostream &out, const Shape &shape);

    // Citeste forma de la utilizator
    friend std::istream &operator>>(std::istream &in, Shape &shape);

    // Incrementeaza toate varfurile (prefixat)
    Shape &operator++();

    // Incrementeaza toate varfurile (postfixat)
    Shape operator++(int);

    // Daca formele au acelasi ID
    bool operator==(const Shape &other) const;

    // Compara dupa numar de varfuri
    bool operator<(const Shape &other) const;

    // Returneaza ID-ul formei
    unsigned int getId() const;

    // Returneaza numarul de varfuri
    unsigned int getCount() const;

    // Returneaza culoarea formei
    Color getColor() const;

    float getPerimeter();

    // Static factory method - creates and initializes a Shape dynamically
    static Shape *create();
};