#include <cmath>
#include <array>
#include <iostream>


class Vec3
{

private:
    std::array<float, 3> v;

public:
    Vec3(float x, float y, float z): v{x, y, z} {}
    Vec3(): v{0.0f, 0.0f, 0.0f} {}

    float x() const { return v[0]; }
    float y() const { return v[1]; }
    float z() const { return v[2]; }
	
	inline const Vec3& operator+() const { return *this; }
	inline Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }
	inline float operator[](int i) const { return v[i]; }
	inline float& operator[](int i) { return v[i]; }
	
	inline Vec3& operator+=(const Vec3 &v);
	inline Vec3& operator-=(const Vec3 &v);
	inline Vec3& operator*=(const Vec3 &v);
	inline Vec3& operator/=(const Vec3 &v);
	
	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);
	
	inline float length() const 
	{
		return std::sqrtf(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	}
	
	inline float squared_length() const 
	{
		return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
	}
	
	inline void normalize();

};


inline void Vec3::normalize()
{
    float k = length();
    v[0] /= k;
    v[1] /= k;
    v[2] /= k;
}


inline std::ostream& operator<<(std::ostream &os, const Vec3& &t)
{
	os << t.x() << t.y() << t.z();
	return os;
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.v[0]+v2.v[0], v1.v[1]+v2.v[1], v1.v[2]+v2.v[2]);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.v[0]-v2.v[0], v1.v[1]-v2.v[1], v1.v[2]-v2.v[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.v[0]*v2.v[0], v1.v[1]*v2.v[1], v1.v[2]*v2.v[2]);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3(v1.v[0]/v2.v[0], v1.v[1]/v2.v[1], v1.v[2]/v2.v[2]);
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
	return Vec3(t*v.v[0], t*v.v[1], t*v.v[2]);
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
    return Vec3(t*v.v[0], t*v.v[1], t*v.v[2]);
}

inline Vec3 operator/(const Vec3 &v, float t)
{
	return Vec3(v.v[0]/t, v.v[1]/t, v.v[2]/t);
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

inline Vec3& Vec3::operator+=(const Vec3 &v)
{
	v[0] += v.v[0];
	v[1] += v.v[1];
	v[2] += v.v[2];
	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3 &v)
{
	v[0] -= v.v[0];
	v[1] -= v.v[1];
	v[2] -= v.v[2];
	return *this;
}

inline Vec3& Vec3::operator*=(const Vec3 &v)
{
	v[0] *= v.v[0];
	v[1] *= v.v[1];
	v[2] *= v.v[2];
	return *this;
}

inline Vec3& Vec3::operator/=(const Vec3 &v)
{
	v[0] /= v.v[0];
	v[1] /= v.v[1];
	v[2] /= v.v[2];
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

inline Vec3 unit_vector(Vec3 v)
{
	return v / v.length();
}
