#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>
#include "../include/point.h"
#include "../include/rectangle.h"
#include "../include/trapezoid.h"
#include "../include/romb.h"
#include "../include/array.h"
#include "../include/utils.h"

void test_point() {
    std::cout << "Testing Point class...\n";
    
    Point<int> p1(3, 4);
    Point<double> p2(2.5, 3.7);
    
    assert(p1.x() == 3);
    assert(p1.y() == 4);
    assert(p2.x() == 2.5);
    assert(p2.y() == 3.7);
    
    p1.set_x(10);
    p1.set_y(20);
    assert(p1.x() == 10);
    assert(p1.y() == 20);
    
    Point<int> p3(10, 20);
    Point<int> p4(5, 5);
    assert(p1 == p3);
    assert(p1 != p4);
    
    std::cout << "Point tests passed!\n";
}

void test_rectangle() {
    std::cout << "Testing Rectangle class...\n";
    
    Rectangle<int> rect1(0, 0, 5, 3);
    Rectangle<double> rect2(1.0, 1.0, 4.0, 2.0);
    
    // Тест площади
    assert(rect1.area() == 15.0);
    assert(rect2.area() == 8.0);
    
    // Тест центра
    Point<int> center1 = rect1.center();
    Point<double> center2 = rect2.center();
    assert(center1.x() == 2);
    assert(center1.y() == 1);
    assert(center2.x() == 3.0);
    assert(center2.y() == 2.0);
    
    // Тест опирующего конструктора
    Rectangle<int> rect3(rect1);
    assert(rect3.area() == rect1.area());
    
    Rectangle<int> rect4(0, 0, 1, 1);
    rect4 = rect1;
    assert(rect4.area() == rect1.area());
    
    // Тест конвертации в тип double
    double area = static_cast<double>(rect1);
    assert(area == 15.0);
    
    std::cout << "Rectangle tests passed!\n";
}

void test_trapezoid() {
    std::cout << "Testing Trapezoid class...\n";
    
    // Трапеция с основаниями, параллельными оси x
    Trapezoid<double> trap1(0, 0, 4, 0, 3, 3, 1, 3);
    
    // Тест площади (предположительно для этой трапеции 9)
    double area = trap1.area();
    assert(std::abs(area - 9.0) < 0.001);
    
    // Тест центра
    Point<double> center = trap1.center();
    assert(std::abs(center.x() - 2.0) < 0.001);
    assert(std::abs(center.y() - 1.5) < 0.001);
    
    // Тест копирующего конструктора
    Trapezoid<double> trap2(trap1);
    assert(trap2.area() == trap1.area());
    
    std::cout << "Trapezoid tests passed!\n";
}

void test_romb() {
    std::cout << "Testing Romb class...\n";
    
    Romb<double> romb1(0, 0, 6, 4);
    
    double area = romb1.area();
    assert(std::abs(area - 12.0) < 0.001);
    
    Point<double> center = romb1.center();
    assert(center.x() == 0.0);
    assert(center.y() == 0.0);
    
    // тест коордиант
    auto points_center = romb1.center();
    assert(points_center.x() == 0.0);
    assert(points_center.y() == 0.0);
    
    Romb<double> romb2(romb1);
    assert(romb2.area() == romb1.area());
    
    std::cout << "Romb tests passed!\n";
}

void test_array() {
    std::cout << "Testing Array class...\n";
    
    Array<std::shared_ptr<Figure<int>>> figures;
    
    // Тест push_back и size
    assert(figures.size() == 0);
    
    auto rect1 = std::make_shared<Rectangle<int>>(0, 0, 5, 3);
    figures.push_back(rect1);
    assert(figures.size() == 1);
    
    auto romb1 = std::make_shared<Romb<int>>(0, 0, 6, 4);
    figures.push_back(romb1);
    assert(figures.size() == 2);
    
    // Тест operator[]
    assert(figures[0]->area() == 15.0);
    assert(std::abs(figures[1]->area() - 12.0) < 0.001);
    
    // Тест erase
    figures.erase(0);
    assert(figures.size() == 1);
    assert(std::abs(figures[0]->area() - 12.0) < 0.001);
    
    Array<std::shared_ptr<Figure<int>>> figures2(figures);
    assert(figures2.size() == figures.size());
    
    // Тест двигающего конструктора
    Array<std::shared_ptr<Figure<int>>> figures3(std::move(figures2));
    assert(figures3.size() == 1);
    assert(figures2.size() == 0);
    
    std::cout << "Array tests passed!\n";
}

void test_utils() {
    std::cout << "Testing utility functions...\n";

Array<std::shared_ptr<Figure<double>>> figures;
    
    // Добавление фигур
    figures.push_back(std::make_shared<Rectangle<double>>(0, 0, 5, 3));
    figures.push_back(std::make_shared<Romb<double>>(0, 0, 6, 4));
    figures.push_back(std::make_shared<Trapezoid<double>>(0, 0, 4, 0, 3, 3, 1, 3));
    
    // Тест функции total_area
    double total = total_area(figures);
    double expected_total = 15.0 + 12.0 + 9.0; // rectangle + romb + trapezoid
    assert(std::abs(total - expected_total) < 0.001);
    
    // Тест print_all_figures
    std::cout << "Testing print function (should see 3 figures):\n";
    print_all_figures(figures);
    
    std::cout << "Utility functions tests passed!\n";
}

void test_polymorphism() {
    std::cout << "Testing polymorphism...\n";
    
    Array<std::shared_ptr<Figure<double>>> figures;
    
    // Добавление разных типов фигур в одинаковую область
    figures.push_back(std::make_shared<Rectangle<double>>(0, 0, 4, 2));
    figures.push_back(std::make_shared<Trapezoid<double>>(0, 0, 3, 0, 2, 2, 1, 2));
    figures.push_back(std::make_shared<Romb<double>>(0, 0, 4, 4));
    
    // Проверка на полиморфичность всех фигур
    double total = 0.0;
    for (size_t i = 0; i < figures.size(); ++i) {
        total += figures[i]->area();
        Point<double> center = figures[i]->center();
        
        // Предположительно, у всех фигур одинаковая площадь и центр
        assert(figures[i]->area() > 0);
        assert(!std::isnan(center.x()) && !std::isnan(center.y()));
    }
    
    assert(total > 0);
    std::cout << "Polymorphism tests passed!\n";
}

void test_edge_cases() {
    std::cout << "Testing edge cases...\n";
    
    // Разные скалярные типы
    Rectangle<float> rect_float(0.0f, 0.0f, 5.0f, 3.0f);
    assert(rect_float.area() == 15.0f);
    
    Rectangle<long> rect_long(0, 0, 5, 3);
    assert(rect_long.area() == 15.0);
    
    // Нулевая площадь
    Rectangle<int> zero_rect(0, 0, 0, 5);
    assert(zero_rect.area() == 0.0);
    
    // Отрицательные координаты
    Rectangle<int> neg_rect(-5, -5, 10, 10);
    assert(neg_rect.area() == 100.0);
    
    // Пустая область
    Array<std::shared_ptr<Figure<int>>> empty_array;
    assert(empty_array.size() == 0);
    assert(total_area(empty_array) == 0.0);
    
    std::cout << "Edge cases tests passed!\n";
}

void run_all_tests() {
    std::cout << "=== Starting All Tests ===\n\n";
    
    try {
        test_point();
        std::cout << std::endl;
        
        test_rectangle();
        std::cout << std::endl;
        
        test_trapezoid();
        std::cout << std::endl;
        
        test_romb();
        std::cout << std::endl;
        
        test_array();
        std::cout << std::endl;
        
        test_utils();
        std::cout << std::endl;
        
        test_polymorphism();
        std::cout << std::endl;
        
        test_edge_cases();
        std::cout << std::endl;
        
        std::cout << "=== All Tests Passed! ===\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
    }
}

int main() {
    run_all_tests();
    return 0;
}