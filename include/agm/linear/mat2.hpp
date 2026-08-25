#pragma once

#include "vec2.hpp"
#include "vec4.hpp"

namespace agm {

template <typename T>
struct mat2 {
  vec2<T> columns[2] = {vec2<T>{}, vec2<T>{}};

  constexpr mat2() noexcept
    : columns{
          vec2<T>{T{1}, T{0}},
          vec2<T>{T{0}, T{1}}
  } {}

  constexpr mat2(T a00, T a01, T a10, T a11) noexcept
    : columns{
          vec2<T>{a00, a10},
          vec2<T>{a01, a11}
  } {}

  constexpr mat2(const vec2<T>& c1, const vec2<T>& c2) noexcept
    : columns{c1, c2} {}

  constexpr mat2(const vec4<T>& v) noexcept
    : columns{
          vec2<T>{v.x, v.y},
          vec2<T>{v.z, v.w}
  } {}

  constexpr mat2(const mat2<T>&) noexcept            = default;
  constexpr mat2(mat2<T>&&) noexcept                 = default;
  constexpr mat2& operator=(const mat2<T>&) noexcept = default;
  constexpr mat2& operator=(mat2<T>&&) noexcept      = default;

  constexpr mat2& operator=(const vec4<T>& v) noexcept {
    this->columns[0].x = v.x;
    this->columns[0].y = v.y;
    this->columns[1].x = v.z;
    this->columns[1].y = v.w;
    return *this;
  }

  [[nodiscard]] constexpr const vec2<T>& operator[](size_t col_index) const noexcept {
    assert(col_index < 2 && "mat2 column index out of bounds! must be 0 or 1!");
    return columns[col_index];
  }

  [[nodiscard]] constexpr vec2<T>& operator[](size_t col_index) noexcept {
    assert(col_index < 2 && "mat2 column index out of bounds! must be 0 or 1!");
    return columns[col_index];
  }

  [[nodiscard]] static constexpr mat2<T> zero() noexcept {
    return mat2<T>(vec2<T>{T{0}, T{0}}, vec2<T>{T{0}, T{0}});
  }

  [[nodiscard]] static constexpr mat2<T> identity() noexcept { return mat2<T>(); }
};

template <typename T>
[[nodiscard]] constexpr mat2<T> operator*(const mat2<T>& m1, const vec2<T>& v1) {
  return mat2<T>();
}

}  // namespace agm
