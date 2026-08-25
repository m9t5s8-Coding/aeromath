#pragma once

#include <cassert>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <type_traits>

namespace agm {

template <typename T>
struct alignas(sizeof(T) * 4) vec4 {
  T x = T{};
  T y = T{};
  T z = T{};
  T w = T{};

  // Default Constructor
  constexpr vec4() noexcept = default;

  // Copy Constructor
  constexpr vec4(const vec4<T>&) noexcept = default;

  // Move Constructor
  constexpr vec4(vec4<T>&&) noexcept = default;

  // Copy Assigment
  constexpr vec4& operator=(const vec4<T>&) noexcept = default;

  // Move Assignment
  constexpr vec4& operator=(vec4<T>&&) noexcept = default;

  constexpr vec4(T x_, T y_, T z_, T w_) noexcept
    : x(x_),
      y(y_),
      z(z_),
      w(w_) {}

  explicit constexpr vec4(T s_) noexcept
    : x(s_),
      y(s_),
      z(s_),
      w(s_) {}

  explicit constexpr vec4(const T* const array_ptr) noexcept
    : x(array_ptr[0]),
      y(array_ptr[1]),
      z(array_ptr[2]),
      w(array_ptr[3]) {}

  template <typename U>
  vec4(const vec4<U>&) = delete;

  [[nodiscard]] constexpr const T& operator[](size_t index) const noexcept {
    assert(index < 4 && "vec4 index is out of bounds! must be from 0 - 3");
    return (&x)[index];
  }

  [[nodiscard]] constexpr T& operator[](size_t index) noexcept {
    assert(index < 4 && "vec4 index is out of bounds! must be from 0 - 3");
    return (&x)[index];
  }

  constexpr vec4<T>& operator+=(const vec4<T>& other) noexcept {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
    return *this;
  }

  constexpr vec4<T>& operator+=(T scalar) noexcept {
    this->x += scalar;
    this->y += scalar;
    this->z += scalar;
    this->w += scalar;
    return *this;
  }

  constexpr vec4<T>& operator-=(const vec4<T>& other) noexcept {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;
    return *this;
  }

  constexpr vec4<T>& operator-=(T scalar) noexcept {
    this->x -= scalar;
    this->y -= scalar;
    this->z -= scalar;
    this->w -= scalar;
    return *this;
  }

  constexpr vec4<T>& operator*=(const vec4<T>& other) noexcept {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    this->w *= other.w;
    return *this;
  }

  constexpr vec4<T>& operator*=(T scalar) noexcept {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    this->w *= scalar;
    return *this;
  }

  constexpr vec4<T>& operator/=(const vec4<T>& other) noexcept {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    this->w /= other.w;
    return *this;
  }

  constexpr vec4<T>& operator/=(T scalar) noexcept {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    this->w /= scalar;
    return *this;
  }
};

// Addition
template <typename T>
[[nodiscard]] constexpr vec4<T> operator+(vec4<T> lhs, const vec4<T>& rhs) noexcept {
  lhs += rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec4<T> operator+(T scalar, vec4<T> rhs) noexcept {
  rhs += scalar;
  return rhs;
}

template <typename T>
[[nodiscard]] constexpr vec4<T> operator+(vec4<T> lhs, T scalar) noexcept {
  lhs += scalar;
  return lhs;
}

// Subtraction
template <typename T>
[[nodiscard]] constexpr vec4<T> operator-(vec4<T> lhs, const vec4<T>& rhs) noexcept {
  lhs -= rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec4<T> operator-(T scalar, const vec4<T>& rhs) noexcept {
  return vec4<T>(scalar - rhs.x, scalar - rhs.y, scalar - rhs.z, scalar - rhs.w);
}

template <typename T>
[[nodiscard]] constexpr vec4<T> operator-(vec4<T> lhs, T scalar) noexcept {
  lhs -= scalar;
  return lhs;
}

// Multiplication
template <typename T>
[[nodiscard]] constexpr vec4<T> operator*(vec4<T> lhs, const vec4<T>& rhs) noexcept {
  lhs *= rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec4<T> operator*(T scalar, vec4<T> rhs) noexcept {
  rhs *= scalar;
  return rhs;
}

template <typename T>
[[nodiscard]] constexpr vec4<T> operator*(vec4<T> lhs, T scalar) noexcept {
  lhs *= scalar;
  return lhs;
}

// Division
template <typename T>
[[nodiscard]] constexpr vec4<T> operator/(vec4<T> lhs, const vec4<T>& rhs) noexcept {
  lhs /= rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec4<T> operator/(T scalar, const vec4<T>& rhs) noexcept {
  return vec4<T>(scalar / rhs.x, scalar / rhs.y, scalar / rhs.z, scalar / rhs.w);
}

template <typename T>
[[nodiscard]] constexpr vec4<T> operator/(vec4<T> lhs, T scalar) noexcept {
  lhs /= scalar;
  return lhs;
}

// Comparision
template <typename T>
constexpr bool operator==(const vec4<T>& lhs, const vec4<T>& rhs) noexcept {
  if constexpr (std::is_integral_v<T>) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
  } else {
    auto abs_val = [](T val) constexpr noexcept {
      return val < T(0) ? -val : val;
    };

    constexpr T epsilon = T(0.00001);
    return abs_val(lhs.x - rhs.x) < epsilon && abs_val(lhs.y - rhs.y) < epsilon &&
           abs_val(lhs.z - rhs.z) < epsilon && abs_val(lhs.w - rhs.w) < epsilon;
  }
}

template <typename T>
constexpr bool operator!=(const vec4<T>& lhs, const vec4<T>& rhs) noexcept {
  return !(lhs == rhs);
}

// Dot
template <typename T>
[[nodiscard]] constexpr T dot(const vec4<T>& lhs, const vec4<T>& rhs) noexcept {
  return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);
}

// Length Squared
template <typename T>
[[nodiscard]] constexpr T length_squared(const vec4<T>& v) noexcept {
  return dot(v, v);
}

// Length
template <typename T>
[[nodiscard]] inline T length(const vec4<T>& v) noexcept {
  return std::sqrt(length_squared(v));
}

// Normalize
template <typename T>
[[nodiscard]] inline vec4<T> normalize(vec4<T> v) noexcept {
  T len = length(v);
  if (len > T(0)) {
    v /= len;
  }
  return v;
}

template <typename T>
std::ostream& operator<<(std::ostream& ss, const vec4<T>& other) {
  ss << "(" << other.x << ", " << other.y << ", " << other.z << ", " << other.w << ")";
  return ss;
}

using vec4i    = vec4<int>;
using vec4_i8  = vec4<int8_t>;
using vec4_i16 = vec4<int16_t>;
using vec4_i32 = vec4<int32_t>;
using vec4_i64 = vec4<int64_t>;

using vec4u    = vec4<unsigned int>;
using vec4_u8  = vec4<uint8_t>;
using vec4_u16 = vec4<uint16_t>;
using vec4_u32 = vec4<uint32_t>;
using vec4_u64 = vec4<uint64_t>;

using vec4f = vec4<float>;
using vec4d = vec4<double>;

}  // namespace agm
