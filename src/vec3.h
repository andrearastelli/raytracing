#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <iostream>
#include <array>
#include <cmath>

#include <immintrin.h>


class Vec3
{

public:
    //std::array<float, 3> v;
    __m128 v;

public:
    static const Vec3 X;
    static const Vec3 Y;
    static const Vec3 Z;
    static const Vec3 ONE;
    static const Vec3 ZERO;

public:
    Vec3() { v = _mm_setzero_ps(); }
    Vec3(float x, float y, float z, float w=0.0f) { v = _mm_set_ps(x, y, z, w); }
    explicit Vec3(__m128 v) : v{v} {}


    // float x() const { return v[0]; }
    // float y() const { return v[1]; }
    // float z() const { return v[2]; }
	
	// const Vec3& operator+() const { return *this; }
	// Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }
	// float operator[](int i) const { return v[i]; }
	// float& operator[](int i) { return v[i]; }
	
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
		return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
	}
	
	void normalize();

};


// constexpr const Vec3 Vec3::X = { 1.0f, 0.0f, 0.0f };
// constexpr const Vec3 Vec3::Y = { 0.0f, 1.0f, 0.0f };
// constexpr const Vec3 Vec3::Z = { 0.0f, 0.0f, 1.0f };
// constexpr const Vec3 Vec3::ONE = { 1.0f, 1.0f, 1.0f };
// constexpr const Vec3 Vec3::ZERO = { 0.0f, 0.0f, 0.0f };


// std::ostream& operator<<(std::ostream &os, const Vec3 &t)
// {
// 	os << t.x() << t.y() << t.z();
// 	return os;
// }


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
    auto mul = v1 * v1;
    auto res = _mm_cvtss_f32(mul.v);
	return res;
}


Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
    auto res = _mm_sub_ps(
            _mm_mul_ps(                                                    // z, y, x, w
                    _mm_shuffle_ps(v1.v, v1.v, _MM_SHUFFLE(3, 0, 2, 1)),   // w,
                    _mm_shuffle_ps(v2.v, v2.v, _MM_SHUFFLE(3, 1, 0, 2))),
            _mm_mul_ps(
                    _mm_shuffle_ps(v1.v, v1.v, _MM_SHUFFLE(3, 1, 0, 2)),
                    _mm_shuffle_ps(v2.v, v2.v, _MM_SHUFFLE(3, 0, 2, 1)))
    );

    // return Vec3(
	// 	(v1.y()*v2.z() - v1.z()*v2.y()),
	// 	(-(v1.x()*v2.z() - v1.z()*v2.x())),
	// 	(v1.x()*v2.y() - v1.y()*v2.x())
	// );

    return Vec3(res);
}


Vec3& Vec3::operator+=(const Vec3 &v1)
{
	v[0] += v1.v[0];
	v[1] += v1.v[1];
	v[2] += v1.v[2];
	return *this;
}


Vec3& Vec3::operator-=(const Vec3 &v1)
{
	v[0] -= v1.v[0];
	v[1] -= v1.v[1];
	v[2] -= v1.v[2];
	return *this;
}


Vec3& Vec3::operator*=(const Vec3 &v1)
{
	v[0] *= v1.v[0];
	v[1] *= v1.v[1];
	v[2] *= v1.v[2];
	return *this;
}


Vec3& Vec3::operator/=(const Vec3 &v1)
{
	v[0] /= v1.v[0];
	v[1] /= v1.v[1];
	v[2] /= v1.v[2];
	return *this;
}


Vec3& Vec3::operator*=(const float t)
{
	v[0] *= t;
	v[1] *= t;
	v[2] *= t;
	return *this;
}


Vec3& Vec3::operator/=(const float t)
{
	v[0] /= t;
	v[1] /= t;
	v[2] /= t;
	return *this;
}


void Vec3::normalize()
{
    float k = length();
    v[0] /= k;
    v[1] /= k;
    v[2] /= k;
}


Vec3 unit_vector(Vec3 v)
{
    return v / v.length();
}


#endif //RAYTRACING_VEC3_H
