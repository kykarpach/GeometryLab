# GeometryLab

GeometryLab — учебная библиотека вычислительной геометрии на C++20.

Проект сделан для практики C++, CMake, структуры библиотеки, тестирования и базовых алгоритмов геометрии.

## Что реализовано

- `Vec2` — двумерный вектор
- `Vec3` — трехмерный вектор
- `Segment2` — отрезок на плоскости
- `Segment3` — отрезок в пространстве
- `AABB2` — ограничивающий прямоугольник на плоскости
- `Polygon2` — многоугольник на плоскости
- пересечение 2D-отрезков
- пересечение 3D-отрезков
- расстояния:
  - между точками
  - от точки до отрезка
  - от точки до прямой
  - между прямыми
- построение выпуклой оболочки на плоскости

## Сборка

Нужны:

- компилятор с поддержкой C++20
- CMake 3.20 или новее

Команды сборки:

```bash
cmake -S . -B build
cmake --build build
```

## Запуск демо

Windows:

```bash
.\build\demo.exe
```

Linux/macOS:

```bash
./build/demo
```

## Запуск тестов

Windows:

```bash
.\build\tests.exe
```

Linux/macOS:

```bash
./build/tests
```

## Структура проекта

```text
include/geometry/   заголовочные файлы библиотеки
src/                реализации
tests/              тесты
examples/           пример использования
CMakeLists.txt      конфигурация сборки
```

## Пример использования

```cpp
#include "geometry/Vec2.h"
#include "geometry/Segment2.h"
#include "geometry/Distance.h"

#include <iostream>

int main() {
    geom::Vec2 p(3.0, 4.0);

    geom::Segment2 segment(
        geom::Vec2(0.0, 0.0),
        geom::Vec2(10.0, 0.0)
    );

    std::cout << geom::distance_point_segment(p, segment) << '\n';

    return 0;
}
```
