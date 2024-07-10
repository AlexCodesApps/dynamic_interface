#include "dynamic_interface.hpp"
#include <cmath>
#include <iostream>
#include <numbers>

struct position {float x, y;};

DECLARE_INTERFACE(shape,
    (void, draw, position),
    (int, count_sides),
    (float, area),
    (float, perimeter)
)

struct circle {
    float radius;
    void draw(position p) {
        std::cout << " A Circle Is Recorded At " << p.x << " " << p.y << std::endl;
    }
    int count_sides() {
        return 1;
    }
    float area() {
        return radius * radius * std::numbers::pi;
    }
    float circumfrence() {
        return radius * 2.0f * std::numbers::pi;
    }
    float perimeter() {
        return circumfrence();
    }
};

struct square {
    int w, h;
    void draw(position p) {
        std::cout << " A Square Is Recorded At " << p.x << " " << p.y << std::endl;
    }
    int count_sides() {
        return 4;
    }
    float area() {
        return w * h;
    }
    float perimeter() {
        return w + w + h + h;
    }
};

struct regular_polygon {
    int sides;
    float side_length;
    void draw(position p) {
        std::cout << " A Polygon Is Recorded At " << p.x << ", " << p.y << std::endl;
    }
    int count_sides() {
        return sides;
    }
    float radius() {
        return (side_length/2) / std::tan(std::numbers::pi/sides);
    }
    float apothem() {
        return std::cos(std::numbers::pi/sides) * radius();
    }
    float perimeter() {
        return sides * side_length;
    }
    float area() {
        return (perimeter() * apothem()) / 2;
    }
};

void print_shape(shape s) {
    s.draw({4, 5});
    std::cout << "Shape Number Of Sides: " << s.count_sides() << std::endl;
    std::cout << "Shape Perimeter: " << s.perimeter() << std::endl;
    std::cout << "Shape Area: " << s.area() << std::endl;
}

int main() {
    circle c{12.3};
    square s{12, 9};
    regular_polygon p{5, 3.8};
    print_shape(c);
    print_shape(s);
    print_shape(p);
}
