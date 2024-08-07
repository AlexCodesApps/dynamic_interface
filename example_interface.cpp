#include "dynamic_interface.hpp"
#include <cmath>
#include <iostream>

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
        return radius * radius * M_PI;
    }
    float circumference() {
        return radius * 2.0f * M_PI;
    }
    float perimeter() {
        return circumference();
    }
};
struct square {
    int w;
    void draw(position p) {
        std::cout << " A Square Is Recorded At " << p.x << " " << p.y << std::endl;
    }
    int count_sides() {
        return 4;
    }
    float area() {
        return w * w;
    }
    float perimeter() {
        return w * 4;
    }
};
struct rectangle {
    int w, h;
    void draw(position p) {
        std::cout << " A Rectangle Is Recorded At " << p.x << " " << p.y << std::endl;
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
    float apothem() {
        return (side_length/2) / std::tan(M_PI/sides);
    }
    float radius() {
        return (side_length/2) / std::sin(M_PI/sides);
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
    square s{32};
    rectangle r{12, 9};
    regular_polygon p{4, 32};
    print_shape(c);
    print_shape(s);
    print_shape(r);
    print_shape(p);
}
