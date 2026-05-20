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

### Linux
```bash
./build/ShapeViewer
```
### Windows
```bash
.\build\Release\ShapeViewer.exe
```

```bash
.\build\Debug\ShapeViewer.exe
```


## Application Structure

### Main Pages

1. **Main Page** - The main menu with 6 options:
   - Add shape
   - Delete shape
   - Modify shape
   - Display shapes
  - View journal
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
  - Demonstrates HAS-A composition
  - Polymorphic storage via Shape* pointers
  - Filtering by type using `dynamic_cast` and `typeid`

- **PageManager** - Controls navigation between pages
  - Implemented as a Meyers Singleton (static local in `getInstance()`)
  - Copy and move operations are deleted to enforce a single instance

- **Point** - 2D point for coordinates
  - Supports arithmetic operations (+, -)
  - Array indexing with operator[]

- **Matrix** - Matrix operations for transformations

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
- **IObject Interface** - Unique IDs generated via `IObject` base
- **Singleton (Meyers)** - `PageManager` centralizes page navigation and state
- **Singleton (Meyers)** - `Logger` stores journal entries
- **Abstract Factory** - `IShapeFactory` with three concrete families and two abstract products (`Patrulater`, `Triangle`)
- **Templates** - `FixedBuffer<T, N>` with vector-backed storage, exceptions, and template utilities

## STL Usage

### Containers

- `std::vector` - filtered shape results and internal storage for `FixedBuffer`
- `std::list` - stable node removals for delete operations
- `std::map` - lookup by ID
- `std::unordered_map` - page registry by key

### Algorithms

- `std::find_if` - equality checks in ShapeManager and filtered lookups
- `std::copy_if` - filter shapes by color
- `std::count_if` - count shapes by predicate
- `std::remove_if` + `erase` - erase-remove idiom on vector
- `std::for_each` - formatted printing and batch operations
- `std::sort` - perimeter-based ordering in pages and repository

### Pair / Structured Binding

- Structured binding on a map iterator to access `(id, shape)` in remove operations

## Template Requirements

- **Template class**: `FixedBuffer<T, N>` manages heap storage, uses exceptions on overflow/underflow, and lives in [includes/Utility/fixedBuffer.h](includes/Utility/fixedBuffer.h)
- **Template method inside template class**: `convert<U>()` converts buffer element types with independent template parameter
- **Free template functions**: `sumBuffer` and `findIndex` used in repository logic
- **Full specialization**: `toDebugString<Point>` for cleaner point output (documented in code)
- **Non-type template parameter**: `FixedBuffer<T, N>` uses `N` as compile-time capacity

