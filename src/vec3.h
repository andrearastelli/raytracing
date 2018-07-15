#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <iostream>
#include <array>
#include <cmath>

#if defined(_MSC_VER)
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

class Vec3
{

public:
    union {
        //float v_f[4] __attribute__((aligned(0x1000)));
        struct { float x, y, z; } __attribute__((aligned(0x1000)));
        __m128 v;
    };

public:
    static const Vec3 X;
    static const Vec3 Y;
    static const Vec3 Z;
    static const Vec3 ONE;
    static const Vec3 ZERO;

public:
    Vec3() { _mm_setzero_ps(); }
    Vec3(float x, float y, float z, float w=0.0f) { _mm_set_ps(w, z, y, x); }
    explicit Vec3(__m128 v) : v{v} {}

    //float x() const { float v_f[4]{0}; _mm_storeu_ps(v_f, v); return v_f[0]; }
    //float y() const { float v_f[4]{0}; _mm_storeu_ps(v_f, v); return v_f[1]; }
    //float z() const { float v_f[4]{0}; _mm_storeu_ps(v_f, v); return v_f[2]; }
	
	const Vec3& operator+() const { return *this; }
	Vec3 operator-() const { return Vec3(_mm_mul_ps(v, _mm_set1_ps(-1))); }
	float operator[](int i) const {
        switch (i)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
        auto error_text = "Index [" + std::to_string(i) + "] value not allowed.";
        throw std::runtime_error(error_text);
        // return v_f[3-i];
    }
    float& operator[](int i) {
        switch (i)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }
        auto error_text = "Index [" + std::to_string(i) + "] value not allowed.";
        throw std::runtime_error(error_text);
        // return v_f[3-i];
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
	    float v_f[4]{0};
	    auto res = _mm_mul_ps(v, v);
	    _mm_store_ps(v_f, res);
		return v_f[0] + v_f[1] + v_f[2];
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
    os << "[" << t.x << ", " << t.y << ", " << t.z << "]";
	return os;
}


Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
    auto res = _mm_add_ps(v1.v, v2.v);
	return Vec3(res);
}


Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
{
    auto res = _mm_sub_ps(v1.v, v2.v);
	return Vec3(res);
}


Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
    auto res = _mm_mul_ps(v1.v, v2.v);
	return Vec3(res);
}


Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
{
    auto res = _mm_div_ps(v1.v, v2.v);
	return Vec3(res);
}


Vec3 operator*(const Vec3 &v, float t)
{
    auto t_vec = _mm_set1_ps(t);
    auto res = _mm_mul_ps(v.v, t_vec);
	return Vec3(res);
}


Vec3 operator*(float t, const Vec3 &v)
{
    return v * t;
}


Vec3 operator/(const Vec3 &v, float t)
{
    auto t_vec = _mm_set1_ps(t);
    auto res = _mm_div_ps(v.v, t_vec);
	return Vec3(res);
}


float dot(const Vec3 &v1, const Vec3 &v2)
{
    auto mul = v1 * v2;
    // auto res = mul.v_f[0] + mul.v_f[1] + mul.v_f[2];
    // auto res = _mm_cvtss_f32(_mm_dp_ps(v1.v, v2.v, 0x71));
    auto res = _mm_hadd_ps(mul.v, mul.v);
    res = _mm_hadd_ps(res, res);
	return res[0];
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
    v = _mm_div_ps(v, _mm_set1_ps(k));
}


Vec3 unit_vector(Vec3 v)
{
    return v / v.length();
}


#endif //RAYTRACING_VEC3_H
