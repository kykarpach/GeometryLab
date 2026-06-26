// Тест создан нейросетью. Автор проекта не ручается за полноту и идеальную корректность этих тестов.
#include "geometry/Polygon2.h"
#include "geometry/AABB2.h"
#include "geometry/Intersections.h"
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

void test_polygon2() {
    using namespace geom;

    // 1. Constructor and size
    {
        Polygon2 poly({
            Vec2(0.0, 0.0),
            Vec2(4.0, 0.0),
            Vec2(4.0, 3.0)
        });

        assert(poly.size() == 3);
        assert(poly[0].x() == 0.0);
        assert(poly[1].x() == 4.0);
        assert(poly[2].y() == 3.0);
    }

    // 2. Invalid polygon: less than 3 vertices
    {
        bool thrown = false;

        try {
            Polygon2 bad({
                Vec2(0.0, 0.0),
                Vec2(1.0, 1.0)
            });
        } catch (const std::invalid_argument&) {
            thrown = true;
        }

        assert(thrown);
    }

    // 3. Triangle perimeter and area
    {
        Polygon2 tri({
            Vec2(0.0, 0.0),
            Vec2(3.0, 0.0),
            Vec2(0.0, 4.0)
        });

        assert(nearly_equal(tri.perimeter(), 12.0));
        assert(nearly_equal(tri.area(), 6.0));
    }

    // 4. Rectangle perimeter and area
    {
        Polygon2 rect({
            Vec2(0.0, 0.0),
            Vec2(4.0, 0.0),
            Vec2(4.0, 3.0),
            Vec2(0.0, 3.0)
        });

        assert(nearly_equal(rect.perimeter(), 14.0));
        assert(nearly_equal(rect.area(), 12.0));
    }

    // 5. Same rectangle, reverse order: area should stay positive
    {
        Polygon2 rect({
            Vec2(0.0, 0.0),
            Vec2(0.0, 3.0),
            Vec2(4.0, 3.0),
            Vec2(4.0, 0.0)
        });

        assert(nearly_equal(rect.area(), 12.0));
    }

    // 6. Bounding box
    {
        Polygon2 poly({
            Vec2(2.0, 5.0),
            Vec2(10.0, 3.0),
            Vec2(4.0, -1.0)
        });

        AABB2 box = poly.bounding_box();

        assert(box.min().x() == 2.0);
        assert(box.min().y() == -1.0);
        assert(box.max().x() == 10.0);
        assert(box.max().y() == 5.0);
    }

    // 7. contains_point: inside rectangle
    {
        Polygon2 rect({
            Vec2(0.0, 0.0),
            Vec2(4.0, 0.0),
            Vec2(4.0, 3.0),
            Vec2(0.0, 3.0)
        });

        assert(rect.contains_point(Vec2(2.0, 1.0)));
    }

    // 8. contains_point: outside rectangle
    {
        Polygon2 rect({
            Vec2(0.0, 0.0),
            Vec2(4.0, 0.0),
            Vec2(4.0, 3.0),
            Vec2(0.0, 3.0)
        });

        assert(!rect.contains_point(Vec2(5.0, 1.0)));
        assert(!rect.contains_point(Vec2(2.0, 4.0)));
    }

    // 9. contains_point: on border
    {
        Polygon2 rect({
            Vec2(0.0, 0.0),
            Vec2(4.0, 0.0),
            Vec2(4.0, 3.0),
            Vec2(0.0, 3.0)
        });

        assert(rect.contains_point(Vec2(0.0, 0.0)));
        assert(rect.contains_point(Vec2(2.0, 0.0)));
        assert(rect.contains_point(Vec2(4.0, 2.0)));
    }

    // 10. Concave polygon
    {
        Polygon2 poly({
            Vec2(0.0, 0.0),
            Vec2(4.0, 0.0),
            Vec2(4.0, 4.0),
            Vec2(2.0, 2.0),
            Vec2(0.0, 4.0)
        });

        assert(nearly_equal(poly.area(), 12.0));

        assert(poly.contains_point(Vec2(1.0, 1.0)));
        assert(poly.contains_point(Vec2(3.5, 1.0)));

        // Точка в "вырезанной" вогнутой области
        assert(!poly.contains_point(Vec2(2.0, 3.0)));
    }
}

void test_aabb2() {
    using namespace geom;

    // 1. default constructor
    {
        AABB2 box;

        assert(box.min().x() == 0.0);
        assert(box.min().y() == 0.0);
        assert(box.max().x() == 0.0);
        assert(box.max().y() == 0.0);

        assert(box.width() == 0.0);
        assert(box.height() == 0.0);
        assert(box.area() == 0.0);
    }

    // 2. normal constructor
    {
        AABB2 box(Vec2(1.0, 2.0), Vec2(5.0, 8.0));

        assert(box.min().x() == 1.0);
        assert(box.min().y() == 2.0);
        assert(box.max().x() == 5.0);
        assert(box.max().y() == 8.0);

        assert(box.width() == 4.0);
        assert(box.height() == 6.0);
        assert(box.area() == 24.0);
    }

    // 3. center
    {
        AABB2 box(Vec2(0.0, 0.0), Vec2(10.0, 6.0));
        Vec2 c = box.center();

        assert(c.x() == 5.0);
        assert(c.y() == 3.0);
    }

    // 4. contains: inside
    {
        AABB2 box(Vec2(0.0, 0.0), Vec2(10.0, 10.0));

        assert(box.contains(Vec2(5.0, 5.0)));
    }

    // 5. contains: border
    {
        AABB2 box(Vec2(0.0, 0.0), Vec2(10.0, 10.0));

        assert(box.contains(Vec2(0.0, 0.0)));
        assert(box.contains(Vec2(10.0, 10.0)));
        assert(box.contains(Vec2(0.0, 5.0)));
        assert(box.contains(Vec2(10.0, 5.0)));
    }

    // 6. contains: outside
    {
        AABB2 box(Vec2(0.0, 0.0), Vec2(10.0, 10.0));

        assert(!box.contains(Vec2(-1.0, 5.0)));
        assert(!box.contains(Vec2(11.0, 5.0)));
        assert(!box.contains(Vec2(5.0, -1.0)));
        assert(!box.contains(Vec2(5.0, 11.0)));
    }

    // 7. intersects: overlapping boxes
    {
        AABB2 a(Vec2(0.0, 0.0), Vec2(10.0, 10.0));
        AABB2 b(Vec2(5.0, 5.0), Vec2(15.0, 15.0));

        assert(a.intersects(b));
        assert(b.intersects(a));
    }

    // 8. intersects: touching by side
    {
        AABB2 a(Vec2(0.0, 0.0), Vec2(10.0, 10.0));
        AABB2 b(Vec2(10.0, 0.0), Vec2(20.0, 10.0));

        assert(a.intersects(b));
        assert(b.intersects(a));
    }

    // 9. intersects: touching by point
    {
        AABB2 a(Vec2(0.0, 0.0), Vec2(10.0, 10.0));
        AABB2 b(Vec2(10.0, 10.0), Vec2(20.0, 20.0));

        assert(a.intersects(b));
        assert(b.intersects(a));
    }

    // 10. intersects: separated boxes
    {
        AABB2 a(Vec2(0.0, 0.0), Vec2(10.0, 10.0));
        AABB2 b(Vec2(11.0, 0.0), Vec2(20.0, 10.0));
        AABB2 c(Vec2(0.0, 11.0), Vec2(10.0, 20.0));

        assert(!a.intersects(b));
        assert(!b.intersects(a));

        assert(!a.intersects(c));
        assert(!c.intersects(a));
    }

    // 11. intersects: cross-like case
    // Важный тест: углы могут не лежать внутри, но пересечение есть.
    {
        AABB2 a(Vec2(0.0, 4.0), Vec2(10.0, 6.0));
        AABB2 b(Vec2(4.0, 0.0), Vec2(6.0, 10.0));

        assert(a.intersects(b));
        assert(b.intersects(a));
    }

    // 12. expand to the right/up
    {
        AABB2 box(Vec2(0.0, 0.0), Vec2(10.0, 10.0));

        box.expand(Vec2(15.0, 20.0));

        assert(box.min().x() == 0.0);
        assert(box.min().y() == 0.0);
        assert(box.max().x() == 15.0);
        assert(box.max().y() == 20.0);
    }

    // 13. expand to the left/down
    {
        AABB2 box(Vec2(0.0, 0.0), Vec2(10.0, 10.0));

        box.expand(Vec2(-5.0, -3.0));

        assert(box.min().x() == -5.0);
        assert(box.min().y() == -3.0);
        assert(box.max().x() == 10.0);
        assert(box.max().y() == 10.0);
    }

    // 14. expand by inner point should not change box
    {
        AABB2 box(Vec2(0.0, 0.0), Vec2(10.0, 10.0));

        box.expand(Vec2(5.0, 5.0));

        assert(box.min().x() == 0.0);
        assert(box.min().y() == 0.0);
        assert(box.max().x() == 10.0);
        assert(box.max().y() == 10.0);
    }

    // 15. invalid constructor
    {
        bool thrown = false;

        try {
            AABB2 bad(Vec2(10.0, 0.0), Vec2(0.0, 10.0));
        } catch (const std::invalid_argument&) {
            thrown = true;
        }

        assert(thrown);
    }
}

void test_intersect_segment3() {

    // 1. Непараллельные отрезки пересекаются в точке
    {
        Segment3 a(Vec3(0, 0, 0), Vec3(2, 0, 0));
        Segment3 b(Vec3(1, -1, 0), Vec3(1, 1, 0));

        auto res = intersect(a, b);

        assert(res.type == IntersectionType3::Point);
        assert(res.point.has_value());
        assert(is_zero((*res.point - Vec3(1, 0, 0)).length()));
    }

    // 2. Скрещивающиеся отрезки: прямые не параллельны, но в 3D не пересекаются
    {
        Segment3 a(Vec3(0, 0, 0), Vec3(1, 0, 0));
        Segment3 b(Vec3(0, 1, 1), Vec3(0, 2, 0));

        auto res = intersect(a, b);

        assert(res.type == IntersectionType3::None);
    }

    // 3. Непараллельные прямые пересеклись бы, но точка вне первого отрезка
    {
        Segment3 a(Vec3(0, 0, 0), Vec3(1, 0, 0));
        Segment3 b(Vec3(2, -1, 0), Vec3(2, 1, 0));

        auto res = intersect(a, b);

        assert(res.type == IntersectionType3::None);
    }

    // 4. Параллельные отрезки на разных прямых
    {
        Segment3 a(Vec3(0, 0, 0), Vec3(2, 0, 0));
        Segment3 b(Vec3(0, 1, 0), Vec3(2, 1, 0));

        auto res = intersect(a, b);

        assert(res.type == IntersectionType3::None);
    }

    // 5. Коллинеарные отрезки перекрываются отрезком
    {
        Segment3 a(Vec3(0, 0, 0), Vec3(4, 0, 0));
        Segment3 b(Vec3(2, 0, 0), Vec3(6, 0, 0));

        auto res = intersect(a, b);

        assert(res.type == IntersectionType3::Segment);
        assert(res.segment.has_value());
        assert(is_zero((res.segment->start() - Vec3(2, 0, 0)).length()));
        assert(is_zero((res.segment->end() - Vec3(4, 0, 0)).length()));
    }

    // 6. Коллинеарные отрезки касаются в одной точке
    {
        Segment3 a(Vec3(0, 0, 0), Vec3(2, 0, 0));
        Segment3 b(Vec3(2, 0, 0), Vec3(4, 0, 0));

        auto res = intersect(a, b);

        assert(res.type == IntersectionType3::Point);
        assert(res.point.has_value());
        assert(is_zero((*res.point - Vec3(2, 0, 0)).length()));
    }

    // 7. Коллинеарные отрезки не пересекаются
    {
        Segment3 a(Vec3(0, 0, 0), Vec3(1, 0, 0));
        Segment3 b(Vec3(2, 0, 0), Vec3(3, 0, 0));

        auto res = intersect(a, b);

        assert(res.type == IntersectionType3::None);
    }

    // 8. Один отрезок вырожден в точку, точка лежит на втором
    {
        Segment3 a(Vec3(1, 1, 1), Vec3(1, 1, 1));
        Segment3 b(Vec3(0, 0, 0), Vec3(2, 2, 2));

        auto res = intersect(a, b);

        assert(res.type == IntersectionType3::Point);
        assert(res.point.has_value());
        assert(is_zero((*res.point - Vec3(1, 1, 1)).length()));
    }

    // 9. Один отрезок вырожден в точку, точка не лежит на втором
    {
        Segment3 a(Vec3(1, 1, 2), Vec3(1, 1, 2));
        Segment3 b(Vec3(0, 0, 0), Vec3(2, 2, 2));

        auto res = intersect(a, b);

        assert(res.type == IntersectionType3::None);
    }

    // 10. Оба отрезка вырождены в одну точку
    {
        Segment3 a(Vec3(1, 2, 3), Vec3(1, 2, 3));
        Segment3 b(Vec3(1, 2, 3), Vec3(1, 2, 3));

        auto res = intersect(a, b);

        assert(res.type == IntersectionType3::Point);
        assert(res.point.has_value());
        assert(is_zero((*res.point - Vec3(1, 2, 3)).length()));
    }

    // 11. Оба отрезка вырождены в разные точки
    {
        Segment3 a(Vec3(1, 2, 3), Vec3(1, 2, 3));
        Segment3 b(Vec3(1, 2, 4), Vec3(1, 2, 4));

        auto res = intersect(a, b);

        assert(res.type == IntersectionType3::None);
    }
}

void test_segment2_intersection() {
    using namespace geom;

    // Непараллельные отрезки пересекаются в одной точке.
    Segment2 a1(Vec2(0.0, 0.0), Vec2(10.0, 0.0));
    Segment2 b1(Vec2(5.0, -5.0), Vec2(5.0, 5.0));

    IntersectionResult2 r1 = intersect(a1, b1);

    assert(r1.type == IntersectionType2::Point);
    assert(r1.point.has_value());
    assert(geom::nearly_equal(r1.point->x(), 5.0));
    assert(geom::nearly_equal(r1.point->y(), 0.0));

    // Непараллельные прямые пересекаются, но сами отрезки не доходят до точки пересечения.
    Segment2 a2(Vec2(0.0, 0.0), Vec2(1.0, 0.0));
    Segment2 b2(Vec2(2.0, -1.0), Vec2(2.0, 1.0));

    IntersectionResult2 r2 = intersect(a2, b2);

    assert(r2.type == IntersectionType2::None);
    assert(!r2.point.has_value());
    assert(!r2.segment.has_value());

    // Параллельные отрезки лежат на разных прямых.
    Segment2 a3(Vec2(0.0, 0.0), Vec2(10.0, 0.0));
    Segment2 b3(Vec2(0.0, 1.0), Vec2(10.0, 1.0));

    IntersectionResult2 r3 = intersect(a3, b3);

    assert(r3.type == IntersectionType2::None);

    // Коллинеарные отрезки не пересекаются.
    Segment2 a4(Vec2(0.0, 0.0), Vec2(10.0, 0.0));
    Segment2 b4(Vec2(11.0, 0.0), Vec2(15.0, 0.0));

    IntersectionResult2 r4 = intersect(a4, b4);

    assert(r4.type == IntersectionType2::None);

    // Коллинеарные отрезки касаются в одной точке.
    Segment2 a5(Vec2(0.0, 0.0), Vec2(10.0, 0.0));
    Segment2 b5(Vec2(10.0, 0.0), Vec2(15.0, 0.0));

    IntersectionResult2 r5 = intersect(a5, b5);

    assert(r5.type == IntersectionType2::Point);
    assert(r5.point.has_value());
    assert(geom::nearly_equal(r5.point->x(), 10.0));
    assert(geom::nearly_equal(r5.point->y(), 0.0));

    // Коллинеарные отрезки пересекаются отрезком.
    Segment2 a6(Vec2(0.0, 0.0), Vec2(10.0, 0.0));
    Segment2 b6(Vec2(3.0, 0.0), Vec2(7.0, 0.0));

    IntersectionResult2 r6 = intersect(a6, b6);

    assert(r6.type == IntersectionType2::Segment);
    assert(r6.segment.has_value());
    assert(geom::nearly_equal(r6.segment->start().x(), 3.0));
    assert(geom::nearly_equal(r6.segment->start().y(), 0.0));
    assert(geom::nearly_equal(r6.segment->end().x(), 7.0));
    assert(geom::nearly_equal(r6.segment->end().y(), 0.0));

    // Коллинеарные отрезки пересекаются отрезком, частичное наложение.
    Segment2 a7(Vec2(0.0, 0.0), Vec2(10.0, 0.0));
    Segment2 b7(Vec2(7.0, 0.0), Vec2(15.0, 0.0));

    IntersectionResult2 r7 = intersect(a7, b7);

    assert(r7.type == IntersectionType2::Segment);
    assert(r7.segment.has_value());
    assert(geom::nearly_equal(r7.segment->start().x(), 7.0));
    assert(geom::nearly_equal(r7.segment->start().y(), 0.0));
    assert(geom::nearly_equal(r7.segment->end().x(), 10.0));
    assert(geom::nearly_equal(r7.segment->end().y(), 0.0));

    // Один отрезок вырожден в точку и лежит на другом.
    Segment2 a8(Vec2(5.0, 0.0), Vec2(5.0, 0.0));
    Segment2 b8(Vec2(0.0, 0.0), Vec2(10.0, 0.0));

    IntersectionResult2 r8 = intersect(a8, b8);

    assert(r8.type == IntersectionType2::Point);
    assert(r8.point.has_value());
    assert(geom::nearly_equal(r8.point->x(), 5.0));
    assert(geom::nearly_equal(r8.point->y(), 0.0));

    // Оба отрезка вырождены в одну и ту же точку.
    Segment2 a9(Vec2(2.0, 3.0), Vec2(2.0, 3.0));
    Segment2 b9(Vec2(2.0, 3.0), Vec2(2.0, 3.0));

    IntersectionResult2 r9 = intersect(a9, b9);

    assert(r9.type == IntersectionType2::Point);
    assert(r9.point.has_value());
    assert(geom::nearly_equal(r9.point->x(), 2.0));
    assert(geom::nearly_equal(r9.point->y(), 3.0));

    // Оба отрезка вырождены в разные точки.
    Segment2 a10(Vec2(2.0, 3.0), Vec2(2.0, 3.0));
    Segment2 b10(Vec2(4.0, 5.0), Vec2(4.0, 5.0));

    IntersectionResult2 r10 = intersect(a10, b10);

    assert(r10.type == IntersectionType2::None);
}

void test_intersection_result3() {
    

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
    ;

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
    
    test_polygon2();
    test_aabb2();
    test_intersect_segment3();
    test_segment2_intersection();
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



        // distance_point_line: точка над осью X
    {
        geom::Vec3 p(0.0, 3.0, 0.0);
        geom::Vec3 A0(0.0, 0.0, 0.0);
        geom::Vec3 A1(1.0, 0.0, 0.0);

        assert(nearly_equal(geom::distance_point_line(p, A0, A1), 3.0));
    }

    // distance_point_line: точка лежит на прямой
    {
        geom::Vec3 p(5.0, 0.0, 0.0);
        geom::Vec3 A0(0.0, 0.0, 0.0);
        geom::Vec3 A1(1.0, 0.0, 0.0);

        assert(nearly_equal(geom::distance_point_line(p, A0, A1), 0.0));
    }

    // distance_point_line: направляющий вектор не единичный
    {
        geom::Vec3 p(0.0, 3.0, 4.0);
        geom::Vec3 A0(0.0, 0.0, 0.0);
        geom::Vec3 A1(10.0, 0.0, 0.0);

        assert(nearly_equal(geom::distance_point_line(p, A0, A1), 5.0));
    }

    // distance_point_line: вырожденная прямая
    {
        geom::Vec3 p(1.0, 2.0, 3.0);
        geom::Vec3 A0(0.0, 0.0, 0.0);
        geom::Vec3 A1(0.0, 0.0, 0.0);

        bool thrown = false;

        try {
            geom::distance_point_line(p, A0, A1);
        } catch (const std::invalid_argument&) {
            thrown = true;
        }

        assert(thrown);
    }

    // distance_line_line: совпадающие прямые
    {
        geom::Vec3 A0(0.0, 0.0, 0.0);
        geom::Vec3 A1(1.0, 0.0, 0.0);

        geom::Vec3 B0(5.0, 0.0, 0.0);
        geom::Vec3 B1(10.0, 0.0, 0.0);

        assert(nearly_equal(geom::distance_line_line(A0, A1, B0, B1), 0.0));
    }

    // distance_line_line: параллельные разные прямые
    {
        geom::Vec3 A0(0.0, 0.0, 0.0);
        geom::Vec3 A1(1.0, 0.0, 0.0);

        geom::Vec3 B0(0.0, 2.0, 0.0);
        geom::Vec3 B1(1.0, 2.0, 0.0);

        assert(nearly_equal(geom::distance_line_line(A0, A1, B0, B1), 2.0));
    }

    // distance_line_line: пересекающиеся прямые
    {
        geom::Vec3 A0(0.0, 0.0, 0.0);
        geom::Vec3 A1(1.0, 0.0, 0.0);

        geom::Vec3 B0(0.0, 0.0, 0.0);
        geom::Vec3 B1(0.0, 1.0, 0.0);

        assert(nearly_equal(geom::distance_line_line(A0, A1, B0, B1), 0.0));
    }

    // distance_line_line: скрещивающиеся прямые
    {
        geom::Vec3 A0(0.0, 0.0, 0.0);
        geom::Vec3 A1(1.0, 0.0, 0.0);

        geom::Vec3 B0(0.0, 1.0, 2.0);
        geom::Vec3 B1(0.0, 2.0, 2.0);

        assert(nearly_equal(geom::distance_line_line(A0, A1, B0, B1), 2.0));
    }

    // distance_line_line: скрещивающиеся прямые, направления не единичные
    {
        geom::Vec3 A0(0.0, 0.0, 0.0);
        geom::Vec3 A1(2.0, 0.0, 0.0);

        geom::Vec3 B0(0.0, 1.0, 5.0);
        geom::Vec3 B1(0.0, 4.0, 5.0);

        assert(nearly_equal(geom::distance_line_line(A0, A1, B0, B1), 5.0));
    }

    // distance_line_line: первая прямая вырождена
    {
        geom::Vec3 A0(0.0, 0.0, 0.0);
        geom::Vec3 A1(0.0, 0.0, 0.0);

        geom::Vec3 B0(0.0, 1.0, 0.0);
        geom::Vec3 B1(1.0, 1.0, 0.0);

        bool thrown = false;

        try {
            geom::distance_line_line(A0, A1, B0, B1);
        } catch (const std::invalid_argument&) {
            thrown = true;
        }

        assert(thrown);
    }

    // distance_line_line: вторая прямая вырождена
    {
        geom::Vec3 A0(0.0, 0.0, 0.0);
        geom::Vec3 A1(1.0, 0.0, 0.0);

        geom::Vec3 B0(0.0, 1.0, 0.0);
        geom::Vec3 B1(0.0, 1.0, 0.0);

        bool thrown = false;

        try {
            geom::distance_line_line(A0, A1, B0, B1);
        } catch (const std::invalid_argument&) {
            thrown = true;
        }

        assert(thrown);
    }
        



    return 0;

    


}