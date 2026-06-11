#include <cassert>
#include "C:\Users\777\Desktop\Proga\C++\GeometryLab\include\geometry\Vec2.h"

int main() {
    geom::Vec2 v(1.0, 2.0);

    assert(v.x() == 1.0);
    assert(v.y() == 2.0);

    return 0;
}