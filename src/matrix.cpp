#include "../include/codebase/matrix.hpp"

#include <cmath>
#include <stdexcept>


// ============================================================
// mat2
// ============================================================

mat2::mat2() {
    columns[0] = vec2(1, 0);
    columns[1] = vec2(0, 1);
}

mat2::mat2(const vec2& col0, const vec2& col1) {
    columns[0] = col0;
    columns[1] = col1;
}

vec2& mat2::operator[](int col) {
    return columns[col];
}

const vec2& mat2::operator[](int col) const {
    return columns[col];
}

mat2 mat2::operator*(const mat2& rhs) const {
    return mat2(
        (*this) * rhs.columns[0],
        (*this) * rhs.columns[1]
    );
}

vec2 mat2::operator*(const vec2& v) const {
    return vec2(
        columns[0].x * v.x + columns[1].x * v.y,
        columns[0].y * v.x + columns[1].y * v.y
    );
}

mat2 mat2::operator*(float scalar) const {
    return mat2(
        columns[0] * scalar,
        columns[1] * scalar
    );
}

float mat2::determinant() const {
    return columns[0].x * columns[1].y
         - columns[1].x * columns[0].y;
}

mat2 mat2::transposed() const {
    return mat2(
        vec2(columns[0].x, columns[1].x),
        vec2(columns[0].y, columns[1].y)
    );
}

mat2 mat2::inverse() const {
    float det = determinant();

    if (det == 0.0f)
        throw std::runtime_error("[ERROR]: mat2 is not invertible");

    float invDet = 1.0f / det;

    return mat2(
        vec2(
            columns[1].y * invDet,
            -columns[0].y * invDet
        ),
        vec2(
            -columns[1].x * invDet,
            columns[0].x * invDet
        )
    );
}

const float* mat2::value_ptr() const {
    return &columns[0].x;
}

mat2 mat2::identity() {
    return mat2();
}

mat2 mat2::rotate(float deg) {
    float rad = deg * PI / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);

    return mat2(
        vec2(c, s),
        vec2(-s, c)
    );
}

mat2 mat2::scale(const vec2& scale) {
    return mat2(
        vec2(scale.x, 0),
        vec2(0, scale.y)
    );
}


// ============================================================
// mat3
// ============================================================

mat3::mat3() {
    columns[0] = vec3(1, 0, 0);
    columns[1] = vec3(0, 1, 0);
    columns[2] = vec3(0, 0, 1);
}

mat3::mat3(
    const vec3& col0,
    const vec3& col1,
    const vec3& col2
) {
    columns[0] = col0;
    columns[1] = col1;
    columns[2] = col2;
}

vec3& mat3::operator[](int col) {
    return columns[col];
}

const vec3& mat3::operator[](int col) const {
    return columns[col];
}

mat3 mat3::operator*(const mat3& rhs) const {
    return mat3(
        (*this) * rhs.columns[0],
        (*this) * rhs.columns[1],
        (*this) * rhs.columns[2]
    );
}

vec3 mat3::operator*(const vec3& v) const {
    return vec3(
        columns[0].x * v.x
            + columns[1].x * v.y
            + columns[2].x * v.z,

        columns[0].y * v.x
            + columns[1].y * v.y
            + columns[2].y * v.z,

        columns[0].z * v.x
            + columns[1].z * v.y
            + columns[2].z * v.z
    );
}

mat3 mat3::operator*(float scalar) const {
    return mat3(
        columns[0] * scalar,
        columns[1] * scalar,
        columns[2] * scalar
    );
}

float mat3::determinant() const {
    return columns[0].x *
               (columns[1].y * columns[2].z
                - columns[2].y * columns[1].z)
         - columns[1].x *
               (columns[0].y * columns[2].z
                - columns[2].y * columns[0].z)
         + columns[2].x *
               (columns[0].y * columns[1].z
                - columns[1].y * columns[0].z);
}

mat3 mat3::transposed() const {
    return mat3(
        vec3(columns[0].x, columns[1].x, columns[2].x),
        vec3(columns[0].y, columns[1].y, columns[2].y),
        vec3(columns[0].z, columns[1].z, columns[2].z)
    );
}

mat3 mat3::inverse() const {
    float det = determinant();

    if (det == 0.0f)
        throw std::runtime_error("[ERROR]: mat3 is not invertible");

    float invDet = 1.0f / det;

    vec3 c0(
        (columns[1].y * columns[2].z
            - columns[2].y * columns[1].z) * invDet,

        (columns[2].y * columns[0].z
            - columns[0].y * columns[2].z) * invDet,

        (columns[0].y * columns[1].z
            - columns[1].y * columns[0].z) * invDet
    );

    vec3 c1(
        (columns[2].x * columns[1].z
            - columns[1].x * columns[2].z) * invDet,

        (columns[0].x * columns[2].z
            - columns[2].x * columns[0].z) * invDet,

        (columns[1].x * columns[0].z
            - columns[0].x * columns[1].z) * invDet
    );

    vec3 c2(
        (columns[1].x * columns[2].y
            - columns[2].x * columns[1].y) * invDet,

        (columns[2].x * columns[0].y
            - columns[0].x * columns[2].y) * invDet,

        (columns[0].x * columns[1].y
            - columns[1].x * columns[0].y) * invDet
    );

    return mat3(c0, c1, c2);
}

mat2 mat3::toMat2() const {
    return mat2(
        vec2(columns[0].x, columns[0].y),
        vec2(columns[1].x, columns[1].y)
    );
}

const float* mat3::value_ptr() const {
    return &columns[0].x;
}

mat3 mat3::identity() {
    return mat3();
}

mat3 mat3::scale(const vec3& scale) {
    return mat3(
        vec3(scale.x, 0, 0),
        vec3(0, scale.y, 0),
        vec3(0, 0, scale.z)
    );
}

mat3 mat3::rotate(const vec3& axis, float deg) {
    float rad = deg * 3.14159265358979323846f / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);
    float t = 1.0f - c;

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    return mat3(
        vec3(
            t * x * x + c,
            t * x * y + s * z,
            t * x * z - s * y
        ),

        vec3(
            t * x * y - s * z,
            t * y * y + c,
            t * y * z + s * x
        ),

        vec3(
            t * x * z + s * y,
            t * y * z - s * x,
            t * z * z + c
        )
    );
}


// ============================================================
// mat4
// ============================================================

mat4::mat4() {
    columns[0] = vec4(1, 0, 0, 0);
    columns[1] = vec4(0, 1, 0, 0);
    columns[2] = vec4(0, 0, 1, 0);
    columns[3] = vec4(0, 0, 0, 1);
}

mat4::mat4(
    const vec4& col0,
    const vec4& col1,
    const vec4& col2,
    const vec4& col3
) {
    columns[0] = col0;
    columns[1] = col1;
    columns[2] = col2;
    columns[3] = col3;
}

vec4& mat4::operator[](int col) {
    return columns[col];
}

const vec4& mat4::operator[](int col) const {
    return columns[col];
}

mat4 mat4::operator*(const mat4& rhs) const {
    return mat4(
        (*this) * rhs.columns[0],
        (*this) * rhs.columns[1],
        (*this) * rhs.columns[2],
        (*this) * rhs.columns[3]
    );
}

vec4 mat4::operator*(const vec4& v) const {
    return vec4(
        columns[0].x * v.x
            + columns[1].x * v.y
            + columns[2].x * v.z
            + columns[3].x * v.w,

        columns[0].y * v.x
            + columns[1].y * v.y
            + columns[2].y * v.z
            + columns[3].y * v.w,

        columns[0].z * v.x
            + columns[1].z * v.y
            + columns[2].z * v.z
            + columns[3].z * v.w,

        columns[0].w * v.x
            + columns[1].w * v.y
            + columns[2].w * v.z
            + columns[3].w * v.w
    );
}

mat4 mat4::operator*(float scalar) const {
    return mat4(
        columns[0] * scalar,
        columns[1] * scalar,
        columns[2] * scalar,
        columns[3] * scalar
    );
}

mat4 mat4::transposed() const {
    return mat4(
        vec4(columns[0].x, columns[1].x, columns[2].x, columns[3].x),
        vec4(columns[0].y, columns[1].y, columns[2].y, columns[3].y),
        vec4(columns[0].z, columns[1].z, columns[2].z, columns[3].z),
        vec4(columns[0].w, columns[1].w, columns[2].w, columns[3].w)
    );
}

mat3 mat4::toMat3() const {
    return mat3(
        vec3(columns[0].x, columns[0].y, columns[0].z),
        vec3(columns[1].x, columns[1].y, columns[1].z),
        vec3(columns[2].x, columns[2].y, columns[2].z)
    );
}

float mat4::determinant() const {
    const float* m = value_ptr();

    float b00 = m[0] * m[5] - m[1] * m[4];
    float b01 = m[0] * m[6] - m[2] * m[4];
    float b02 = m[0] * m[7] - m[3] * m[4];
    float b03 = m[1] * m[6] - m[2] * m[5];
    float b04 = m[1] * m[7] - m[3] * m[5];
    float b05 = m[2] * m[7] - m[3] * m[6];
    float b06 = m[8] * m[13] - m[9] * m[12];
    float b07 = m[8] * m[14] - m[10] * m[12];
    float b08 = m[8] * m[15] - m[11] * m[12];
    float b09 = m[9] * m[14] - m[10] * m[13];
    float b10 = m[9] * m[15] - m[11] * m[13];
    float b11 = m[10] * m[15] - m[11] * m[14];

    return b00 * b11
         - b01 * b10
         + b02 * b09
         + b03 * b08
         - b04 * b07
         + b05 * b06;
}

mat4 mat4::inverse() const {
    const float* m = value_ptr();

    float b00 = m[0] * m[5] - m[1] * m[4];
    float b01 = m[0] * m[6] - m[2] * m[4];
    float b02 = m[0] * m[7] - m[3] * m[4];
    float b03 = m[1] * m[6] - m[2] * m[5];
    float b04 = m[1] * m[7] - m[3] * m[5];
    float b05 = m[2] * m[7] - m[3] * m[6];
    float b06 = m[8] * m[13] - m[9] * m[12];
    float b07 = m[8] * m[14] - m[10] * m[12];
    float b08 = m[8] * m[15] - m[11] * m[12];
    float b09 = m[9] * m[14] - m[10] * m[13];
    float b10 = m[9] * m[15] - m[11] * m[13];
    float b11 = m[10] * m[15] - m[11] * m[14];

    float det = b00 * b11
              - b01 * b10
              + b02 * b09
              + b03 * b08
              - b04 * b07
              + b05 * b06;

    if (det == 0.0f)
        throw std::runtime_error("[ERROR]: mat4 is not invertible");

    float invDet = 1.0f / det;

    float out[16];

    out[0] = (
        m[5] * b11
        - m[6] * b10
        + m[7] * b09
    ) * invDet;

    out[1] = (
        -m[1] * b11
        + m[2] * b10
        - m[3] * b09
    ) * invDet;

    out[2] = (
        m[13] * b05
        - m[14] * b04
        + m[15] * b03
    ) * invDet;

    out[3] = (
        -m[9] * b05
        + m[10] * b04
        - m[11] * b03
    ) * invDet;

    out[4] = (
        -m[4] * b11
        + m[6] * b08
        - m[7] * b07
    ) * invDet;

    out[5] = (
        m[0] * b11
        - m[2] * b08
        + m[3] * b07
    ) * invDet;

    out[6] = (
        -m[12] * b05
        + m[14] * b02
        - m[15] * b01
    ) * invDet;

    out[7] = (
        m[8] * b05
        - m[10] * b02
        + m[11] * b01
    ) * invDet;

    out[8] = (
        m[4] * b10
        - m[5] * b08
        + m[7] * b06
    ) * invDet;

    out[9] = (
        -m[0] * b10
        + m[1] * b08
        - m[3] * b06
    ) * invDet;

    out[10] = (
        m[12] * b04
        - m[13] * b02
        + m[15] * b00
    ) * invDet;

    out[11] = (
        -m[8] * b04
        + m[9] * b02
        - m[11] * b00
    ) * invDet;

    out[12] = (
        -m[4] * b09
        + m[5] * b07
        - m[6] * b06
    ) * invDet;

    out[13] = (
        m[0] * b09
        - m[1] * b07
        + m[2] * b06
    ) * invDet;

    out[14] = (
        -m[12] * b03
        + m[13] * b01
        - m[14] * b00
    ) * invDet;

    out[15] = (
        m[8] * b03
        - m[9] * b01
        + m[10] * b00
    ) * invDet;

    return mat4(
        vec4(out[0], out[1], out[2], out[3]),
        vec4(out[4], out[5], out[6], out[7]),
        vec4(out[8], out[9], out[10], out[11]),
        vec4(out[12], out[13], out[14], out[15])
    );
}

const float* mat4::value_ptr() const {
    return &columns[0].x;
}

mat4 mat4::identity() {
    return mat4();
}

mat4 mat4::translate(const vec3& t) {
    mat4 m;

    m.columns[3] = vec4(
        t.x,
        t.y,
        t.z,
        1.0f
    );

    return m;
}

mat4 mat4::scale(const vec3& s) {
    mat4 m;

    m.columns[0].x = s.x;
    m.columns[1].y = s.y;
    m.columns[2].z = s.z;

    return m;
}

mat4 mat4::rotate(const vec3& axis, float deg) {
    float rad = deg * 3.14159265358979323846f / 180.0f;
    float c = std::cos(rad);
    float s = std::sin(rad);
    float t = 1.0f - c;

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    return mat4(
        vec4(
            t * x * x + c,
            t * x * y + s * z,
            t * x * z - s * y,
            0
        ),

        vec4(
            t * x * y - s * z,
            t * y * y + c,
            t * y * z + s * x,
            0
        ),

        vec4(
            t * x * z + s * y,
            t * y * z - s * x,
            t * z * z + c,
            0
        ),

        vec4(0, 0, 0, 1)
    );
}

mat4 mat4::lookAt(
    const vec3& eye,
    const vec3& target,
    const vec3& worldUp
) {
    vec3 forward = (target - eye).normalized();
    vec3 right = forward.cross(worldUp).normalized();
    vec3 up = right.cross(forward);

    mat4 m;

    m.columns[0] = vec4(
        right.x,
        up.x,
        -forward.x,
        0
    );

    m.columns[1] = vec4(
        right.y,
        up.y,
        -forward.y,
        0
    );

    m.columns[2] = vec4(
        right.z,
        up.z,
        -forward.z,
        0
    );

    m.columns[3] = vec4(
        -right.dot(eye),
        -up.dot(eye),
        forward.dot(eye),
        1
    );

    return m;
}

mat4 mat4::perspective(
    float fovYDeg,
    float aspect,
    float nearPlane,
    float farPlane
) {
    float fovRad = fovYDeg * 3.14159265358979323846f / 180.0f;
    float f = 1.0f / std::tan(fovRad / 2.0f);

    mat4 m;

    m.columns[0] = vec4(
        f / aspect,
        0,
        0,
        0
    );

    m.columns[1] = vec4(
        0,
        f,
        0,
        0
    );

    m.columns[2] = vec4(
        0,
        0,
        (farPlane + nearPlane)
            / (nearPlane - farPlane),
        -1
    );

    m.columns[3] = vec4(
        0,
        0,
        (2 * farPlane * nearPlane)
            / (nearPlane - farPlane),
        0
    );

    return m;
}

mat4 mat4::orthographic(
    float left,
    float right,
    float bottom,
    float top,
    float nearPlane,
    float farPlane
) {
    mat4 m;

    m.columns[0] = vec4(
        2.0f / (right - left),
        0,
        0,
        0
    );

    m.columns[1] = vec4(
        0,
        2.0f / (top - bottom),
        0,
        0
    );

    m.columns[2] = vec4(
        0,
        0,
        -2.0f / (farPlane - nearPlane),
        0
    );

    m.columns[3] = vec4(
        -(right + left) / (right - left),
        -(top + bottom) / (top - bottom),
        -(farPlane + nearPlane)
            / (farPlane - nearPlane),
        1
    );

    return m;
}