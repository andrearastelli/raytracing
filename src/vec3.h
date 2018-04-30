#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <iostream>
#include <array>
#include <cmath>


class Vec3
{

private:
    std::array<float, 3> v;

public:
    static const Vec3 X;
    static const Vec3 Y;
    static const Vec3 Z;
    static const Vec3 ONE;
    static const Vec3 ZERO;

public:
    Vec3(): v{0.0f, 0.0f, 0.0f} {}
    constexpr Vec3(float x, float y, float z): v{x, y, z} {}

    float x() const { return v[0]; }
    float y() const { return v[1]; }
    float z() const { return v[2]; }
	
	inline const Vec3& operator+() const { return *this; }
	inline Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }
	inline float operator[](int i) const { return v[i]; }
	inline float& operator[](int i) { return v[i]; }
	
	inline Vec3& operator+=(const Vec3 &v1);
	inline Vec3& operator-=(const Vec3 &v1);
	inline Vec3& operator*=(const Vec3 &v1);
	inline Vec3& operator/=(const Vec3 &v1);
	
	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);
	
	inline float length() const 
	{
		return std::sqrt(squared_length());
	}
	
	inline float squared_length() const 
	{
		return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
	}
	
	inline void normalize();

};


constexpr const Vec3 Vec3::X = { 1.0f, 0.0f, 0.0f };
constexpr const Vec3 Vec3::Y = { 0.0f, 1.0f, 0.0f };
constexpr const Vec3 Vec3::Z = { 0.0f, 0.0f, 1.0f };
constexpr const Vec3 Vec3::ONE = { 1.0f, 1.0f, 1.0f };
constexpr const Vec3 Vec3::ZERO = { 0.0f, 0.0f, 0.0f };


inline std::ostream& operator<<(std::ostream &os, const Vec3 &t)
{
	os << t.x() << t.y() << t.z();
	return os;
}


inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.x()+v2.x(), v1.y()+v2.y(), v1.z()+v2.z());
}


inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.x()-v2.x(), v1.y()-v2.y(), v1.z()-v2.z());
}


inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.x()*v2.x(), v1.y()*v2.y(), v1.z()*v2.z());
}


inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.x()/v2.x(), v1.y()/v2.y(), v1.z()/v2.z());
}


/**
 * Vec3 * float.
 *
 * @param v Vector value.
 * @param t Scalar value.
 *
 * @return vector * float result.
 */
inline Vec3 operator*(const Vec3 &v, float t)
{
	return Vec3(t*v.x(), t*v.y(), t*v.z());
}


/**
 * float * Vec3.
 *
 * @param t Scalar value.
 * @param v Vector value.
 *
 * @return float * vector result.
 */
inline Vec3 operator*(float t, const Vec3 &v)
{
    return Vec3(t*v.x(), t*v.y(), t*v.z());
}


inline Vec3 operator/(const Vec3 &v, float t)
{
	return Vec3(v.x()/t, v.y()/t, v.z()/t);
}


inline float dot(const Vec3 &v1, const Vec3 &v2)
{
	return v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z();
}


inline Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3( 
		(v1.y()*v2.z() - v1.z()*v2.y()),
		(-(v1.x()*v2.z() - v1.z()*v2.x())),
		(v1.x()*v2.y() - v1.y()*v2.x())
	);
}


inline Vec3& Vec3::operator+=(const Vec3 &v1)
{
	v[0] += v1.v[0];
	v[1] += v1.v[1];
	v[2] += v1.v[2];
	return *this;
}


inline Vec3& Vec3::operator-=(const Vec3 &v1)
{
	v[0] -= v1.v[0];
	v[1] -= v1.v[1];
	v[2] -= v1.v[2];
	return *this;
}


inline Vec3& Vec3::operator*=(const Vec3 &v1)
{
	v[0] *= v1.v[0];
	v[1] *= v1.v[1];
	v[2] *= v1.v[2];
	return *this;
}


inline Vec3& Vec3::operator/=(const Vec3 &v1)
{
	v[0] /= v1.v[0];
	v[1] /= v1.v[1];
	v[2] /= v1.v[2];
	return *this;
}


inline Vec3& Vec3::operator*=(const float t)
{
	v[0] *= t;
	v[1] *= t;
	v[2] *= t;
	return *this;
}


inline Vec3& Vec3::operator/=(const float t)
{
	v[0] /= t;
	v[1] /= t;
	v[2] /= t;
	return *this;
}


inline void Vec3::normalize()
{
    float k = length();
    v[0] /= k;
    v[1] /= k;
    v[2] /= k;
}


inline Vec3 unit_vector(Vec3 v)
{
    return v / v.length();
}


#endif //RAYTRACING_VEC3_H
