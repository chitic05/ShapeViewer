# Proiect-1-POO

Aplicație C++ pentru gestionarea și vizualizarea formelor geometrice cu SDL3.

## Cerințe

- CMake (3.10+)
- Compilator C++17 (GCC/Clang)
- SDL3 (inclus în `externals/`)

## Compilare

```bash
# Creează directorul build dacă nu există
mkdir -p build
cd build

# Configurează proiectul
cmake ..

# Compilează
cmake --build .
```

## Rulare

```bash
./build/Shapes
```

## Structura Aplicației

### Pagini Principale

1. **Main Page** - Meniul principal cu 5 opțiuni:
   - Adaugă formă
   - Șterge formă
   - Modifică formă
   - Afișează forme
   - Ieșire

2. **Add Page** - Adaugă forme noi:
   - Introducere număr de vârfuri
   - Coordonate pentru fiecare vârf
   - Selectare culoare

3. **Delete Page** - Șterge forme după ID:
   - Afișează lista formelor existente
   - Solicită ID-ul formei de șters

4. **Modify Page** - Transformări geometrice:
   - Rotație în jurul centrului formei
   - Scalare față de centru
   - Translație (deplasare)

5. **Print Page** - Vizualizare forme:
   - Listează toate formele cu detalii
   - Vizualizare grafică SDL cu selecție după ID

### Clase Principale

- **Shape** - Reprezentarea unei forme geometrice (poligon)
- **ShapeManager** - Gestionează colecția de forme
- **PageManager** - Controlează navigarea între pagini
- **Point** - Punct 2D pentru coordonate
- **Matrix** - Operații matriceale pentru transformări