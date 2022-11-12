#include <algorithm>
#include <new>
#include "vector.h"

Vector::Iterator::Iterator() : ptr_(nullptr) {
}

Vector::Iterator::Iterator(ValueType* pointer) : ptr_(pointer) {
}

Vector::ValueType& Vector::Iterator::operator*() const {
    return *ptr_;
}

Vector::ValueType* Vector::Iterator::operator->() const {
    return ptr_;
}

Vector::Iterator& Vector::Iterator::operator=(Iterator other) {
    ptr_ = other.ptr_;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator++() {
    ++ptr_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Vector::Iterator it(*this);
    ++*this;
    return it;
}

Vector::Iterator& Vector::Iterator::operator--() {
    --ptr_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator--(int) {
    Vector::Iterator it(*this);
    --*this;
    return it;
}

Vector::Iterator Vector::Iterator::operator+(DifferenceType shift) {
    return Iterator(ptr_ + shift);
}

Vector::DifferenceType Vector::Iterator::operator-(Iterator other) {
    return ptr_ - other.ptr_;
}

Vector::Iterator& Vector::Iterator::operator+=(DifferenceType shift) {
    ptr_ += shift;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator-=(DifferenceType shift) {
    ptr_ -= shift;
    return *this;
}

Vector::Vector() : arr_(nullptr), size_(0), capacity_(0) {
}

Vector::Vector(size_t size) : size_(size), capacity_(size) {
    if (size == 0) {
        arr_ = nullptr;
        return;
    }
    arr_ = new ValueType[size_];
    for (SizeType i = 0; i < size_; ++i) {
        arr_[i] = 0;
    }
}

Vector::Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
    if (other.capacity_ == 0) {
        arr_ = nullptr;
        return;
    }
    arr_ = new ValueType[capacity_];
    for (SizeType i = 0; i < size_; ++i) {
        arr_[i] = other.arr_[i];
    }
}

Vector::Vector(std::initializer_list<ValueType> list) : size_(list.size()), capacity_(list.size()) {
    arr_ = new ValueType[size_];
    for (SizeType count = 0; ValueType i : list) {
        arr_[count] = i;
        ++count;
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }
    if (other.capacity_ == 0) {
        arr_ = nullptr;
        return *this;
    }
    ValueType* new_arr = new ValueType[other.size_];
    delete[] arr_;
    arr_ = new_arr;
    size_ = other.size_;
    capacity_ = other.capacity_;
    for (SizeType i = 0; i < size_; ++i) {
        arr_[i] = other.arr_[i];
    }
    return *this;
}

Vector::~Vector() {
    delete[] arr_;
}

Vector::SizeType Vector::Size() const {
    return size_;
}

Vector::SizeType Vector::Capacity() const {
    return capacity_;
}

const Vector::ValueType* Vector::Data() const {
    return arr_;
}

Vector::ValueType& Vector::operator[](size_t position) {
    return arr_[position];
}

Vector::ValueType Vector::operator[](size_t position) const {
    return arr_[position];
}

bool Vector::operator==(const Vector& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (SizeType i = 0; i < size_; ++i) {
        if (arr_[i] != other.arr_[i]) {
            return false;
        }
    }
    return true;
}

std::strong_ordering Vector::operator<=>(const Vector& other) const {
    for (SizeType i = 0; i < std::min(size_, other.size_); ++i) {
        if (arr_[i] < other.arr_[i]) {
            return std::strong_ordering::less;
        } else if (arr_[i] > other.arr_[i]) {
            return std::strong_ordering::greater;
        }
    }
    if (size_ < other.size_) {
        return std::strong_ordering::less;
    }
    if (size_ > other.size_) {
        return std::strong_ordering::greater;
    }
    return std::strong_ordering::equal;
}

void Vector::Reserve(SizeType new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    ValueType* new_arr = new ValueType[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_arr[i] = arr_[i];
    }
    delete[] arr_;
    arr_ = new_arr;
    capacity_ = new_capacity;
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::PushBack(const ValueType& new_element) {
    if (size_ >= capacity_) {
        if (size_ == 0) {
            Reserve(1);
        } else {
            Reserve(2 * capacity_);
        }
    }
    arr_[size_] = new_element;
    ++size_;
}

void Vector::PopBack() {
    --size_;
}

void Vector::Swap(Vector& other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(arr_, other.arr_);
}

Vector::Iterator Vector::Begin() {
    Iterator it(arr_);
    return it;
}

Vector::Iterator Vector::End() {
    Iterator it(arr_ + size_);
    return it;
}

Vector::Iterator Vector::begin() {
    return Begin();
}

Vector::Iterator Vector::end() {
    return End();
}
