#ifndef ROMB_H
#define ROMB_H

#include "figure.h"

template<Scalar T>
class Romb : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1_, p2_, p3_, p4_;
    
public:
    Romb(T center_x, T center_y, T horizontal_diag, T vertical_diag) {
        T half_h = horizontal_diag / 2;
        T half_v = vertical_diag / 2;
        
        p1_ = std::make_unique<Point<T>>(center_x - half_h, center_y);
        p2_ = std::make_unique<Point<T>>(center_x, center_y + half_v);
        p3_ = std::make_unique<Point<T>>(center_x + half_h, center_y);
        p4_ = std::make_unique<Point<T>>(center_x, center_y - half_v);
    }
    
    Romb(const Romb<T>& other) {
        Point<T> c = other.center();
        T d1 = other.p3_->x() - other.p1_->x();
        T d2 = other.p2_->y() - other.p4_->y();
        
        p1_ = std::make_unique<Point<T>>(c.x() - d1/2, c.y());
        p2_ = std::make_unique<Point<T>>(c.x(), c.y() + d2/2);
        p3_ = std::make_unique<Point<T>>(c.x() + d1/2, c.y());
        p4_ = std::make_unique<Point<T>>(c.x(), c.y() - d2/2);
    }
    
    Romb<T>& operator=(const Romb<T>& other) {
        if (this != &other) {
            Point<T> c = other.center();
            T d1 = other.p3_->x() - other.p1_->x();
            T d2 = other.p2_->y() - other.p4_->y();
            
            p1_ = std::make_unique<Point<T>>(c.x() - d1/2, c.y());
            p2_ = std::make_unique<Point<T>>(c.x(), c.y() + d2/2);
            p3_ = std::make_unique<Point<T>>(c.x() + d1/2, c.y());
            p4_ = std::make_unique<Point<T>>(c.x(), c.y() - d2/2);
        }
        return *this;
    }
    
    double area() const override {
        T d1 = p3_->x() - p1_->x();
        T d2 = p2_->y() - p4_->y();
        return std::abs(static_cast<double>(d1 * d2)) / 2.0;
    }
    
    Point<T> center() const override {
        T center_x = (p1_->x() + p3_->x()) / 2;
        T center_y = (p2_->y() + p4_->y()) / 2;
        return Point<T>(center_x, center_y);
    }
    
    void print(std::ostream& os) const override {
        os << "Romb: Points: " << *p1_ << ", " << *p2_ << ", " 
           << *p3_ << ", " << *p4_ << ", Center: " << center() 
           << ", Area: " << area();
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Romb<T>>(*this);
    }
    
    bool operator==(const Romb<T>& other) const {
        return center() == other.center() && area() == other.area();
    }
};

#endif
