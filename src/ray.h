#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


#include <cmath>


#include "vec3.h"
#include "color.h"


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define M_PI 3.14159265358979323846
#endif


std::random_device d;
std::mt19937 m{ d() };
std::uniform_real_distribution<float> dist(0.0f, 1.0f);


class Ray
{

private:
    Vec3 a;
    Vec3 b;
    float t;

public:
    Ray() = default;
    Ray(const Vec3 &a, const Vec3 &b, float t = 0.0f): a{a}, b{b}, t{t} {}
    ~Ray() = default;

    Vec3 origin() const { return a; }
    Vec3 direction() const { return b; }
    float time() const { return t; }
    Vec3 point_at_parameter(float t) const { return a + t * b; }

};


float hit_sphere(const Vec3 &center, float radius, const Ray &r)
{
    auto oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0f * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant < 0)
        return -1.0f;
    else
        return (-b - std::sqrt(discriminant)) / (2.0f * a);
}


#endif //RAYTRACING_RAY_H
