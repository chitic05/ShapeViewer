# ShapeViewer

A C++ application for managing and visualizing geometric shapes with SDL3.

## Requirements

- CMake (3.10+)
- C++17 compiler (GCC/Clang)
- SDL3 (included in `externals/`)

## Build

```bash
# Create the build directory if it doesn't exist
mkdir -p build
cd build

# Configure the project in Release mode
cmake .. -DCMAKE_BUILD_TYPE=Release

# Compile
cmake --build .
```

### Optional: Debug Build

```bash
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

### Note for Multi-Config Generators

If you use a multi-config generator (for example Visual Studio), configure normally and select
the build configuration at build time:

```bash
cmake -S . -B build
cmake --build build --config Release
```

## Run

```bash
./build/ShapeViewer
```

## Application Structure

### Main Pages

1. **Main Page** - The main menu with 5 options:
   - Add shape
   - Delete shape
   - Modify shape
   - Display shapes
   - Exit

2. **Add Page** - Adds new shapes:
   - Enter number of vertices
   - Coordinates for each vertex
   - Color selection

3. **Delete Page** - Deletes shapes by ID:
   - Displays the list of existing shapes
   - Prompts for the shape ID to delete

4. **Modify Page** - Geometric transformations:
   - Rotation around the shape center
   - Scaling relative to the center
   - Translation (movement)

5. **Print Page** - Shape visualization:
   - Lists all shapes with details
   - SDL graphical view with ID-based selection

### Main Classes

- **Shape** - Base class for all geometric shapes
  - Manages vertices, color, and ID
  - Pure virtual methods for derived classes
  - Uses virtual inheritance to resolve diamond problem

- **Rectangle** - Inherits virtually from Shape
  - Defined by width and height
  - 4 vertices aligned to axes

- **Diamond** - Inherits virtually from Shape
  - Defined by two diagonals (diagonal1, diagonal2)
  - 4 vertices forming a rotated square

- **Square** - Multiple inheritance from Rectangle and Diamond
  - Combines properties of both Rectangle and Diamond
  - Uses virtual inheritance to resolve diamond problem
  - Demonstrates the diamond inheritance pattern

- **ShapeManager** - Manages the collection of shapes
  - Polymorphic storage via Shape* pointers
  - Filtering by type using `dynamic_cast` and `typeid`

- **PageManager** - Controls navigation between pages

- **Point** - 2D point for coordinates
  - Supports arithmetic operations (+, -)
  - Array indexing with operator[]

- **Matrix** - Matrix operations for transformations

- **Segment** - Demonstrates HAS-A composition
  - Contains two Point objects (not pointers)
  - Shows initializer list usage: `Segment(Point s, Point e) : start(s), end(e)`
  - Calculates distance between two points

### Shape Inheritance Hierarchy (Diamond Pattern)

```
        Shape (virtual base)
         /   \
        /     \
    Rectangle Diamond
        \     /
         \   /
         Square
```

**Virtual Inheritance Explanation:**
- Both `Rectangle` and `Diamond` inherit virtually from `Shape`
- `Square` inherits from both `Rectangle` and `Diamond`
- Without virtual inheritance, `Square` would have TWO copies of `Shape` (diamond problem)
- With virtual inheritance, `Square` has only ONE copy of `Shape`
- Constructor calls must explicitly invoke the virtual base: `Shape::Shape(other)`

## C++ Features Demonstrated

- **Inheritance & Virtual Methods** - Shape hierarchy with virtual functions
- **Virtual Inheritance** - Square inherits from both Rectangle and Diamond (diamond problem resolution)
- **Polymorphism** - Downcasting with `dynamic_cast` and type checking with `typeid`
- **RTTI (Runtime Type Information)** - Type identification at runtime
- **Access Control** - Private/Protected/Public members with detailed documentation
- **Composition (HAS-A)** - Segment class demonstrates object composition
- **Initializer Lists** - Proper member initialization in constructors
- **Copy Semantics** - Copy constructors and assignment operators
- **final Keyword** - Preventing further inheritance on concrete classes
- **Virtual Inheritance** - Resolving diamond inheritance pattern in Shape hierarchy

