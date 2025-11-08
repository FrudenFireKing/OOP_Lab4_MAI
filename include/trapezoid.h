#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "figure.h"

template<Scalar T>
class Trapezoid : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1_, p2_, p3_, p4_;
    
public:
    Trapezoid(T x1, T y1, T x2, T y2, T x3, T y3, T x4, T y4) {
        p1_ = std::make_unique<Point<T>>(x1, y1);
        p2_ = std::make_unique<Point<T>>(x2, y2);
        p3_ = std::make_unique<Point<T>>(x3, y3);
        p4_ = std::make_unique<Point<T>>(x4, y4);
    }
    
    Trapezoid(const Trapezoid<T>& other) {
        p1_ = std::make_unique<Point<T>>(*other.p1_);
        p2_ = std::make_unique<Point<T>>(*other.p2_);
        p3_ = std::make_unique<Point<T>>(*other.p3_);
        p4_ = std::make_unique<Point<T>>(*other.p4_);
    }
    
    Trapezoid<T>& operator=(const Trapezoid<T>& other) {
        if (this != &other) {
            p1_ = std::make_unique<Point<T>>(*other.p1_);
            p2_ = std::make_unique<Point<T>>(*other.p2_);
            p3_ = std::make_unique<Point<T>>(*other.p3_);
            p4_ = std::make_unique<Point<T>>(*other.p4_);
        }
        return *this;
    }
    
    double area() const override {
        T base1 = std::abs(p2_->x() - p1_->x());  // нижнее основание
        T base2 = std::abs(p3_->x() - p4_->x());  // верхнее основание
        T height = std::abs(p4_->y() - p1_->y()); 
        
        return static_cast<double>((base1 + base2) * height) / 2.0;
    }
    
    Point<T> center() const override {
        T center_x = (p1_->x() + p2_->x() + p3_->x() + p4_->x()) / 4;
        T center_y = (p1_->y() + p2_->y() + p3_->y() + p4_->y()) / 4;
        return Point<T>(center_x, center_y);
    }
    
    void print(std::ostream& os) const override {
        os << "Trapezoid: Points: " << *p1_ << ", " << *p2_ << ", " 
           << *p3_ << ", " << *p4_ << ", Center: " << center() 
           << ", Area: " << area();
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Trapezoid<T>>(*this);
    }
    
    bool operator==(const Trapezoid<T>& other) const {
        return *p1_ == *other.p1_ && *p2_ == *other.p2_ && 
               *p3_ == *other.p3_ && *p4_ == *other.p4_;
    }
};

#endif