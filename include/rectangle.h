#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"

template<Scalar T>
class Rectangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1_, p2_, p3_, p4_;
    
    void calculate_points(T x, T y, T width, T height) {
        p1_ = std::make_unique<Point<T>>(x, y);
        p2_ = std::make_unique<Point<T>>(x + width, y);
        p3_ = std::make_unique<Point<T>>(x + width, y + height);
        p4_ = std::make_unique<Point<T>>(x, y + height);
    }
    
public:
    Rectangle(T x, T y, T width, T height) {
        calculate_points(x, y, width, height);
    }
    
    Rectangle(const Rectangle<T>& other) {
        calculate_points(other.p1_->x(), other.p1_->y(), 
                        other.p2_->x() - other.p1_->x(),
                        other.p4_->y() - other.p1_->y());
    }
    
    Rectangle<T>& operator=(const Rectangle<T>& other) {
        if (this != &other) {
            calculate_points(other.p1_->x(), other.p1_->y(), 
                            other.p2_->x() - other.p1_->x(),
                            other.p4_->y() - other.p1_->y());
        }
        return *this;
    }
    
    double area() const override {
        T width = p2_->x() - p1_->x();
        T height = p4_->y() - p1_->y();
        return std::abs(static_cast<double>(width * height));
    }
    
    Point<T> center() const override {
        T center_x = (p1_->x() + p3_->x()) / 2;
        T center_y = (p1_->y() + p3_->y()) / 2;
        return Point<T>(center_x, center_y);
    }
    
    void print(std::ostream& os) const override {
        os << "Rectangle: Points: " << *p1_ << ", " << *p2_ << ", " 
           << *p3_ << ", " << *p4_ << ", Center: " << center() 
           << ", Area: " << area();
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Rectangle<T>>(*this);
    }
    
    bool operator==(const Rectangle<T>& other) const {
        return *p1_ == *other.p1_ && *p3_ == *other.p3_;
    }
};

#endif