#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <memory>
#include <iostream>

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    
    virtual double area() const = 0;
    virtual Point<T> center() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;
    
    explicit operator double() const {
        return area();
    }
    
    bool operator==(const Figure<T>& other) const {
        return this->area() == other.area();
    }
    
    bool operator!=(const Figure<T>& other) const {
        return !(*this == other);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
        figure.print(os);
        return os;
    }
};

#endif