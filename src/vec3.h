#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <iostream>
#include <array>
#include <cmath>
#include "simd.h"

#if defined(_MSC_VER)
#include <immintrin.h>
#else
#include <x86intrin.h>
#endif

class alignas(16) Vec3
{

public:
    union {
        struct { float _x, _y, _z; };
        __m128 v;
    };

public:
    static const Vec3 X;
    static const Vec3 Y;
    static const Vec3 Z;
    static const Vec3 ONE;
    static const Vec3 ZERO;

public:
    Vec3() : v{_mm_setzero_ps()} {}
    Vec3(float x, float y, float z, float w=0.0f) : v{_mm_set_ps(w, z, y, x)} {}
    Vec3(__m128 v) : v{v} {}

    float x() const { return _x; }
    float y() const { return _y; }
    float z() const { return _z; }

	const Vec3& operator+() const { return *this; }
	Vec3 operator-() const { return _mm_mul_ps(v, _mm_set1_ps(-1)); }
	float operator[](int i) const {
        switch (i)
        {
            case 0: return _x;
            case 1: return _y;
            case 2: return _z;
            default: return _z;
        }
    }
    float& operator[](int i) {
        switch (i)
        {
            case 0: return _x;
            case 1: return _y;
            case 2: return _z;
            default: return _z;
        }
     }

	Vec3& operator+=(const Vec3 &v1);
	Vec3& operator-=(const Vec3 &v1);
	Vec3& operator*=(const Vec3 &v1);
	Vec3& operator/=(const Vec3 &v1);

	Vec3& operator*=(float t);
	Vec3& operator/=(float t);

	float length() const
	{
		return std::sqrt(squared_length());
	}

	float squared_length() const
	{
	    auto res = _mm_mul_ps(v, v);
        if (CPUInfo().is_sse3())
        {
            res = _mm_hadd_ps(res, res);
            res = _mm_hadd_ps(res, res);
        } else {
            float _f[4]{0};
            _mm_store_ps(_f, res);
            res = _mm_set1_ps(_f[0] + _f[1] + _f[2] + _f[3]);
        }

        float v_f[4]{0};
        _mm_store1_ps(v_f, res);
		return v_f[0];
	}

	void normalize();

};


const Vec3 Vec3::X = { 1.0f, 0.0f, 0.0f };
const Vec3 Vec3::Y = { 0.0f, 1.0f, 0.0f };
const Vec3 Vec3::Z = { 0.0f, 0.0f, 1.0f };
const Vec3 Vec3::ONE = { 1.0f, 1.0f, 1.0f };
const Vec3 Vec3::ZERO = { 0.0f, 0.0f, 0.0f };


std::ostream& operator<<(std::ostream &os, const Vec3 &t)
{
	// os << "[" << t.x() << ", " << t.y() << ", " << t.z() << "]";
    os << "[" << t._x << ", " << t._y << ", " << t._z << "]";
	return os;
}


Vec3 operator+(const Vec3 &v1, const Vec3 &v2) { return _mm_add_ps(v1.v, v2.v); }
Vec3 operator-(const Vec3 &v1, const Vec3 &v2) { return _mm_sub_ps(v1.v, v2.v); }
Vec3 operator*(const Vec3 &v1, const Vec3 &v2) { return _mm_mul_ps(v1.v, v2.v); }
Vec3 operator/(const Vec3 &v1, const Vec3 &v2) { return _mm_div_ps(v1.v, v2.v); }

Vec3 operator*(const Vec3 &v, float t) { return _mm_mul_ps(v.v, _mm_set1_ps(t)); }
Vec3 operator*(float t, const Vec3 &v) { return v * t; }
Vec3 operator/(const Vec3 &v, float t) { return _mm_div_ps(v.v, _mm_set1_ps(t)); }

float dot(const Vec3 &v1, const Vec3 &v2)
{
    auto res = _mm_mul_ps(v1.v, v2.v);
    if (CPUInfo().is_sse3()) {
        res = _mm_hadd_ps(res, res);
        res = _mm_hadd_ps(res, res);
    }
    else {
        float _f[4]{0};
        _mm_store_ps(_f, res);
        res = _mm_set1_ps(_f[0] + _f[1] + _f[2] + _f[3]);
    }
    float v_f[4]{0};
    _mm_store1_ps(v_f, res);
	return v_f[0];
}

Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
    auto res = _mm_sub_ps(
            _mm_mul_ps(
                    _mm_shuffle_ps(v1.v, v1.v, _MM_SHUFFLE(3, 0, 2, 1)),
                    _mm_shuffle_ps(v2.v, v2.v, _MM_SHUFFLE(3, 1, 0, 2))
            ),
            _mm_mul_ps(
                    _mm_shuffle_ps(v1.v, v1.v, _MM_SHUFFLE(3, 1, 0, 2)),
                    _mm_shuffle_ps(v2.v, v2.v, _MM_SHUFFLE(3, 0, 2, 1))
            ));

    return Vec3(res);
}


Vec3& Vec3::operator+=(const Vec3 &v1)
{
    v = _mm_add_ps(v, v1.v);
	return *this;
}


Vec3& Vec3::operator-=(const Vec3 &v1)
{
    v = _mm_sub_ps(v, v1.v);
	return *this;
}


Vec3& Vec3::operator*=(const Vec3 &v1)
{
    v = _mm_mul_ps(v, v1.v);
	return *this;
}


Vec3& Vec3::operator/=(const Vec3 &v1)
{
    v = _mm_div_ps(v, v1.v);
	return *this;
}


Vec3& Vec3::operator*=(const float t)
{
    v = _mm_mul_ps(v, _mm_set1_ps(t));
	return *this;
}


Vec3& Vec3::operator/=(const float t)
{
	v = _mm_div_ps(v, _mm_set1_ps(t));
	return *this;
}


void Vec3::normalize()
{
    float k = length();
    if (k == 0)
    {
        v = _mm_setzero_ps();
        return;
    }
    v = _mm_div_ps(v, _mm_set1_ps(k));
}


Vec3 unit_vector(Vec3 v)
{
    if (v.length() == 0.0f) return Vec3();
    return v / v.length();
}


#endif //RAYTRACING_VEC3_H
