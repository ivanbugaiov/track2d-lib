#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <cmath>
#include <iostream>

namespace track2d {

template <typename T>
class vector2d_t {
    friend std::ostream& operator<<(std::ostream& os, const vector2d_t<T>& vec) {
        os << vec.x << ", " << vec.y;
        return os;
    }

public:
    vector2d_t() : x(T(0)), y(T(0)) {}
    ~vector2d_t() {}
    vector2d_t(T in_x, T in_y) : x(T(in_x)), y(T(in_y)) {}
    vector2d_t(const vector2d_t& other) { *this = other; }
    vector2d_t& operator=(T val) { x = val; y = val; return *this; }
    vector2d_t& operator=(const vector2d_t& other);

    bool operator==(const vector2d_t& other) const { return ((x == other.x) && (y == other.y)); }
    bool operator!=(const vector2d_t& other) const { return ((x != other.x) && (y != other.y)); }

	vector2d_t operator+(const vector2d_t& other) const { vector2d_t res = *this; res += other; return res; }
    vector2d_t operator-(const vector2d_t& other) const { vector2d_t res = *this; res -= other; return res; }
    vector2d_t operator*(const vector2d_t& other) const { vector2d_t res = *this; res *= other; return res; }
    vector2d_t operator/(const vector2d_t& other) const { vector2d_t res = *this; res /= other; return res; }
    vector2d_t operator%(const vector2d_t& other) const { vector2d_t res = *this; res %= other; return res; }

    vector2d_t& operator+=(const vector2d_t& other) { x += other.x; y += other.y; return *this; }
    vector2d_t& operator-=(const vector2d_t& other) { x -= other.x; y -= other.y; return *this; }
    vector2d_t& operator*=(const vector2d_t& other) { x *= other.x; y *= other.y; return *this; }
    vector2d_t& operator/=(const vector2d_t& other) { x /= other.x; y /= other.y; return *this; }
    vector2d_t& operator%=(const vector2d_t& other) { x %= other.x; y %= other.y; return *this; }

	vector2d_t operator+(T val) const { vector2d_t res = *this; res += val; return res; }
    vector2d_t operator-(T val) const { vector2d_t res = *this; res -= val; return res; }
    vector2d_t operator*(T val) const { vector2d_t res = *this; res *= val; return res; }
    vector2d_t operator/(T val) const { vector2d_t res = *this; res /= val; return res; }
    vector2d_t operator%(T val) const { vector2d_t res = *this; res %= val; return res; }

	vector2d_t& operator+=(T val) { x += val; y += val; return *this; }
    vector2d_t& operator-=(T val) { x -= val; y -= val; return *this; }
    vector2d_t& operator*=(T val) { x *= val; y *= val; return *this; }
    vector2d_t& operator/=(T val) { x /= val; y /= val; return *this; }
    vector2d_t& operator%=(T val) { x %= val; y %= val; return *this; }    

    void set_zero() { x = T(0); y = T(0); }
    bool is_zero() const { return (x == T(0) && y == T(0)); }
    bool is_any_zero() const { return (x == T(0) || y == T(0)); }

    T length() const { return sqrt(x * x + y * y); }
    T angle() const { return atan2f(y, x); }
    T area() const { return x * y; }
 
    vector2d_t cartesian2polar() { return {length(), angle()}; }
    vector2d_t polar2cartesian() { return {x * cosf(y), x * sinf(y)}; }
    vector2d_t normalize(T val) const { return (*this) * (val / length()); }
    vector2d_t unit() const { return normalize(T(1)); }
    vector2d_t rotate(T angle) const {
        auto old = *this;
        return { old.x * cos(angle) - old.y * sin(angle), old.x * sin(angle) + old.y * cos(angle) };
    }
 
    vector2d_t abs() const { return {fabs(x), fabs(y)}; }
    vector2d_t swap_xy() const { return {y, x}; }
    const T& min() const { return (x < y) ? x : y; }
    const T& max() const { return (x > y) ? x : y; }
    T get_angle_between(const vector2d_t& other) const;
    T dot(const vector2d_t& other) const { return x * other.x + y * other.y; }

public:
    T x;
    T y;
}; // vector2d_t

template <typename T>
vector2d_t<T>& vector2d_t<T>::operator=(const vector2d_t<T>& other) {
    if (&other == this) { return *this; }
    x = other.x;
    y = other.y;
    return *this;
} // operator=

template <typename T>
T vector2d_t<T>::get_angle_between(const vector2d_t& other) const {
    vector2d_t<T> va(x, y);
    vector2d_t<T> vb(other.x, other.y);
    va.cartesian2polar();
    vb.cartesian2polar();
    return va.y - vb.y;
} // get_angle_between

} // namespace track2d

#endif // VECTOR2D_HPP
