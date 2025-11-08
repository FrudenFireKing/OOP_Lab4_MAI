#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <cstddef>

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
    
    void resize(size_t new_capacity) {
        auto new_data = std::make_unique<T[]>(new_capacity);
        
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }
        
        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }
    
public:
    Array() : size_(0), capacity_(10) {
        data_ = std::make_unique<T[]>(capacity_);
    }
    
    Array(size_t initial_capacity) : size_(0), capacity_(initial_capacity) {
        data_ = std::make_unique<T[]>(capacity_);
    }
    
    ~Array() = default;
    
    Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = std::make_unique<T[]>(capacity_);
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            auto new_data = std::make_unique<T[]>(other.capacity_);
            for (size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.data_[i];
            }
            data_ = std::move(new_data);
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }
    
    Array(Array&& other) noexcept 
        : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    void push_back(T value) {
        if (size_ >= capacity_) {
            resize(capacity_ * 2);
        }
        data_[size_++] = std::move(value);
    }
    
    void erase(size_t index) {
        if (index >= size_) return;
        
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
    }
    
    T& operator[](size_t index) {
        return data_[index];
    }
    
    const T& operator[](size_t index) const {
        return data_[index];
    }
    
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    
    T* begin() { return &data_[0]; }
    T* end() { return &data_[size_]; }
    const T* begin() const { return &data_[0]; }
    const T* end() const { return &data_[size_]; }
};

#endif