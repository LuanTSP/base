// mat2.hpp
#pragma once
#include <cmath>
#include <stdexcept>
#include "vector.hpp"


/// A 2x2 matrix, stored column-major. Commonly used for 2D rotation and scaling.
class mat2 {
public:
    /// Creates an identity matrix.
    mat2() {
        columns[0] = vec2(1, 0);
        columns[1] = vec2(0, 1);
    }

    /// Creates a matrix from two column vectors.
    /// @param col0 First column.
    /// @param col1 Second column.
    mat2(const vec2& col0, const vec2& col1) {
        columns[0] = col0;
        columns[1] = col1;
    }

    /// Accesses a column by index (0 or 1).
    vec2& operator[](int col) { return columns[col]; }
    /// Accesses a column by index (0 or 1), read-only.
    const vec2& operator[](int col) const { return columns[col]; }

    /// Multiplies two matrices.
    mat2 operator*(const mat2& rhs) const {
        return mat2(
            (*this) * rhs.columns[0],
            (*this) * rhs.columns[1]
        );
    }

    /// Transforms a vector by this matrix.
    /// @param v The vector to transform.
    vec2 operator*(const vec2& v) const {
        return vec2(
            columns[0].x * v.x + columns[1].x * v.y,
            columns[0].y * v.x + columns[1].y * v.y
        );
    }

    /// Scales every element by a scalar.
    mat2 operator*(float scalar) const {
        return mat2(columns[0] * scalar, columns[1] * scalar);
    }

    /// Returns the determinant of the matrix.
    float determinant() const {
        return columns[0].x * columns[1].y - columns[1].x * columns[0].y;
    }

    /// Returns the transposed matrix.
    mat2 transposed() const {
        return mat2(
            vec2(columns[0].x, columns[1].x),
            vec2(columns[0].y, columns[1].y)
        );
    }

    /// Returns the inverse of the matrix.
    /// @throws std::runtime_error if the matrix is not invertible.
    mat2 inverse() const {
        float det = determinant();
        if (det == 0.0f)
            throw std::runtime_error("[ERROR]: mat2 is not invertible");

        float invDet = 1.0f / det;
        return mat2(
            vec2( columns[1].y * invDet, -columns[0].y * invDet),
            vec2(-columns[1].x * invDet,  columns[0].x * invDet)
        );
    }

    /// Returns a raw pointer to the underlying data, in column-major order.
    const float* value_ptr() const { return &columns[0].x; }

    /// Returns the identity matrix.
    static mat2 identity() { return mat2(); }

    /// Returns a rotation matrix.
    /// @param deg Angle in degrees, counter-clockwise.
    static mat2 rotate(float deg) {
        float rad = deg * PI / 180.0f;
        float c = std::cos(rad);
        float s = std::sin(rad);
        return mat2(vec2(c, s), vec2(-s, c));
    }

    /// Returns a scaling matrix.
    /// @param scale Scale factor for each axis.
    static mat2 scale(const vec2& scale) {
        return mat2(vec2(scale.x, 0), vec2(0, scale.y));
    }

private:
    vec2 columns[2];
};

/// A 3x3 matrix, stored column-major. Commonly used for normal transforms
/// and 2D transforms with translation (via homogeneous coordinates).
class mat3 {
public:
    /// Creates an identity matrix.
    mat3() {
        columns[0] = vec3(1, 0, 0);
        columns[1] = vec3(0, 1, 0);
        columns[2] = vec3(0, 0, 1);
    }

    /// Creates a matrix from three column vectors.
    /// @param col0 First column.
    /// @param col1 Second column.
    /// @param col2 Third column.
    mat3(const vec3& col0, const vec3& col1, const vec3& col2) {
        columns[0] = col0;
        columns[1] = col1;
        columns[2] = col2;
    }

    /// Accesses a column by index (0 to 2).
    vec3& operator[](int col) { return columns[col]; }
    /// Accesses a column by index (0 to 2), read-only.
    const vec3& operator[](int col) const { return columns[col]; }

    /// Multiplies two matrices.
    mat3 operator*(const mat3& rhs) const {
        return mat3(
            (*this) * rhs.columns[0],
            (*this) * rhs.columns[1],
            (*this) * rhs.columns[2]
        );
    }

    /// Transforms a vector by this matrix.
    /// @param v The vector to transform.
    vec3 operator*(const vec3& v) const {
        return vec3(
            columns[0].x * v.x + columns[1].x * v.y + columns[2].x * v.z,
            columns[0].y * v.x + columns[1].y * v.y + columns[2].y * v.z,
            columns[0].z * v.x + columns[1].z * v.y + columns[2].z * v.z
        );
    }

    /// Scales every element by a scalar.
    mat3 operator*(float scalar) const {
        return mat3(columns[0] * scalar, columns[1] * scalar, columns[2] * scalar);
    }

    /// Returns the determinant of the matrix.
    float determinant() const {
        return columns[0].x * (columns[1].y * columns[2].z - columns[2].y * columns[1].z)
             - columns[1].x * (columns[0].y * columns[2].z - columns[2].y * columns[0].z)
             + columns[2].x * (columns[0].y * columns[1].z - columns[1].y * columns[0].z);
    }

    /// Returns the transposed matrix.
    mat3 transposed() const {
        return mat3(
            vec3(columns[0].x, columns[1].x, columns[2].x),
            vec3(columns[0].y, columns[1].y, columns[2].y),
            vec3(columns[0].z, columns[1].z, columns[2].z)
        );
    }

    /// Returns the inverse of the matrix.
    /// @throws std::runtime_error if the matrix is not invertible.
    mat3 inverse() const {
        float det = determinant();
        if (det == 0.0f)
            throw std::runtime_error("[ERROR]: mat3 is not invertible");

        float invDet = 1.0f / det;

        vec3 c0(
            (columns[1].y * columns[2].z - columns[2].y * columns[1].z) * invDet,
            (columns[2].y * columns[0].z - columns[0].y * columns[2].z) * invDet,
            (columns[0].y * columns[1].z - columns[1].y * columns[0].z) * invDet
        );
        vec3 c1(
            (columns[2].x * columns[1].z - columns[1].x * columns[2].z) * invDet,
            (columns[0].x * columns[2].z - columns[2].x * columns[0].z) * invDet,
            (columns[1].x * columns[0].z - columns[0].x * columns[1].z) * invDet
        );
        vec3 c2(
            (columns[1].x * columns[2].y - columns[2].x * columns[1].y) * invDet,
            (columns[2].x * columns[0].y - columns[0].x * columns[2].y) * invDet,
            (columns[0].x * columns[1].y - columns[1].x * columns[0].y) * invDet
        );

        return mat3(c0, c1, c2);
    }

    /// Returns the upper-left 2x2 block of this matrix.
    mat2 toMat2() const {
        return mat2(vec2(columns[0].x, columns[0].y), vec2(columns[1].x, columns[1].y));
    }

    /// Returns a raw pointer to the underlying data, in column-major order.
    const float* value_ptr() const { return &columns[0].x; }

    /// Returns the identity matrix.
    static mat3 identity() { return mat3(); }

    /// Returns a scaling matrix.
    /// @param scale Scale factor for each axis.
    static mat3 scale(const vec3& scale) {
        return mat3(
            vec3(scale.x, 0, 0),
            vec3(0, scale.y, 0),
            vec3(0, 0, scale.z)
        );
    }

    /// Returns a rotation matrix around an arbitrary axis.
    /// @param axis Rotation axis (assumed to be normalized).
    /// @param deg Angle in degrees.
    static mat3 rotate(const vec3& axis, float deg) {
        float rad = deg * 3.14159265358979323846f / 180.0f;
        float c = std::cos(rad);
        float s = std::sin(rad);
        float t = 1.0f - c;

        float x = axis.x, y = axis.y, z = axis.z;

        return mat3(
            vec3(t * x * x + c,     t * x * y + s * z, t * x * z - s * y),
            vec3(t * x * y - s * z, t * y * y + c,     t * y * z + s * x),
            vec3(t * x * z + s * y, t * y * z - s * x, t * z * z + c)
        );
    }

private:
    vec3 columns[3];
};

/// A 4x4 matrix, stored column-major (matches OpenGL's expected layout).
/// The main matrix type for 3D transforms, projections and cameras.
class mat4 {
public:
    /// Creates an identity matrix.
    mat4() {
        columns[0] = vec4(1, 0, 0, 0);
        columns[1] = vec4(0, 1, 0, 0);
        columns[2] = vec4(0, 0, 1, 0);
        columns[3] = vec4(0, 0, 0, 1);
    }

    /// Creates a matrix from four column vectors.
    /// @param col0 First column.
    /// @param col1 Second column.
    /// @param col2 Third column.
    /// @param col3 Fourth column.
    mat4(const vec4& col0, const vec4& col1, const vec4& col2, const vec4& col3) {
        columns[0] = col0;
        columns[1] = col1;
        columns[2] = col2;
        columns[3] = col3;
    }

    /// Accesses a column by index (0 to 3).
    vec4& operator[](int col) { return columns[col]; }
    /// Accesses a column by index (0 to 3), read-only.
    const vec4& operator[](int col) const { return columns[col]; }

    /// Multiplies two matrices.
    mat4 operator*(const mat4& rhs) const {
        return mat4(
            (*this) * rhs.columns[0],
            (*this) * rhs.columns[1],
            (*this) * rhs.columns[2],
            (*this) * rhs.columns[3]
        );
    }

    /// Transforms a vector by this matrix.
    /// @param v The vector to transform.
    vec4 operator*(const vec4& v) const {
        return vec4(
            columns[0].x * v.x + columns[1].x * v.y + columns[2].x * v.z + columns[3].x * v.w,
            columns[0].y * v.x + columns[1].y * v.y + columns[2].y * v.z + columns[3].y * v.w,
            columns[0].z * v.x + columns[1].z * v.y + columns[2].z * v.z + columns[3].z * v.w,
            columns[0].w * v.x + columns[1].w * v.y + columns[2].w * v.z + columns[3].w * v.w
        );
    }

    /// Scales every element by a scalar.
    mat4 operator*(float scalar) const {
        return mat4(columns[0] * scalar, columns[1] * scalar,
                    columns[2] * scalar, columns[3] * scalar);
    }

    /// Returns the transposed matrix.
    mat4 transposed() const {
        return mat4(
            vec4(columns[0].x, columns[1].x, columns[2].x, columns[3].x),
            vec4(columns[0].y, columns[1].y, columns[2].y, columns[3].y),
            vec4(columns[0].z, columns[1].z, columns[2].z, columns[3].z),
            vec4(columns[0].w, columns[1].w, columns[2].w, columns[3].w)
        );
    }

    /// Returns the upper-left 3x3 block of this matrix (useful for normal matrices).
    mat3 toMat3() const {
        return mat3(
            vec3(columns[0].x, columns[0].y, columns[0].z),
            vec3(columns[1].x, columns[1].y, columns[1].z),
            vec3(columns[2].x, columns[2].y, columns[2].z)
        );
    }

    /// Returns the determinant of the matrix.
    float determinant() const {
        const float* m = value_ptr();

        float b00 = m[0]*m[5] - m[1]*m[4];
        float b01 = m[0]*m[6] - m[2]*m[4];
        float b02 = m[0]*m[7] - m[3]*m[4];
        float b03 = m[1]*m[6] - m[2]*m[5];
        float b04 = m[1]*m[7] - m[3]*m[5];
        float b05 = m[2]*m[7] - m[3]*m[6];
        float b06 = m[8]*m[13] - m[9]*m[12];
        float b07 = m[8]*m[14] - m[10]*m[12];
        float b08 = m[8]*m[15] - m[11]*m[12];
        float b09 = m[9]*m[14] - m[10]*m[13];
        float b10 = m[9]*m[15] - m[11]*m[13];
        float b11 = m[10]*m[15] - m[11]*m[14];

        return b00*b11 - b01*b10 + b02*b09 + b03*b08 - b04*b07 + b05*b06;
    }

    /// Returns the inverse of the matrix.
    /// @throws std::runtime_error if the matrix is not invertible.
    mat4 inverse() const {
        const float* m = value_ptr();

        float b00 = m[0]*m[5] - m[1]*m[4];
        float b01 = m[0]*m[6] - m[2]*m[4];
        float b02 = m[0]*m[7] - m[3]*m[4];
        float b03 = m[1]*m[6] - m[2]*m[5];
        float b04 = m[1]*m[7] - m[3]*m[5];
        float b05 = m[2]*m[7] - m[3]*m[6];
        float b06 = m[8]*m[13] - m[9]*m[12];
        float b07 = m[8]*m[14] - m[10]*m[12];
        float b08 = m[8]*m[15] - m[11]*m[12];
        float b09 = m[9]*m[14] - m[10]*m[13];
        float b10 = m[9]*m[15] - m[11]*m[13];
        float b11 = m[10]*m[15] - m[11]*m[14];

        float det = b00*b11 - b01*b10 + b02*b09 + b03*b08 - b04*b07 + b05*b06;
        if (det == 0.0f)
            throw std::runtime_error("[ERROR]: mat4 is not invertible");

        float invDet = 1.0f / det;

        float out[16];
        out[0]  = ( m[5]*b11 - m[6]*b10 + m[7]*b09) * invDet;
        out[1]  = (-m[1]*b11 + m[2]*b10 - m[3]*b09) * invDet;
        out[2]  = ( m[13]*b05 - m[14]*b04 + m[15]*b03) * invDet;
        out[3]  = (-m[9]*b05 + m[10]*b04 - m[11]*b03) * invDet;
        out[4]  = (-m[4]*b11 + m[6]*b08 - m[7]*b07) * invDet;
        out[5]  = ( m[0]*b11 - m[2]*b08 + m[3]*b07) * invDet;
        out[6]  = (-m[12]*b05 + m[14]*b02 - m[15]*b01) * invDet;
        out[7]  = ( m[8]*b05 - m[10]*b02 + m[11]*b01) * invDet;
        out[8]  = ( m[4]*b10 - m[5]*b08 + m[7]*b06) * invDet;
        out[9]  = (-m[0]*b10 + m[1]*b08 - m[3]*b06) * invDet;
        out[10] = ( m[12]*b04 - m[13]*b02 + m[15]*b00) * invDet;
        out[11] = (-m[8]*b04 + m[9]*b02 - m[11]*b00) * invDet;
        out[12] = (-m[4]*b09 + m[5]*b07 - m[6]*b06) * invDet;
        out[13] = ( m[0]*b09 - m[1]*b07 + m[2]*b06) * invDet;
        out[14] = (-m[12]*b03 + m[13]*b01 - m[14]*b00) * invDet;
        out[15] = ( m[8]*b03 - m[9]*b01 + m[10]*b00) * invDet;

        return mat4(
            vec4(out[0], out[1], out[2], out[3]),
            vec4(out[4], out[5], out[6], out[7]),
            vec4(out[8], out[9], out[10], out[11]),
            vec4(out[12], out[13], out[14], out[15])
        );
    }

    /// Returns a raw pointer to the underlying data, in column-major order.
    /// Pass this directly to glUniformMatrix4fv.
    const float* value_ptr() const { return &columns[0].x; }

    /// Returns the identity matrix.
    static mat4 identity() { return mat4(); }

    /// Returns a translation matrix.
    /// @param t The translation vector.
    static mat4 translate(const vec3& t) {
        mat4 m;
        m.columns[3] = vec4(t.x, t.y, t.z, 1.0f);
        return m;
    }

    /// Returns a scaling matrix.
    /// @param s Scale factor for each axis.
    static mat4 scale(const vec3& s) {
        mat4 m;
        m.columns[0].x = s.x;
        m.columns[1].y = s.y;
        m.columns[2].z = s.z;
        return m;
    }

    /// Returns a rotation matrix around an arbitrary axis.
    /// @param axis Rotation axis (assumed to be normalized).
    /// @param deg Angle in degrees.
    static mat4 rotate(const vec3& axis, float deg) {
        float rad = deg * 3.14159265358979323846f / 180.0f;
        float c = std::cos(rad);
        float s = std::sin(rad);
        float t = 1.0f - c;

        float x = axis.x, y = axis.y, z = axis.z;

        return mat4(
            vec4(t*x*x + c,     t*x*y + s*z, t*x*z - s*y, 0),
            vec4(t*x*y - s*z, t*y*y + c,     t*y*z + s*x, 0),
            vec4(t*x*z + s*y, t*y*z - s*x, t*z*z + c,     0),
            vec4(0, 0, 0, 1)
        );
    }

    /// Builds a view matrix looking from eye towards target.
    /// @param eye Camera position in world space.
    /// @param target Point the camera looks at.
    /// @param worldUp World "up" direction, typically (0, 1, 0).
    static mat4 lookAt(const vec3& eye, const vec3& target, const vec3& worldUp) {
        vec3 forward = (target - eye).normalized();
        vec3 right = forward.cross(worldUp).normalized();
        vec3 up = right.cross(forward);

        mat4 m;
        m.columns[0] = vec4(right.x, up.x, -forward.x, 0);
        m.columns[1] = vec4(right.y, up.y, -forward.y, 0);
        m.columns[2] = vec4(right.z, up.z, -forward.z, 0);
        m.columns[3] = vec4(-right.dot(eye), -up.dot(eye), forward.dot(eye), 1);
        return m;
    }

    /// Builds a perspective projection matrix.
    /// @param fovYDeg Vertical field of view, in degrees.
    /// @param aspect Aspect ratio (width / height).
    /// @param nearPlane Distance to the near clipping plane.
    /// @param farPlane Distance to the far clipping plane.
    static mat4 perspective(float fovYDeg, float aspect, float nearPlane, float farPlane) {
        float fovRad = fovYDeg * 3.14159265358979323846f / 180.0f;
        float f = 1.0f / std::tan(fovRad / 2.0f);

        mat4 m;
        m.columns[0] = vec4(f / aspect, 0, 0, 0);
        m.columns[1] = vec4(0, f, 0, 0);
        m.columns[2] = vec4(0, 0, (farPlane + nearPlane) / (nearPlane - farPlane), -1);
        m.columns[3] = vec4(0, 0, (2 * farPlane * nearPlane) / (nearPlane - farPlane), 0);
        return m;
    }

    /// Builds an orthographic projection matrix.
    /// @param left Left clipping plane.
    /// @param right Right clipping plane.
    /// @param bottom Bottom clipping plane.
    /// @param top Top clipping plane.
    /// @param nearPlane Distance to the near clipping plane.
    /// @param farPlane Distance to the far clipping plane.
    static mat4 orthographic(float left, float right, float bottom, float top,
                             float nearPlane, float farPlane) {
        mat4 m;
        m.columns[0] = vec4(2.0f / (right - left), 0, 0, 0);
        m.columns[1] = vec4(0, 2.0f / (top - bottom), 0, 0);
        m.columns[2] = vec4(0, 0, -2.0f / (farPlane - nearPlane), 0);
        m.columns[3] = vec4(
            -(right + left) / (right - left),
            -(top + bottom) / (top - bottom),
            -(farPlane + nearPlane) / (farPlane - nearPlane),
            1
        );
        return m;
    }

private:
    vec4 columns[4];
};