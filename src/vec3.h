#include <cmath>
#include <stdlib.h>

class Vec3
{
private:
    float v[3];

public:
    Vec3(float x, float y, float z): v{x, y, z} {}
    Vec3(): v{0.0f, 0.0f, 0.0f} {}

    float x() { return v[0]; }
    float y() { return v[1]; }
    float z() { return v[2]; }
	
	inline const Vec3& operator+() const { return *this; }
	inline Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }
	inline float operator[](int i) const { return v[i]; }
	inline float& operator[](int i) { return v[i]; }
	
	inline Vec3& operator+=(const Vec3 &v2);
	inline Vec3& operator-=(const Vec3 &v2);
	inline Vec3& operator*=(const Vec3 &v2);
	inline Vec3& operator/=(const Vec3 &v2);
	
	inline Vec3& operator*=(const float t);
	inline Vec3& operator/=(const float t);
	
	inline float length() const 
	{
		return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	}
	
	inline float squared_length() const 
	{
		return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
	}
	
	inline void normalize();
};

inline std::istream& operator>>(std::istream &is, Vec3& &t)
{
	is >> t.v[0] >> t.v[1] >> t.v[2];
	return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec3& &t)
{
	os << t.v[0] << t.v[1] << t.v[2];
	return os;
}

inline void Vec3::normalize()
{
	float k = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	v[0] /= k;
	v[1] /= k;
	v[2] /= k;
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

inline Vec3 operator*(const Vec3 &v, float t)
{
	return Vec3(t*v.v[0], t*v.v[1], t*v.v[2]);
}

inline Vec3 operator/(const Vec3 &v, float t)
{
	return Vec3(v.v[0]/t, v.v[1]/t, v.v[2]/t);
}

inline float dot(const Vec3 &v1, const Vec3 &v2)
{
	return v1.v[0]*v2.v[0] + v1.v[1]*v2.v[1] + v1.v[2]*v2.v[2];
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
	return Vec3( 
		(v1.v[1]*v2.v[2] - v1.v[2]*v2.v[1]),
		(-(v1.v[0]*v2.v[2] - v1.v[2]*v2.v[0])),
		(v1.v[0]*v2.v[1] - v1.v[1]*v2.v[0])
	);
}

inline Vec3& Vec3::operato+=(const Vec3 &v)
{
	v[0] += v.v[0];
	v[1] += v.v[1];
	v[2] += v.v[2];
	return *this;
}

inline Vec3& Vec3::operato-=(const Vec3 &v)
{
	v[0] -= v.v[0];
	v[1] -= v.v[1];
	v[2] -= v.v[2];
	return *this;
}

inline Vec3& Vec3::operato*=(const Vec3 &v)
{
	v[0] *= v.v[0];
	v[1] *= v.v[1];
	v[2] *= v.v[2];
	return *this;
}

inline Vec3& Vec3::operato/=(const Vec3 &v)
{
	v[0] /= v.v[0];
	v[1] /= v.v[1];
	v[2] /= v.v[2];
	return *this;
}

inline Vec3& Vec3::operato*=(const float t)
{
	v[0] *= t;
	v[1] *= t;
	v[2] *= t;
	return *this;
}

inline Vec3& Vec3::operato/=(const float t)
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
