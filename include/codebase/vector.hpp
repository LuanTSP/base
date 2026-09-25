// 2D vector
#pragma once
#include <cmath>
#include <stdexcept>
#include <ostream>

constexpr float PI = 3.14159265358979323846f;

/// A 2D vector with common linear algebra operations.
class vec2 {
public:
    float x = 0;
    float y = 0;

    /// Creates a zero vector (0, 0).
    vec2() = default;

    /// Creates a vector from two components.
    /// @param x First component.
    /// @param y Second component.
    vec2(float x, float y) : x(x), y(y) {}

    ~vec2() = default;

    /// Adds two vectors.
    vec2 operator+(const vec2& rhs) const { return vec2(x + rhs.x, y + rhs.y); }

    /// Subtracts two vectors.
    vec2 operator-(const vec2& rhs) const { return vec2(x - rhs.x, y - rhs.y); }

    /// Scales the vector by a scalar.
    vec2 operator*(float scalar) const { return vec2(x * scalar, y * scalar); }

    /// Divides the vector by a scalar.
    vec2 operator/(float scalar) const { return vec2(x / scalar, y / scalar); }

    /// Returns the vector with both components negated.
    vec2 operator-() const { return vec2(-x, -y); }

    /// Scales a vector by a scalar (scalar on the left side, e.g. 2.0f * v).
    friend vec2 operator*(float scalar, const vec2& rhs) {
        return vec2(rhs.x * scalar, rhs.y * scalar);
    }

    /// Adds rhs to this vector, in place.
    vec2& operator+=(const vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }

    /// Subtracts rhs from this vector, in place.
    vec2& operator-=(const vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

    /// Scales this vector, in place.
    vec2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }

    /// Divides this vector, in place.
    vec2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

    /// Checks if two vectors are equal.
    bool operator==(const vec2& rhs) const { return x == rhs.x && y == rhs.y; }

    /// Checks if two vectors are different.
    bool operator!=(const vec2& rhs) const { return !(*this == rhs); }

    /// Accesses a component by index: 0 for x, 1 for y.
    float& operator[](int i) { return i == 0 ? x : y; }

    /// Accesses a component by index: 0 for x, 1 for y (read-only).
    const float& operator[](int i) const { return i == 0 ? x : y; }

    /// Returns the dot product with another vector.
    /// @param v The other vector.
    float dot(const vec2& v) const { return x * v.x + y * v.y; }

    /// Returns the 2D cross product (a scalar): tells the rotation
    /// direction (sign) between this vector and v.
    /// @param v The other vector.
    float cross(const vec2& v) const { return x * v.y - y * v.x; }

    /// Returns the length (magnitude) of the vector.
    float length() const { return std::sqrt(x * x + y * y); }

    /// Returns the squared length. Cheaper than length(); use it when you
    /// only need to compare distances.
    float lengthSquared() const { return x * x + y * y; }

    /// Normalizes this vector to unit length, in place.
    /// @throws std::runtime_error if the vector is zero.
    vec2& normalize() {
        float len = length();
        if (len <= 0.0f)
            throw std::runtime_error("[ERROR]: Tried to normalize a zero vec2");

        x /= len;
        y /= len;
        return *this;
    }

    /// Returns a normalized copy of this vector, without modifying it.
    /// @throws std::runtime_error if the vector is zero.
    vec2 normalized() const {
        vec2 copy = *this;
        return copy.normalize();
    }

    /// Rotates this vector by an angle, in place.
    /// @param deg Angle in degrees, counter-clockwise.
    vec2& rotateDegrees(float deg) {
        float rad = deg * PI / 180.0f;
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);

        float newX = x * cosA - y * sinA;
        float newY = x * sinA + y * cosA;

        x = newX;
        y = newY;
        return *this;
    }

    /// Returns a rotated copy of this vector, without modifying it.
    /// @param deg Angle in degrees, counter-clockwise.
    vec2 rotatedDegrees(float deg) const {
        vec2 copy = *this;
        return copy.rotateDegrees(deg);
    }

    /// Returns a vector perpendicular to this one (rotated 90° counter-clockwise).
    vec2 perpendicular() const { return vec2(-y, x); }

    /// Reflects this vector around a normal, in place.
    /// @param n The surface normal (assumed to be normalized).
    vec2& reflect(const vec2& n) {
        float d = dot(n);
        x = x - 2.0f * d * n.x;
        y = y - 2.0f * d * n.y;
        return *this;
    }

    /// Returns the distance to another point.
    /// @param v The other point.
    float distance(const vec2& v) const { return (*this - v).length(); }

    /// Returns the squared distance to another point. Cheaper than distance().
    /// @param v The other point.
    float distanceSquared(const vec2& v) const { return (*this - v).lengthSquared(); }

    /// Linearly interpolates between this vector and target.
    /// @param target The destination vector.
    /// @param t Interpolation factor, typically between 0 and 1.
    vec2 lerp(const vec2& target, float t) const {
        return *this + (target - *this) * t;
    }

    /// Returns (0, 0).
    static vec2 zero()  { return vec2(0, 0); }
    /// Returns (1, 1).
    static vec2 one()   { return vec2(1, 1); }
    /// Returns (0, 1).
    static vec2 up()    { return vec2(0, 1); }
    /// Returns (0, -1).
    static vec2 down()  { return vec2(0, -1); }
    /// Returns (-1, 0).
    static vec2 left()  { return vec2(-1, 0); }
    /// Returns (1, 0).
    static vec2 right() { return vec2(1, 0); }
};

/// Prints a vector as "(x, y)", useful for debugging with std::cout.
inline std::ostream& operator<<(std::ostream& os, const vec2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

/// A 3D vector with common linear algebra operations.
class vec3 {
public:
    float x = 0;
    float y = 0;
    float z = 0;

    /// Creates a zero vector (0, 0, 0).
    vec3() = default;

    /// Creates a vector from three components.
    /// @param x First component.
    /// @param y Second component.
    /// @param z Third component.
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    /// Creates a vector from a vec2 and a z component.
    /// @param xy The x and y components.
    /// @param z The z component.
    vec3(const vec2& xy, float z) : x(xy.x), y(xy.y), z(z) {}

    ~vec3() = default;

    /// Adds two vectors.
    vec3 operator+(const vec3& rhs) const { return vec3(x + rhs.x, y + rhs.y, z + rhs.z); }

    /// Subtracts two vectors.
    vec3 operator-(const vec3& rhs) const { return vec3(x - rhs.x, y - rhs.y, z - rhs.z); }

    /// Scales the vector by a scalar.
    vec3 operator*(float scalar) const { return vec3(x * scalar, y * scalar, z * scalar); }

    /// Divides the vector by a scalar.
    vec3 operator/(float scalar) const { return vec3(x / scalar, y / scalar, z / scalar); }

    /// Returns the vector with all components negated.
    vec3 operator-() const { return vec3(-x, -y, -z); }

    /// Scales a vector by a scalar (scalar on the left side, e.g. 2.0f * v).
    friend vec3 operator*(float scalar, const vec3& rhs) {
        return vec3(rhs.x * scalar, rhs.y * scalar, rhs.z * scalar);
    }

    /// Adds rhs to this vector, in place.
    vec3& operator+=(const vec3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }

    /// Subtracts rhs from this vector, in place.
    vec3& operator-=(const vec3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }

    /// Scales this vector, in place.
    vec3& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }

    /// Divides this vector, in place.
    vec3& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

    /// Checks if two vectors are equal.
    bool operator==(const vec3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }

    /// Checks if two vectors are different.
    bool operator!=(const vec3& rhs) const { return !(*this == rhs); }

    /// Accesses a component by index: 0 for x, 1 for y, 2 for z.
    float& operator[](int i) { return i == 0 ? x : (i == 1 ? y : z); }

    /// Accesses a component by index: 0 for x, 1 for y, 2 for z (read-only).
    const float& operator[](int i) const { return i == 0 ? x : (i == 1 ? y : z); }

    /// Returns the x and y components as a vec2, discarding z.
    vec2 xy() const { return vec2(x, y); }

    /// Returns the dot product with another vector.
    /// @param v The other vector.
    float dot(const vec3& v) const { return x * v.x + y * v.y + z * v.z; }

    /// Returns the cross product with another vector.
    /// @param v The other vector.
    vec3 cross(const vec3& v) const {
        return vec3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    /// Returns the length (magnitude) of the vector.
    float length() const { return std::sqrt(x * x + y * y + z * z); }

    /// Returns the squared length. Cheaper than length(); use it when you
    /// only need to compare distances.
    float lengthSquared() const { return x * x + y * y + z * z; }

    /// Normalizes this vector to unit length, in place.
    /// @throws std::runtime_error if the vector is zero.
    vec3& normalize() {
        float len = length();
        if (len <= 0.0f)
            throw std::runtime_error("[ERROR]: Tried to normalize a zero vec3");

        x /= len;
        y /= len;
        z /= len;
        return *this;
    }

    /// Returns a normalized copy of this vector, without modifying it.
    /// @throws std::runtime_error if the vector is zero.
    vec3 normalized() const {
        vec3 copy = *this;
        return copy.normalize();
    }

    /// Reflects this vector around a normal, in place.
    /// @param n The surface normal (assumed to be normalized).
    vec3& reflect(const vec3& n) {
        float d = dot(n);
        x = x - 2.0f * d * n.x;
        y = y - 2.0f * d * n.y;
        z = z - 2.0f * d * n.z;
        return *this;
    }

    /// Returns the distance to another point.
    /// @param v The other point.
    float distance(const vec3& v) const { return (*this - v).length(); }

    /// Returns the squared distance to another point. Cheaper than distance().
    /// @param v The other point.
    float distanceSquared(const vec3& v) const { return (*this - v).lengthSquared(); }

    /// Linearly interpolates between this vector and target.
    /// @param target The destination vector.
    /// @param t Interpolation factor, typically between 0 and 1.
    vec3 lerp(const vec3& target, float t) const {
        return *this + (target - *this) * t;
    }

    /// Returns (0, 0, 0).
    static vec3 zero()  { return vec3(0, 0, 0); }
    /// Returns (1, 1, 1).
    static vec3 one()   { return vec3(1, 1, 1); }
    /// Returns (0, 1, 0).
    static vec3 up()    { return vec3(0, 1, 0); }
    /// Returns (0, -1, 0).
    static vec3 down()  { return vec3(0, -1, 0); }
    /// Returns (-1, 0, 0).
    static vec3 left()  { return vec3(-1, 0, 0); }
    /// Returns (1, 0, 0).
    static vec3 right() { return vec3(1, 0, 0); }
    /// Returns (0, 0, 1).
    static vec3 forward() { return vec3(0, 0, 1); }
    /// Returns (0, 0, -1).
    static vec3 backward() { return vec3(0, 0, -1); }
};

/// Prints a vector as "(x, y, z)", useful for debugging with std::cout.
inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

class vec4 {
public:
    float x = 0;
    float y = 0;
    float z = 0;
    float w = 0;

    /// Creates a zero vector (0, 0, 0, 0).
    vec4() = default;

    /// Creates a vector from four components.
    /// @param x First component.
    /// @param y Second component.
    /// @param z Third component.
    /// @param w Fourth component.
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    /// Creates a vector from a vec3 and a w component.
    /// @param xyz The x, y and z components.
    /// @param w The w component.
    vec4(const vec3& xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

    ~vec4() = default;

    /// Adds two vectors.
    vec4 operator+(const vec4& rhs) const { return vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }

    /// Subtracts two vectors.
    vec4 operator-(const vec4& rhs) const { return vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }

    /// Scales the vector by a scalar.
    vec4 operator*(float scalar) const { return vec4(x * scalar, y * scalar, z * scalar, w * scalar); }

    /// Divides the vector by a scalar.
    vec4 operator/(float scalar) const { return vec4(x / scalar, y / scalar, z / scalar, w / scalar); }

    /// Returns the vector with all components negated.
    vec4 operator-() const { return vec4(-x, -y, -z, -w); }

    /// Scales a vector by a scalar (scalar on the left side, e.g. 2.0f * v).
    friend vec4 operator*(float scalar, const vec4& rhs) {
        return vec4(rhs.x * scalar, rhs.y * scalar, rhs.z * scalar, rhs.w * scalar);
    }

    /// Adds rhs to this vector, in place.
    vec4& operator+=(const vec4& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w; return *this; }

    /// Subtracts rhs from this vector, in place.
    vec4& operator-=(const vec4& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w; return *this; }

    /// Scales this vector, in place.
    vec4& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }

    /// Divides this vector, in place.
    vec4& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }

    /// Checks if two vectors are equal.
    bool operator==(const vec4& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
    }

    /// Checks if two vectors are different.
    bool operator!=(const vec4& rhs) const { return !(*this == rhs); }

    /// Accesses a component by index: 0 for x, 1 for y, 2 for z, 3 for w.
    float& operator[](int i) {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return w;
        }
    }

    /// Accesses a component by index: 0 for x, 1 for y, 2 for z, 3 for w (read-only).
    const float& operator[](int i) const {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return w;
        }
    }

    /// Returns the x, y and z components as a vec3, discarding w.
    vec3 xyz() const { return vec3(x, y, z); }

    /// Returns the dot product with another vector.
    /// @param v The other vector.
    float dot(const vec4& v) const { return x * v.x + y * v.y + z * v.z + w * v.w; }

    /// Returns the length (magnitude) of the vector.
    float length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

    /// Returns the squared length. Cheaper than length(); use it when you
    /// only need to compare distances.
    float lengthSquared() const { return x * x + y * y + z * z + w * w; }

    /// Normalizes this vector to unit length, in place.
    /// @throws std::runtime_error if the vector is zero.
    vec4& normalize() {
        float len = length();
        if (len <= 0.0f)
            throw std::runtime_error("[ERROR]: Tried to normalize a zero vec4");

        x /= len;
        y /= len;
        z /= len;
        w /= len;
        return *this;
    }

    /// Returns a normalized copy of this vector, without modifying it.
    /// @throws std::runtime_error if the vector is zero.
    vec4 normalized() const {
        vec4 copy = *this;
        return copy.normalize();
    }

    /// Linearly interpolates between this vector and target.
    /// @param target The destination vector.
    /// @param t Interpolation factor, typically between 0 and 1.
    vec4 lerp(const vec4& target, float t) const {
        return *this + (target - *this) * t;
    }

    /// Returns (0, 0, 0, 0).
    static vec4 zero() { return vec4(0, 0, 0, 0); }
    /// Returns (1, 1, 1, 1).
    static vec4 one()  { return vec4(1, 1, 1, 1); }
};

/// Prints a vector as "(x, y, z, w)", useful for debugging with std::cout.
inline std::ostream& operator<<(std::ostream& os, const vec4& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}