#include "vectors.hpp"
using namespace Vec;

// ===========================
// Vector2 implementations
// ===========================

Vector2 Vector2::operator+(const Vector2& other) const{
    return Vector2(other.x + this->x, other.y + this->y);
}

Vector2& Vector2::operator+=(const Vector2& other){
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const{
    return Vector2(this->x - other.x, this->y - other.y);
}

Vector2& Vector2::operator-=(const Vector2& other){
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

Vector2 Vector2::operator*(const float other) const{
    return Vector2(this->x * other,this->y * other);
}

Vector2 Vector2::operator*(const Vector2& other) const{
    return Vector2(other.x * this->x, other.y * this->y);
}

Vector2& Vector2::operator*=(const Vector2& other){
    this->x *= other.x;
    this->y *= other.y;
    return *this;
}

Vector2 Vector2::operator/(const Vector2& other) const{
    return Vector2(this->x/other.x, this->y/other.y);
}

Vector2 Vector2::operator/(const float& other) const{
    return Vector2(this->x/other,this->y/other);
}

Vector2& Vector2::operator/=(const Vector2& other){
    this->x /= other.x;
    this->y /= other.y;
    return *this;
}

Vector2& Vector2::operator=(const Vector2& other){
    x = other.x;
    y = other.y;

    return *this;
}

// ============================
// Vector3 implementations
// ============================

Vector3 Vector3::operator+(const Vector3& other) const{
    return Vector3(other.x + this->x, other.y + this->y, this->z+other.z);
}

Vector3& Vector3::operator+=(const Vector3& other){
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const{
    return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3& Vector3::operator-=(const Vector3& other){
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

Vector3 Vector3::operator*(const float other) const{
    return Vector3(this->x * other,this->y * other, this->z * other);
}

Vector3 Vector3::operator*(const Vector3& other) const{
    return Vector3(other.x * this->x, other.y * this->y, other.z * this->z);
}

Vector3& Vector3::operator*=(const Vector3& other){
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
}

Vector3 Vector3::operator/(const Vector3& other) const{
    return Vector3(this->x/other.x, this->y/other.y, this->z / other.z);
}

Vector3 Vector3::operator/(const float& other) const{
    return Vector3(this->x/other, this->y/other, this->z/other);
}

Vector3& Vector3::operator/=(const Vector3& other){
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
}

Vector3& Vector3::operator=(const Vector3& other){
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

// =============================
// Vector 4 Implementations
// =============================

Vector4 Vector4::operator+(const Vector4& other) const{
    return Vector4(
        this->x+other.x,
        this->y+other.y,
        this->z+other.z,
        this->a+other.a);
}

Vector4& Vector4::operator+=(const Vector4& other){
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->a += other.a;
    return *this;
}

Vector4 Vector4::operator-(const Vector4& other) const{
    return Vector4(
        this->x - other.x,
        this->y - other.y,
        this->z - other.z, 
        this->a - other.a
    );
}

Vector4& Vector4::operator-=(const Vector4& other){
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->a -= other.a;
    return *this;
}

Vector4 Vector4::operator*(const float other) const{
    return Vector4(
        this->x * other,
        this->y * other, 
        this->z * other,
        this->a * other);
}

Vector4 Vector4::operator*(const Vector4& other) const{
    return Vector4(
        other.x * this->x, 
        other.y * this->y, 
        other.z * this->z, 
        other.a * this->a);
}

Vector4& Vector4::operator*=(const Vector4& other){
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    this->a *= other.a;
    return *this;
}

Vector4 Vector4::operator/(const Vector4& other) const{
    return Vector4(
        this->x / other.x,
        this->y / other.y,
        this->z / other.z,
        this->a / other.a
    );
}

Vector4 Vector4::operator/(const float& other) const{
    return Vector4(
        this->x / other,
        this->y / other,
        this->z / other,
        this->a / other
    );
}

Vector4& Vector4::operator/=(const Vector4& other){
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    this->a /= other.a;
    return *this;
}

Vector4& Vector4::operator=(const Vector4& other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->a = other.a;
    return *this;
}