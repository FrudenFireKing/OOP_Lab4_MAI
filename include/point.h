#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <concepts>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
private:
    T x_, y_;
public:
    Point(T x = 0, T y = 0) : x_(x), y_(y) {}
    
    T x() const { return x_; }
    T y() const { return y_; }
    
    void set_x(T x) { x_ = x; }
    void set_y(T y) { y_ = y; }
    
    bool operator==(const Point<T>& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
    
    bool operator!=(const Point<T>& other) const {
        return !(*this == other);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
        os << "(" << point.x_ << ", " << point.y_ << ")";
        return os;
    }
};

#endif