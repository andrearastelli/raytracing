#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


#include <cmath>


#include "vec3.h"
#include "color.h"


class Ray
{

private:
    Vec3 a;
    Vec3 b;

public:
    Ray() = default;
    Ray(const Vec3 &a, const Vec3 &b): a{a}, b{b} {}
    ~Ray() = default;

    Vec3 origin() const { return a; }
    Vec3 direction() const { return b; }
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
