#ifndef UTILS_H
#define UTILS_H

#include "array.h"
#include "rectangle.h"
#include "trapezoid.h"
#include "romb.h"
#include <iostream>

template<Scalar T>
void print_all_figures(const Array<std::shared_ptr<Figure<T>>>& figures) {
    std::cout << "\n=== All Figures ===" << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        if (figures[i]) {
            std::cout << "Figure " << i << ": " << *figures[i] << std::endl;
        }
    }
}

template<Scalar T>
double total_area(const Array<std::shared_ptr<Figure<T>>>& figures) {
    double total = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        if (figures[i]) {
            total += figures[i]->area();
        }
    }
    return total;
}

template<Scalar T>
std::shared_ptr<Figure<T>> input_rectangle() {
    T x, y, width, height;
    std::cout << "Enter rectangle parameters (x y width height): ";
    std::cin >> x >> y >> width >> height;
    return std::make_shared<Rectangle<T>>(x, y, width, height);
}

template<Scalar T>
std::shared_ptr<Figure<T>> input_trapezoid() {
    T x1, y1, x2, y2, x3, y3, x4, y4;
    std::cout << "Enter trapezoid parameters (x1 y1 x2 y2 x3 y3 x4 y4): ";
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    return std::make_shared<Trapezoid<T>>(x1, y1, x2, y2, x3, y3, x4, y4);
}

template<Scalar T>
std::shared_ptr<Figure<T>> input_romb() {
    T center_x, center_y, diag1, diag2;
    std::cout << "Enter romb parameters (center_x center_y diag1 diag2): ";
    std::cin >> center_x >> center_y >> diag1 >> diag2;
    return std::make_shared<Romb<T>>(center_x, center_y, diag1, diag2);
}

#endif
