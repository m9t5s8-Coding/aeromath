#pragma once

#include <cassert>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <type_traits>

namespace agm {

template <typename T>
struct vec3 {
  T x = T{};
  T y = T{};
  T z = T{};

  // Default Constructor
  constexpr vec3() noexcept = default;

  // Copy Constructor
  constexpr vec3(const vec3<T>&) noexcept = default;

  // Move Constructor
  constexpr vec3(vec3<T>&&) noexcept = default;

  // Copy Assigment
  constexpr vec3& operator=(const vec3<T>&) noexcept = default;

  // Move Assignment
  constexpr vec3& operator=(vec3<T>&&) noexcept = default;

  constexpr vec3(T x_, T y_, T z_) noexcept
    : x(x_),
      y(y_),
      z(z_) {}

  explicit constexpr vec3(T s_) noexcept
    : x(s_),
      y(s_),
      z(s_) {}

  explicit constexpr vec3(const T* const array_ptr) noexcept
    : x(array_ptr[0]),
      y(array_ptr[1]),
      z(array_ptr[2]) {}

  template <typename U>
  vec3(const vec3<U>&) = delete;

  [[nodiscard]] constexpr const T& operator[](size_t index) const noexcept {
    assert(index < 3 && "vec3 index is out of bounds! must be from 0 - 2");
    return (&x)[index];
  }

  [[nodiscard]] constexpr T& operator[](size_t index) noexcept {
    assert(index < 3 && "vec3 index is out of bounds! must be from 0 - 2");
    return (&x)[index];
  }

  constexpr vec3<T>& operator+=(const vec3<T>& other) noexcept {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
  }

  constexpr vec3<T>& operator+=(T scalar) noexcept {
    this->x += scalar;
    this->y += scalar;
    this->z += scalar;
    return *this;
  }

  constexpr vec3<T>& operator-=(const vec3<T>& other) noexcept {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
  }

  constexpr vec3<T>& operator-=(T scalar) noexcept {
    this->x -= scalar;
    this->y -= scalar;
    this->z -= scalar;
    return *this;
  }

  constexpr vec3<T>& operator*=(const vec3<T>& other) noexcept {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
  }

  constexpr vec3<T>& operator*=(T scalar) noexcept {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
  }

  constexpr vec3<T>& operator/=(const vec3<T>& other) noexcept {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
  }

  constexpr vec3<T>& operator/=(T scalar) noexcept {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
  }
};

// Addition
template <typename T>
[[nodiscard]] constexpr vec3<T> operator+(vec3<T> lhs, const vec3<T>& rhs) noexcept {
  lhs += rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec3<T> operator+(T scalar, vec3<T> rhs) noexcept {
  rhs += scalar;
  return rhs;
}

template <typename T>
[[nodiscard]] constexpr vec3<T> operator+(vec3<T> lhs, T scalar) noexcept {
  lhs += scalar;
  return lhs;
}

// Subtraction
template <typename T>
[[nodiscard]] constexpr vec3<T> operator-(vec3<T> lhs, const vec3<T>& rhs) noexcept {
  lhs -= rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec3<T> operator-(T scalar, const vec3<T>& rhs) noexcept {
  return vec3<T>(scalar - rhs.x, scalar - rhs.y, scalar - rhs.z);
}

template <typename T>
[[nodiscard]] constexpr vec3<T> operator-(vec3<T> lhs, T scalar) noexcept {
  lhs -= scalar;
  return lhs;
}

// Multiplication
template <typename T>
[[nodiscard]] constexpr vec3<T> operator*(vec3<T> lhs, const vec3<T>& rhs) noexcept {
  lhs *= rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec3<T> operator*(T scalar, vec3<T> rhs) noexcept {
  rhs *= scalar;
  return rhs;
}

template <typename T>
[[nodiscard]] constexpr vec3<T> operator*(vec3<T> lhs, T scalar) noexcept {
  lhs *= scalar;
  return lhs;
}

// Division
template <typename T>
[[nodiscard]] constexpr vec3<T> operator/(vec3<T> lhs, const vec3<T>& rhs) noexcept {
  lhs /= rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec3<T> operator/(T scalar, const vec3<T>& rhs) noexcept {
  return vec3<T>(scalar / rhs.x, scalar / rhs.y, scalar / rhs.z);
}

template <typename T>
[[nodiscard]] constexpr vec3<T> operator/(vec3<T> lhs, T scalar) noexcept {
  lhs /= scalar;
  return lhs;
}

// Comparision
template <typename T>
constexpr bool operator==(const vec3<T>& lhs, const vec3<T>& rhs) noexcept {
  if constexpr (std::is_integral_v<T>) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
  } else {
    auto abs_val = [](T val) constexpr noexcept {
      return val < T(0) ? -val : val;
    };

    constexpr T epsilon = T(0.00001);
    return abs_val(lhs.x - rhs.x) < epsilon && abs_val(lhs.y - rhs.y) < epsilon &&
           abs_val(lhs.z - rhs.z) < epsilon;
  }
}

template <typename T>
constexpr bool operator!=(const vec3<T>& lhs, const vec3<T>& rhs) noexcept {
  return !(lhs == rhs);
}

// Dot
template <typename T>
[[nodiscard]] constexpr T dot(const vec3<T>& lhs, const vec3<T>& rhs) noexcept {
  return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

// Length Squared
template <typename T>
[[nodiscard]] constexpr T length_squared(const vec3<T>& v) noexcept {
  return dot(v, v);
}

// Length
template <typename T>
[[nodiscard]] inline T length(const vec3<T>& v) noexcept {
  return std::sqrt(length_squared(v));
}

// Normalize
template <typename T>
[[nodiscard]] inline vec3<T> normalize(vec3<T> v) noexcept {
  T len = length(v);
  if (len > T(0)) {
    v /= len;
  }
  return v;
}

template <typename T>
std::ostream& operator<<(std::ostream& ss, const vec3<T>& other) {
  ss << "(" << other.x << ", " << other.y << ", " << other.z << ")";
  return ss;
}

using vec3i    = vec3<int64_t>;
using vec3_i8  = vec3<int8_t>;
using vec3_i16 = vec3<int16_t>;
using vec3_i32 = vec3<int32_t>;
using vec3_i64 = vec3<int64_t>;

using vec3u    = vec3<unsigned int>;
using vec3_u8  = vec3<uint8_t>;
using vec3_u16 = vec3<uint16_t>;
using vec3_u32 = vec3<uint32_t>;
using vec3_u64 = vec3<uint64_t>;

using vec3f = vec3<float>;
using vec3d = vec3<double>;

}  // namespace agm
