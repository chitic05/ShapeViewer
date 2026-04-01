# ShapeViewer

A C++ application for managing and visualizing geometric shapes with SDL3.

## Requirements

- CMake (3.10+)
- Compilator C++17 (GCC/Clang)
- SDL3 (included in `externals/`)

## Build

```bash
# Create the build directory if it doesn't exist
mkdir -p build
cd build

# Configure the project
cmake ..

# Compile
cmake --build .
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

- **Shape** - Representation of a geometric shape (polygon)
- **ShapeManager** - Manages the collection of shapes
- **PageManager** - Controls navigation between pages
- **Point** - 2D point for coordinates
- **Matrix** - Matrix operations for transformations