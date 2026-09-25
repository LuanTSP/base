#pragma once

#include "vector.hpp"


/// A 2x2 matrix, stored column-major. Commonly used for 2D rotation and scaling.
class mat2 {
public:
    /// Creates an identity matrix.
    mat2();

    /// Creates a matrix from two column vectors.
    /// @param col0 First column.
    /// @param col1 Second column.
    mat2(const vec2& col0, const vec2& col1);

    /// Accesses a column by index (0 or 1).
    vec2& operator[](int col);

    /// Accesses a column by index (0 or 1), read-only.
    const vec2& operator[](int col) const;

    /// Multiplies two matrices.
    mat2 operator*(const mat2& rhs) const;

    /// Transforms a vector by this matrix.
    /// @param v The vector to transform.
    vec2 operator*(const vec2& v) const;

    /// Scales every element by a scalar.
    mat2 operator*(float scalar) const;

    /// Returns the determinant of the matrix.
    float determinant() const;

    /// Returns the transposed matrix.
    mat2 transposed() const;

    /// Returns the inverse of the matrix.
    /// @throws std::runtime_error if the matrix is not invertible.
    mat2 inverse() const;

    /// Returns a raw pointer to the underlying data, in column-major order.
    const float* value_ptr() const;

    /// Returns the identity matrix.
    static mat2 identity();

    /// Returns a rotation matrix.
    /// @param deg Angle in degrees, counter-clockwise.
    static mat2 rotate(float deg);

    /// Returns a scaling matrix.
    /// @param scale Scale factor for each axis.
    static mat2 scale(const vec2& scale);

private:
    vec2 columns[2];
};


/// A 3x3 matrix, stored column-major. Commonly used for normal transforms
/// and 2D transforms with translation (via homogeneous coordinates).
class mat3 {
public:
    /// Creates an identity matrix.
    mat3();

    /// Creates a matrix from three column vectors.
    /// @param col0 First column.
    /// @param col1 Second column.
    /// @param col2 Third column.
    mat3(
        const vec3& col0,
        const vec3& col1,
        const vec3& col2
    );

    /// Accesses a column by index (0 to 2).
    vec3& operator[](int col);

    /// Accesses a column by index (0 to 2), read-only.
    const vec3& operator[](int col) const;

    /// Multiplies two matrices.
    mat3 operator*(const mat3& rhs) const;

    /// Transforms a vector by this matrix.
    /// @param v The vector to transform.
    vec3 operator*(const vec3& v) const;

    /// Scales every element by a scalar.
    mat3 operator*(float scalar) const;

    /// Returns the determinant of the matrix.
    float determinant() const;

    /// Returns the transposed matrix.
    mat3 transposed() const;

    /// Returns the inverse of the matrix.
    /// @throws std::runtime_error if the matrix is not invertible.
    mat3 inverse() const;

    /// Returns the upper-left 2x2 block of this matrix.
    mat2 toMat2() const;

    /// Returns a raw pointer to the underlying data, in column-major order.
    const float* value_ptr() const;

    /// Returns the identity matrix.
    static mat3 identity();

    /// Returns a scaling matrix.
    /// @param scale Scale factor for each axis.
    static mat3 scale(const vec3& scale);

    /// Returns a rotation matrix around an arbitrary axis.
    /// @param axis Rotation axis (assumed to be normalized).
    /// @param deg Angle in degrees.
    static mat3 rotate(const vec3& axis, float deg);

private:
    vec3 columns[3];
};


/// A 4x4 matrix, stored column-major (matches OpenGL's expected layout).
/// The main matrix type for 3D transforms, projections and cameras.
class mat4 {
public:
    /// Creates an identity matrix.
    mat4();

    /// Creates a matrix from four column vectors.
    /// @param col0 First column.
    /// @param col1 Second column.
    /// @param col2 Third column.
    /// @param col3 Fourth column.
    mat4(
        const vec4& col0,
        const vec4& col1,
        const vec4& col2,
        const vec4& col3
    );

    /// Accesses a column by index (0 to 3).
    vec4& operator[](int col);

    /// Accesses a column by index (0 to 3), read-only.
    const vec4& operator[](int col) const;

    /// Multiplies two matrices.
    mat4 operator*(const mat4& rhs) const;

    /// Transforms a vector by this matrix.
    /// @param v The vector to transform.
    vec4 operator*(const vec4& v) const;

    /// Scales every element by a scalar.
    mat4 operator*(float scalar) const;

    /// Returns the transposed matrix.
    mat4 transposed() const;

    /// Returns the upper-left 3x3 block of this matrix (useful for normal matrices).
    mat3 toMat3() const;

    /// Returns the determinant of the matrix.
    float determinant() const;

    /// Returns the inverse of the matrix.
    /// @throws std::runtime_error if the matrix is not invertible.
    mat4 inverse() const;

    /// Returns a raw pointer to the underlying data, in column-major order.
    /// Pass this directly to glUniformMatrix4fv.
    const float* value_ptr() const;

    /// Returns the identity matrix.
    static mat4 identity();

    /// Returns a translation matrix.
    /// @param t The translation vector.
    static mat4 translate(const vec3& t);

    /// Returns a scaling matrix.
    /// @param s Scale factor for each axis.
    static mat4 scale(const vec3& s);

    /// Returns a rotation matrix around an arbitrary axis.
    /// @param axis Rotation axis (assumed to be normalized).
    /// @param deg Angle in degrees.
    static mat4 rotate(const vec3& axis, float deg);

    /// Builds a view matrix looking from eye towards target.
    /// @param eye Camera position in world space.
    /// @param target Point the camera looks at.
    /// @param worldUp World "up" direction, typically (0, 1, 0).
    static mat4 lookAt(
        const vec3& eye,
        const vec3& target,
        const vec3& worldUp
    );

    /// Builds a perspective projection matrix.
    /// @param fovYDeg Vertical field of view, in degrees.
    /// @param aspect Aspect ratio (width / height).
    /// @param nearPlane Distance to the near clipping plane.
    /// @param farPlane Distance to the far clipping plane.
    static mat4 perspective(
        float fovYDeg,
        float aspect,
        float nearPlane,
        float farPlane
    );

    /// Builds an orthographic projection matrix.
    /// @param left Left clipping plane.
    /// @param right Right clipping plane.
    /// @param bottom Bottom clipping plane.
    /// @param top Top clipping plane.
    /// @param nearPlane Distance to the near clipping plane.
    /// @param farPlane Distance to the far clipping plane.
    static mat4 orthographic(
        float left,
        float right,
        float bottom,
        float top,
        float nearPlane,
        float farPlane
    );

private:
    vec4 columns[4];
};