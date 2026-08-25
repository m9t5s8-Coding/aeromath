#pragma once

#include <cassert>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <type_traits>

namespace agm {

template <typename T>
struct vec2 {
  T x = T{};
  T y = T{};

  // Default Constructor
  constexpr vec2() noexcept = default;

  // Copy Constructor
  constexpr vec2(const vec2<T>&) noexcept = default;

  // Move Constructor
  constexpr vec2(vec2<T>&&) noexcept = default;

  // Copy Assigment
  constexpr vec2& operator=(const vec2<T>&) noexcept = default;

  // Move Assignment
  constexpr vec2& operator=(vec2<T>&&) noexcept = default;

  constexpr vec2(T x_, T y_) noexcept
    : x(x_),
      y(y_) {}

  explicit constexpr vec2(T s_) noexcept
    : x(s_),
      y(s_) {}

  explicit constexpr vec2(const T* const array_ptr) noexcept
    : x(array_ptr[0]),
      y(array_ptr[1]) {}

  template <typename U>
  vec2(const vec2<U>&) = delete;

  [[nodiscard]] constexpr const T& operator[](size_t index) const noexcept {
    assert(index < 2 && "vec2 index is out of bounds! must be 0 or 1");
    return (&x)[index];
  }

  [[nodiscard]] constexpr T& operator[](size_t index) noexcept {
    assert(index < 2 && "vec2 index is out of bounds! must be 0 or 1");
    return (&x)[index];
  }

  constexpr vec2<T>& operator+=(const vec2<T>& other) noexcept {
    this->x += other.x;
    this->y += other.y;
    return *this;
  }

  constexpr vec2<T>& operator+=(T scalar) noexcept {
    this->x += scalar;
    this->y += scalar;
    return *this;
  }

  constexpr vec2<T>& operator-=(const vec2<T>& other) noexcept {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
  }

  constexpr vec2<T>& operator-=(T scalar) noexcept {
    this->x -= scalar;
    this->y -= scalar;
    return *this;
  }

  constexpr vec2<T>& operator*=(const vec2<T>& other) noexcept {
    this->x *= other.x;
    this->y *= other.y;
    return *this;
  }

  constexpr vec2<T>& operator*=(T scalar) noexcept {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
  }

  constexpr vec2<T>& operator/=(const vec2<T>& other) noexcept {
    this->x /= other.x;
    this->y /= other.y;
    return *this;
  }

  constexpr vec2<T>& operator/=(T scalar) noexcept {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
  }
};

// Addition
template <typename T>
[[nodiscard]] constexpr vec2<T> operator+(vec2<T> lhs, const vec2<T>& rhs) noexcept {
  lhs += rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec2<T> operator+(T scalar, vec2<T> rhs) noexcept {
  rhs += scalar;
  return rhs;
}

template <typename T>
[[nodiscard]] constexpr vec2<T> operator+(vec2<T> lhs, T scalar) noexcept {
  lhs += scalar;
  return lhs;
}

// Subtraction
template <typename T>
[[nodiscard]] constexpr vec2<T> operator-(vec2<T> lhs, const vec2<T>& rhs) noexcept {
  lhs -= rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec2<T> operator-(T scalar, const vec2<T>& rhs) noexcept {
  return vec2<T>(scalar - rhs.x, scalar - rhs.y);
}

template <typename T>
[[nodiscard]] constexpr vec2<T> operator-(vec2<T> lhs, T scalar) noexcept {
  lhs -= scalar;
  return lhs;
}

// Multiplication
template <typename T>
[[nodiscard]] constexpr vec2<T> operator*(vec2<T> lhs, const vec2<T>& rhs) noexcept {
  lhs *= rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec2<T> operator*(T scalar, vec2<T> rhs) noexcept {
  rhs *= scalar;
  return rhs;
}

template <typename T>
[[nodiscard]] constexpr vec2<T> operator*(vec2<T> lhs, T scalar) noexcept {
  lhs *= scalar;
  return lhs;
}

// Division
template <typename T>
[[nodiscard]] constexpr vec2<T> operator/(vec2<T> lhs, const vec2<T>& rhs) noexcept {
  lhs /= rhs;
  return lhs;
}

template <typename T>
[[nodiscard]] constexpr vec2<T> operator/(T scalar, const vec2<T>& rhs) noexcept {
  return vec2<T>(scalar / rhs.x, scalar / rhs.y);
}

template <typename T>
[[nodiscard]] constexpr vec2<T> operator/(vec2<T> lhs, T scalar) noexcept {
  lhs /= scalar;
  return lhs;
}

// Comparision
template <typename T>
constexpr bool operator==(const vec2<T>& lhs, const vec2<T>& rhs) noexcept {
  if constexpr (std::is_integral_v<T>) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  } else {
    auto abs_val = [](T val) constexpr noexcept {
      return val < T(0) ? -val : val;
    };

    constexpr T epsilon = T(0.00001);
    return abs_val(lhs.x - rhs.x) < epsilon && abs_val(lhs.y - rhs.y) < epsilon;
  }
}

template <typename T>
constexpr bool operator!=(const vec2<T>& lhs, const vec2<T>& rhs) noexcept {
  return !(lhs == rhs);
}

// Dot
template <typename T>
[[nodiscard]] constexpr T dot(const vec2<T>& lhs, const vec2<T>& rhs) noexcept {
  return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

// Length Squared
template <typename T>
[[nodiscard]] constexpr T length_squared(const vec2<T>& v) noexcept {
  return dot(v, v);
}

// Length
template <typename T>
[[nodiscard]] inline T length(const vec2<T>& v) noexcept {
  return std::sqrt(length_squared(v));
}

// Normalize
template <typename T>
[[nodiscard]] inline vec2<T> normalize(vec2<T> v) noexcept {
  T len = length(v);
  if (len > T(0)) {
    v /= len;
  }
  return v;
}

template <typename T>
std::ostream& operator<<(std::ostream& ss, const vec2<T>& other) {
  ss << "(" << other.x << ", " << other.y << ")";
  return ss;
}

using vec2i    = vec2<int64_t>;
using vec2_i8  = vec2<int8_t>;
using vec2_i16 = vec2<int16_t>;
using vec2_i32 = vec2<int32_t>;
using vec2_i64 = vec2<int64_t>;

using vec2u    = vec2<unsigned int>;
using vec2_u8  = vec2<uint8_t>;
using vec2_u16 = vec2<uint16_t>;
using vec2_u32 = vec2<uint32_t>;
using vec2_u64 = vec2<uint64_t>;

using vec2f = vec2<float>;
using vec2d = vec2<double>;

}  // namespace agm
