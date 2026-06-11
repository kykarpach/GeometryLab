// Тест создан нейросетью. Автор проекта не ручается за полноту и идеальную корректность этих тестов.

#include "geometry/Vec2.h"

#include <cassert>
#include <cmath>
#include <sstream>
#include <stdexcept>

bool nearly_equal(double a, double b, double eps = 1e-9) {
    return std::abs(a - b) < eps;
}

int main() {
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

    return 0;
}