AeroMath 🚀

A simple and lightweight C++ mathematics library focused on vector and matrix operations.

AeroMath currently provides basic:

2D, 3D, and 4D vectors

2×2, 3×3, and 4×4 matrices

The project is built to practice and explore mathematical programming, C++ library design, and performance-oriented implementations.

Features
Vectors

Vec2 — 2-dimensional vector

Vec3 — 3-dimensional vector

Vec4 — 4-dimensional vector

Matrices

Mat2 — 2×2 matrix

Mat3 — 3×3 matrix

Mat4 — 4×4 matrix

Project Structure
aeromath/
├── include/
│   └── agm/
├── src/
└── README.md

Example
# include <agm/Vec3.h>

int main() {
    agm::Vec3 a(1.0f, 2.0f, 3.0f);
    agm::Vec3 b(4.0f, 5.0f, 6.0f);

    auto result = a + b;

    return 0;
}

What I'm Learning

Building AeroMath is helping me learn and practice:

C++ library design

Vector and matrix mathematics

Operator overloading

Header/source organization

Numerical programming

Memory and data representation

Writing reusable C++ components

Performance-oriented programming

Roadmap

More mathematical functionality will be added over time.

Planned areas include:

Vector operations

Matrix operations

Transformations

More mathematical utilities

Testing

Benchmarks

Repository

GitHub

AeroMath — Mathematics implemented in C++.
