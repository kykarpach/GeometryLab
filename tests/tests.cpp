// Тест создан нейросетью. Автор проекта не ручается за полноту и идеальную корректность этих тестов.
#include "geometry/IntersectionResult3.h"
#include "geometry/IntersectionResult2.h"
#include "geometry/Distance.h"
#include "geometry/Segment3.h"
#include "geometry/Segment2.h"
#include "geometry/Vec2.h"
#include "geometry/Epsilon.h"
#include <cassert>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include "geometry/Vec3.h"
#include <optional>

using namespace geom;

void test_intersection_result3() {
    using namespace geom;

    IntersectionResult3 none = IntersectionResult3::none();

    assert(none.type == IntersectionType3::None);
    assert(!none.point.has_value());
    assert(!none.segment.has_value());

    Vec3 p(2.0, 3.0, 4.0);
    IntersectionResult3 point = IntersectionResult3::point_result(p);

    assert(point.type == IntersectionType3::Point);
    assert(point.point.has_value());
    assert(!point.segment.has_value());
    assert(geom::nearly_equal(point.point->x(), 2.0));
    assert(geom::nearly_equal(point.point->y(), 3.0));
    assert(geom::nearly_equal(point.point->z(), 4.0));

    Segment3 s(Vec3(1.0, 1.0, 1.0), Vec3(4.0, 4.0, 4.0));
    IntersectionResult3 segment = IntersectionResult3::segment_result(s);

    assert(segment.type == IntersectionType3::Segment);
    assert(!segment.point.has_value());
    assert(segment.segment.has_value());
    assert(geom::nearly_equal(segment.segment->start().x(), 1.0));
    assert(geom::nearly_equal(segment.segment->start().y(), 1.0));
    assert(geom::nearly_equal(segment.segment->start().z(), 1.0));
    assert(geom::nearly_equal(segment.segment->end().x(), 4.0));
    assert(geom::nearly_equal(segment.segment->end().y(), 4.0));
    assert(geom::nearly_equal(segment.segment->end().z(), 4.0));
}

void test_intersection_result2() {
    using namespace geom;

    IntersectionResult2 none = IntersectionResult2::none();

    assert(none.type == IntersectionType2::None);
    assert(!none.point.has_value());
    assert(!none.segment.has_value());

    Vec2 p(2.0, 3.0);
    IntersectionResult2 point = IntersectionResult2::point_result(p);

    assert(point.type == IntersectionType2::Point);
    assert(point.point.has_value());
    assert(!point.segment.has_value());
    assert(geom::nearly_equal(point.point->x(), 2.0));
    assert(geom::nearly_equal(point.point->y(), 3.0));

    Segment2 s(Vec2(1.0, 1.0), Vec2(4.0, 4.0));
    IntersectionResult2 segment = IntersectionResult2::segment_result(s);

    assert(segment.type == IntersectionType2::Segment);
    assert(!segment.point.has_value());
    assert(segment.segment.has_value());
    assert(geom::nearly_equal(segment.segment->start().x(), 1.0));
    assert(geom::nearly_equal(segment.segment->start().y(), 1.0));
    assert(geom::nearly_equal(segment.segment->end().x(), 4.0));
    assert(geom::nearly_equal(segment.segment->end().y(), 4.0));
}


void test_distance() {

    assert(geom::nearly_equal(distance(Vec2(0.0, 0.0), Vec2(3.0, 4.0)), 5.0));
    assert(geom::nearly_equal(distance(Vec3(0.0, 0.0, 0.0), Vec3(1.0, 2.0, 2.0)), 3.0));

    Segment2 horizontal2(Vec2(0.0, 0.0), Vec2(10.0, 0.0));

    assert(geom::nearly_equal(distance_point_segment(Vec2(3.0, 4.0), horizontal2), 4.0));
    assert(geom::nearly_equal(distance_point_segment(Vec2(0.0, 5.0), horizontal2), 5.0));
    assert(geom::nearly_equal(distance_point_segment(Vec2(10.0, 5.0), horizontal2), 5.0));

    assert(geom::nearly_equal(
        distance_point_segment(Vec2(-3.0, 4.0), horizontal2),
        5.0
    ));

    assert(geom::nearly_equal(
        distance_point_segment(Vec2(13.0, 4.0), horizontal2),
        5.0
    ));

    assert(geom::nearly_equal(
        distance_point_segment(Vec2(5.0, 0.0), horizontal2),
        0.0
    ));

    Segment2 degenerate2(Vec2(2.0, 3.0), Vec2(2.0, 3.0));

    assert(geom::nearly_equal(
        distance_point_segment(Vec2(5.0, 7.0), degenerate2),
        5.0
    ));

    Segment3 horizontal3(Vec3(0.0, 0.0, 0.0), Vec3(10.0, 0.0, 0.0));

    assert(geom::nearly_equal(
        distance_point_segment(Vec3(3.0, 4.0, 0.0), horizontal3),
        4.0
    ));

    assert(geom::nearly_equal(
        distance_point_segment(Vec3(3.0, 0.0, 4.0), horizontal3),
        4.0
    ));

    assert(geom::nearly_equal(
        distance_point_segment(Vec3(-3.0, 4.0, 0.0), horizontal3),
        5.0
    ));

    assert(geom::nearly_equal(
        distance_point_segment(Vec3(13.0, 4.0, 0.0), horizontal3),
        5.0
    ));

    assert(geom::nearly_equal(
        distance_point_segment(Vec3(5.0, 0.0, 0.0), horizontal3),
        0.0
    ));

    Segment3 degenerate3(Vec3(1.0, 2.0, 3.0), Vec3(1.0, 2.0, 3.0));

    assert(geom::nearly_equal(
        distance_point_segment(Vec3(3.0, 4.0, 4.0), degenerate3),
        3.0
    ));
}


void test_segment3() {

    Segment3 segment(Vec3(1.0, 2.0, 3.0), Vec3(4.0, 6.0, 15.0));

    assert(geom::nearly_equal(segment.start().x(), 1.0));
    assert(geom::nearly_equal(segment.start().y(), 2.0));
    assert(geom::nearly_equal(segment.start().z(), 3.0));

    assert(geom::nearly_equal(segment.end().x(), 4.0));
    assert(geom::nearly_equal(segment.end().y(), 6.0));
    assert(geom::nearly_equal(segment.end().z(), 15.0));

    Vec3 direction = segment.direction();
    assert(geom::nearly_equal(direction.x(), 3.0));
    assert(geom::nearly_equal(direction.y(), 4.0));
    assert(geom::nearly_equal(direction.z(), 12.0));

    assert(geom::nearly_equal(segment.length(), 13.0));
    assert(geom::nearly_equal(segment.length2(), 169.0));
    assert(!segment.is_degenerate());

    Segment3 diagonal(
        Vec3(0.0, 0.0, 0.0),
        Vec3(4.0, 4.0, 4.0)
    );

    assert(diagonal.contains_point(Vec3(2.0, 2.0, 2.0)));
    assert(diagonal.contains_point(Vec3(0.0, 0.0, 0.0)));
    assert(diagonal.contains_point(Vec3(4.0, 4.0, 4.0)));

    assert(!diagonal.contains_point(Vec3(5.0, 5.0, 5.0)));
    assert(!diagonal.contains_point(Vec3(-1.0, -1.0, -1.0)));
    assert(!diagonal.contains_point(Vec3(2.0, 2.0, 3.0)));

    Segment3 degenerate(
        Vec3(2.0, 3.0, 4.0),
        Vec3(2.0, 3.0, 4.0)
    );

    assert(degenerate.is_degenerate());
    assert(degenerate.contains_point(Vec3(2.0, 3.0, 4.0)));
    assert(!degenerate.contains_point(Vec3(2.0, 3.0, 5.0)));
}

void test_segment2() {

    Segment2 segment(Vec2(1.0, 2.0), Vec2(4.0, 6.0));

    assert(nearly_equal(segment.start().x(), 1.0));
    assert(nearly_equal(segment.start().y(), 2.0));
    assert(nearly_equal(segment.end().x(), 4.0));
    assert(nearly_equal(segment.end().y(), 6.0));

    Vec2 direction = segment.direction();
    assert(nearly_equal(direction.x(), 3.0));
    assert(nearly_equal(direction.y(), 4.0));

    assert(nearly_equal(segment.length(), 5.0));
    assert(nearly_equal(segment.length2(), 25.0));
    assert(!segment.is_degenerate());

    Segment2 degenerate(Vec2(2.0, 2.0), Vec2(2.0, 2.0));
    assert(degenerate.is_degenerate());
    assert(degenerate.contains_point(Vec2(2.0, 2.0)));
    assert(!degenerate.contains_point(Vec2(2.0, 3.0)));

    Segment2 diagonal(Vec2(0.0, 0.0), Vec2(4.0, 4.0));

    assert(diagonal.contains_point(Vec2(2.0, 2.0)));
    assert(diagonal.contains_point(Vec2(0.0, 0.0)));
    assert(diagonal.contains_point(Vec2(4.0, 4.0)));

    assert(!diagonal.contains_point(Vec2(5.0, 5.0)));
    assert(!diagonal.contains_point(Vec2(-1.0, -1.0)));
    assert(!diagonal.contains_point(Vec2(2.0, 3.0)));
}

int main() {
    
    
    test_intersection_result2();
    test_intersection_result3();
    test_distance();
    test_segment3();
    test_segment2();
    // Конструкторы и доступ к координатам
    {
        geom::Vec2 v;
        assert(nearly_equal(v.x(), 0.0));
        assert(nearly_equal(v.y(), 0.0));
    }

    {
        geom::Vec2 v(3.0, 4.0);
        assert(nearly_equal(v.x(), 3.0));
        assert(nearly_equal(v.y(), 4.0));
    }

    // Длина
    {
        geom::Vec2 v(3.0, 4.0);
        assert(nearly_equal(v.length2(), 25.0));
        assert(nearly_equal(v.length(), 5.0));
    }

    // Скалярное и 2D-векторное произведение
    {
        geom::Vec2 a(3.0, 4.0);
        geom::Vec2 b(1.0, 2.0);

        assert(nearly_equal(a.dot(b), 11.0));
        assert(nearly_equal(a.cross(b), 2.0));
    }

    // Нормализация
    {
        geom::Vec2 v(3.0, 4.0);
        geom::Vec2 n = v.normalized();

        assert(nearly_equal(n.x(), 0.6));
        assert(nearly_equal(n.y(), 0.8));
        assert(nearly_equal(n.length(), 1.0));
    }

    // operator[]
    {
        geom::Vec2 v(1.0, 2.0);

        assert(nearly_equal(v[0], 1.0));
        assert(nearly_equal(v[1], 2.0));

        v[0] = 10.0;
        v[1] = 20.0;

        assert(nearly_equal(v.x(), 10.0));
        assert(nearly_equal(v.y(), 20.0));
    }

    // Некорректный индекс
    {
        geom::Vec2 v(1.0, 2.0);
        bool thrown = false;

        try {
            v[2];
        } catch (const std::out_of_range&) {
            thrown = true;
        }

        assert(thrown);
    }

    // Унарные + и -
    {
        geom::Vec2 v(3.0, -4.0);

        geom::Vec2 plus = +v;
        assert(nearly_equal(plus.x(), 3.0));
        assert(nearly_equal(plus.y(), -4.0));

        geom::Vec2 minus = -v;
        assert(nearly_equal(minus.x(), -3.0));
        assert(nearly_equal(minus.y(), 4.0));
    }

    // Сложение и вычитание
    {
        geom::Vec2 a(3.0, 4.0);
        geom::Vec2 b(1.0, 2.0);

        geom::Vec2 sum = a + b;
        assert(nearly_equal(sum.x(), 4.0));
        assert(nearly_equal(sum.y(), 6.0));

        geom::Vec2 diff = a - b;
        assert(nearly_equal(diff.x(), 2.0));
        assert(nearly_equal(diff.y(), 2.0));
    }

    // Умножение и деление на число
    {
        geom::Vec2 v(3.0, 4.0);

        geom::Vec2 a = v * 2.0;
        assert(nearly_equal(a.x(), 6.0));
        assert(nearly_equal(a.y(), 8.0));

        geom::Vec2 b = 2.0 * v;
        assert(nearly_equal(b.x(), 6.0));
        assert(nearly_equal(b.y(), 8.0));

        geom::Vec2 c = v / 2.0;
        assert(nearly_equal(c.x(), 1.5));
        assert(nearly_equal(c.y(), 2.0));
    }

    // Составные операторы
    {
        geom::Vec2 v(1.0, 2.0);

        v += geom::Vec2(3.0, 4.0);
        assert(nearly_equal(v.x(), 4.0));
        assert(nearly_equal(v.y(), 6.0));

        v -= geom::Vec2(1.0, 2.0);
        assert(nearly_equal(v.x(), 3.0));
        assert(nearly_equal(v.y(), 4.0));

        v *= 2.0;
        assert(nearly_equal(v.x(), 6.0));
        assert(nearly_equal(v.y(), 8.0));

        v /= 2.0;
        assert(nearly_equal(v.x(), 3.0));
        assert(nearly_equal(v.y(), 4.0));
    }

    // Нормализация нулевого вектора
    {
        geom::Vec2 v(0.0, 0.0);
        bool thrown = false;

        try {
            v.normalized();
        } catch (const std::invalid_argument&) {
            thrown = true;
        }

        assert(thrown);
    }

    // Деление на ноль
    {
        geom::Vec2 v(1.0, 2.0);
        bool thrown = false;

        try {
            v / 0.0;
        } catch (const std::invalid_argument&) {
            thrown = true;
        }

        assert(thrown);
    }

    // Потоковый ввод
    {
        std::istringstream input("5 6");
        geom::Vec2 v;

        input >> v;

        assert(!input.fail());
        assert(nearly_equal(v.x(), 5.0));
        assert(nearly_equal(v.y(), 6.0));
    }

    // Некорректный потоковый ввод
    {
        std::istringstream input("abc 6");
        geom::Vec2 v(1.0, 2.0);

        input >> v;

        assert(input.fail());
        assert(nearly_equal(v.x(), 1.0));
        assert(nearly_equal(v.y(), 2.0));
    }

        // Vec3: конструкторы и координаты
    {
        geom::Vec3 v;
        assert(nearly_equal(v.x(), 0.0));
        assert(nearly_equal(v.y(), 0.0));
        assert(nearly_equal(v.z(), 0.0));
    }

    {
        geom::Vec3 v(1.0, 2.0, 3.0);
        assert(nearly_equal(v.x(), 1.0));
        assert(nearly_equal(v.y(), 2.0));
        assert(nearly_equal(v.z(), 3.0));
    }

    // Vec3: длина
    {
        geom::Vec3 v(3.0, 4.0, 12.0);
        assert(nearly_equal(v.length2(), 169.0));
        assert(nearly_equal(v.length(), 13.0));
    }

    // Vec3: dot
    {
        geom::Vec3 a(1.0, 2.0, 3.0);
        geom::Vec3 b(4.0, 5.0, 6.0);

        assert(nearly_equal(a.dot(b), 32.0));
    }

    // Vec3: cross
    {
        geom::Vec3 x(1.0, 0.0, 0.0);
        geom::Vec3 y(0.0, 1.0, 0.0);

        geom::Vec3 z = x.cross(y);

        assert(nearly_equal(z.x(), 0.0));
        assert(nearly_equal(z.y(), 0.0));
        assert(nearly_equal(z.z(), 1.0));
    }

    // Vec3: normalized
    {
        geom::Vec3 v(0.0, 3.0, 4.0);
        geom::Vec3 n = v.normalized();

        assert(nearly_equal(n.x(), 0.0));
        assert(nearly_equal(n.y(), 0.6));
        assert(nearly_equal(n.z(), 0.8));
        assert(nearly_equal(n.length(), 1.0));
    }

    // Vec3: operator[]
    {
        geom::Vec3 v(1.0, 2.0, 3.0);

        assert(nearly_equal(v[0], 1.0));
        assert(nearly_equal(v[1], 2.0));
        assert(nearly_equal(v[2], 3.0));

        v[0] = 10.0;
        v[1] = 20.0;
        v[2] = 30.0;

        assert(nearly_equal(v.x(), 10.0));
        assert(nearly_equal(v.y(), 20.0));
        assert(nearly_equal(v.z(), 30.0));
    }

    // Vec3: некорректный индекс
    {
        geom::Vec3 v(1.0, 2.0, 3.0);
        bool thrown = false;

        try {
            v[3];
        } catch (const std::exception&) {
            thrown = true;
        }

        assert(thrown);
    }

    // Vec3: сложение и вычитание
    {
        geom::Vec3 a(1.0, 2.0, 3.0);
        geom::Vec3 b(4.0, 5.0, 6.0);

        geom::Vec3 sum = a + b;
        assert(nearly_equal(sum.x(), 5.0));
        assert(nearly_equal(sum.y(), 7.0));
        assert(nearly_equal(sum.z(), 9.0));

        geom::Vec3 diff = b - a;
        assert(nearly_equal(diff.x(), 3.0));
        assert(nearly_equal(diff.y(), 3.0));
        assert(nearly_equal(diff.z(), 3.0));
    }

    // Vec3: умножение и деление
    {
        geom::Vec3 v(2.0, 4.0, 6.0);

        geom::Vec3 a = v * 2.0;
        assert(nearly_equal(a.x(), 4.0));
        assert(nearly_equal(a.y(), 8.0));
        assert(nearly_equal(a.z(), 12.0));

        geom::Vec3 b = 2.0 * v;
        assert(nearly_equal(b.x(), 4.0));
        assert(nearly_equal(b.y(), 8.0));
        assert(nearly_equal(b.z(), 12.0));

        geom::Vec3 c = v / 2.0;
        assert(nearly_equal(c.x(), 1.0));
        assert(nearly_equal(c.y(), 2.0));
        assert(nearly_equal(c.z(), 3.0));
    }

    // Vec3: составные операторы
    {
        geom::Vec3 v(1.0, 2.0, 3.0);

        v += geom::Vec3(1.0, 1.0, 1.0);
        assert(nearly_equal(v.x(), 2.0));
        assert(nearly_equal(v.y(), 3.0));
        assert(nearly_equal(v.z(), 4.0));

        v -= geom::Vec3(1.0, 1.0, 1.0);
        assert(nearly_equal(v.x(), 1.0));
        assert(nearly_equal(v.y(), 2.0));
        assert(nearly_equal(v.z(), 3.0));

        v *= 2.0;
        assert(nearly_equal(v.x(), 2.0));
        assert(nearly_equal(v.y(), 4.0));
        assert(nearly_equal(v.z(), 6.0));

        v /= 2.0;
        assert(nearly_equal(v.x(), 1.0));
        assert(nearly_equal(v.y(), 2.0));
        assert(nearly_equal(v.z(), 3.0));
    }

    // Vec3: нормализация нулевого вектора
    {
        geom::Vec3 v(0.0, 0.0, 0.0);
        bool thrown = false;

        try {
            v.normalized();
        } catch (const std::invalid_argument&) {
            thrown = true;
        }

        assert(thrown);
    }

    // Vec3: деление на ноль
    {
        geom::Vec3 v(1.0, 2.0, 3.0);
        bool thrown = false;

        try {
            v / 0.0;
        } catch (const std::invalid_argument&) {
            thrown = true;
        }

        assert(thrown);
    }

    // Vec3: потоковый ввод
    {
        std::istringstream input("5 6 7");
        geom::Vec3 v;

        input >> v;

        assert(!input.fail());
        assert(nearly_equal(v.x(), 5.0));
        assert(nearly_equal(v.y(), 6.0));
        assert(nearly_equal(v.z(), 7.0));
    }

    // Vec3: некорректный потоковый ввод
    {
        std::istringstream input("abc 6 7");
        geom::Vec3 v(1.0, 2.0, 3.0);

        input >> v;

        assert(input.fail());
        assert(nearly_equal(v.x(), 1.0));
        assert(nearly_equal(v.y(), 2.0));
        assert(nearly_equal(v.z(), 3.0));
    }


    



    return 0;

    


}