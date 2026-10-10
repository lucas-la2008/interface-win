#ifndef MATH_VECTORS__
#define MATH_VECTORS__

namespace Vec {
struct Vector2 {
  float x = 0;
  float y = 0;

  Vector2(float x, float y) : x(x), y(y) {}
  Vector2() : x(0), y(0) {}

  Vector2 operator+(const Vector2 &other) const;

  Vector2 &operator+=(const Vector2 &other);

  Vector2 operator-(const Vector2 &other) const;

  Vector2 &operator-=(const Vector2 &other);

  Vector2 operator*(const float other) const;

  Vector2 operator*(const Vector2 &other) const;

  Vector2 &operator*=(const Vector2 &other);

  Vector2 operator/(const Vector2 &other) const;

  Vector2 operator/(const float &other) const;

  Vector2 &operator/=(const Vector2 &other);

  Vector2 &operator=(const Vector2 &other);
};

struct Vector3 {
  float x = 0;
  float y = 0;
  float z = 0;

  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
  Vector3() : x(0), y(0), z(0) {}

  Vector3 operator+(const Vector3 &other) const;

  Vector3 &operator+=(const Vector3 &other);

  Vector3 operator-(const Vector3 &other) const;

  Vector3 &operator-=(const Vector3 &other);

  Vector3 operator*(const float other) const;

  Vector3 operator*(const Vector3 &other) const;

  Vector3 &operator*=(const Vector3 &other);

  Vector3 operator/(const Vector3 &other) const;

  Vector3 operator/(const float &other) const;

  Vector3 &operator/=(const Vector3 &other);

  Vector3 &operator=(const Vector3 &other);
};

struct Vector4 {
  float x = 0;
  float y = 0;
  float z = 0; 
  float a = 0;

  Vector4(float x, float y, float z, float a) : x(x), y(y), z(z), a(a) {}
  Vector4() : x(0), y(0), z(0), a(0) {}

  Vector4 operator+(const Vector4 &other) const;

  Vector4 &operator+=(const Vector4 &other);

  Vector4 operator-(const Vector4 &other) const;

  Vector4 &operator-=(const Vector4 &other);

  Vector4 operator*(const float other) const;

  Vector4 operator*(const Vector4 &other) const;

  Vector4 &operator*=(const Vector4 &other);

  Vector4 operator/(const Vector4 &other) const;

  Vector4 operator/(const float &other) const;

  Vector4 &operator/=(const Vector4 &other);

  Vector4 &operator=(const Vector4 &other);
};
} // namespace Vec

#endif