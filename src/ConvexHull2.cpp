#include "geometry/ConvexHull2.h"



namespace geom {

    // Берёт набор точек.
    // Сортирует точки слева направо:
    // сначала по x, если x равны — по y.
    // Строит нижнюю часть оболочки.
    // Строит верхнюю часть оболочки.
    // Склеивает их в один контур.
    // Возвращает Polygon2.

// Алгоритм называется - Монотонная цепь Эндрю //https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_answ/Monotone_chain
Polygon2 convex_hull(std::vector<Vec2> points) {
    // Отсортировали точки по x, если x равны - по y
    std::sort(points.begin(),
              points.end(),
              [](const Vec2& a, const Vec2& b) {
                  if (nearly_equal(a.x(), b.x())) {
                      return a.y() < b.y();
                  }

                  return a.x() < b.x();
              });

    
    auto last = std::unique(points.begin(),
                            points.end(),
                            [](const Vec2& a, const Vec2& b) {
                                return nearly_equal(a.x(), b.x()) &&
                                       nearly_equal(a.y(), b.y());
                            });
    // Удалили одинаковые точки
    points.erase(last, points.end());

    if (points.size() < 3) {
        throw std::invalid_argument("convex answ requires at least 3 unique points");
    }


    // Будем обходить моссив точке против часовой стрелки

    auto cross = [](const Vec2& a, const Vec2& b, const Vec2& c) {
        return (b - a).cross(c - a);
    };

    std::vector<Vec2> lower;

    // Строим нижнюю часть оболочки
    for (const Vec2& p : points) {
        while (lower.size() >= 2) {
            const Vec2& a = lower[lower.size() - 2];
            const Vec2& b = lower[lower.size() - 1];

            if (cross(a, b, p) <= EPS) {//Где лежит p относитлеьно ab? Справа или слева?
                lower.pop_back();//Справа ? - удалить. Нижняя граница - левые повороты   
            } else {
                break;
            }
        }

        lower.push_back(p);
    }

    std::vector<Vec2> upper;

    // Строим верхнюю часть оболочки и обходим стдшынй вектор в обратную сторону
    for (auto it = points.rbegin(); it != points.rend(); ++it) {
        const Vec2& p = *it;

        while (upper.size() >= 2) {
            const Vec2& a = upper[upper.size() - 2];
            const Vec2& b = upper[upper.size() - 1];

            if (cross(a, b, p) <= EPS) {
                upper.pop_back();
            } else {
                break;
            }
        }

        upper.push_back(p);
    }

    // Убираем дубли крайних точек
    lower.pop_back();
    upper.pop_back();

    std::vector<Vec2> answ;

    answ.insert(answ.end(), lower.begin(), lower.end());
    answ.insert(answ.end(), upper.begin(), upper.end());

    return Polygon2(answ);
}

} // namespace geom