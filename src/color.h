#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H


#include "vec3.h"


#include <array>
#include <sstream>
#include <fstream>
#include <iostream>

#if defined(_MSC_VER)
#include <immintrin.h>
#else
#include <x86intrin.h>
#endif


class alignas(16) Color
{

public:
    /**
     * The internal color representation.
     */
    union {
        struct { float _r, _g, _b; };
        __m128 v;
    };

public:
    /**
     * Default constructor.
     *
     * Will create a black color.
     */
    Color() : v{_mm_setzero_ps()} {}

    /**
     * Color int constructor.
     *
     * Will create a color from the int values as inputs.
     * The input values must be in the range [0, 255).
     *
     * @param r Red component.
     * @param g Green component.
     * @param b Blue component.
     */
    Color(int r, int g, int b, int alpha=255)
        : v{_mm_set_ps(alpha/255.0f, b/255.0f, g/255.0f, r/255.0f)} {}

    /**
     * Color float constructor.
     *
     * Will create a color using floating point values as inputs.
     * The values must be in the range [0, 1).
     *
     * @param r Red component.
     * @param g Green component.
     * @param b Blue component.
     */
    Color(float r, float g, float b): v{_mm_set_ps(0, b, g, r)} {}

    /**
     * @brief Construct a new Color object
     * 
     * @param v Vec3 object
     */
    Color(const Vec3 &_v): v{_v.v} {}

    /**
     * @brief Construct a new Color object using single value to fill RGB color.
     * 
     * @param c float value used to define all RGB component of this color.
     */
    explicit Color(float gray, float alpha=0.0f) : v{_mm_set1_ps(gray)} {}

    /**
     * @brief Construct a color from a SIMD object.
     *
     * @param _v SIMD object.
     */
    explicit Color(__m128 _v) : v{_v} {}

    /**
     * @brief Destroy the Color object
     */
    ~Color() = default;


    float r() const { return _r; }
    float g() const { return _g; }
    float b() const { return _b; }

    Color& operator+=(const Color &a);
    Color& operator/=(float a);

    Color& gamma();
};


Color& Color::operator+=(const Color &a)
{
    v = _mm_add_ps(v, a.v);

    return *this;
}


Color& Color::operator/=(float a)
{
    v = _mm_div_ps(v, _mm_set1_ps(a));

    return *this;
}


Color operator/(Color a, float b)
{
    Color res(_mm_div_ps(a.v, _mm_set1_ps(b)));

    return res;
}


Color& Color::gamma()
{
    //c[0] = std::sqrt(c[0]);
    //c[1] = std::sqrt(c[1]);
    //c[2] = std::sqrt(c[2]);
    _r = std::pow(_r, 0.4545454545454545f);
    _g = std::pow(_g, 0.4545454545454545f);
    _b = std::pow(_b, 0.4545454545454545f);

    return *this;
}


/**
 * Output stream operator overload.
 *
 * Will format the color as to be represented in a string
 * for the default output stream.
 *
 * @param os The output stream.
 * @param color The color to represent.
 *
 * @return The output stream with the color formatted.
 */
inline std::ostream& operator<<(std::ostream &os, const Color &color)
{
    os << static_cast<int>(color.r() * 255.99) << " "
       << static_cast<int>(color.g() * 255.99) << " "
       << static_cast<int>(color.b() * 255.99);
    return os;
}

/**
 * Output file stream operator overload.
 *
 * Will format the color as to be written in an ASCII file.
 *
 * @param ofs The file stream.
 * @param color The color to represent.
 *
 * @return The output file stream into witch format the color.
 */
inline std::ofstream& operator<<(std::ofstream &ofs, const Color &color)
{
    ofs << static_cast<int>(color.r() * 255.99) << " "
        << static_cast<int>(color.g() * 255.99) << " "
        << static_cast<int>(color.b() * 255.99);
    return ofs;
}

inline Color operator*(const Color &c1, const Color &c2)
{
	return Color(_mm_mul_ps(c1.v, c2.v));
}


inline Color operator*(float t, const Color &c)
{
    return Color(_mm_mul_ps(c.v, _mm_set1_ps(t)));
}


inline Color operator*(const Color &c, float t)
{
    return t * c;
}


inline Color operator+(const Color &a, const Color &b)
{
    return Color(_mm_add_ps(a.v, b.v));
}


#endif //RAYTRACING_COLOR_H
