#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H


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


bool hit_sphere(const Vec3 &center, float radius, const Ray &r)
{
    auto oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0f * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b*b - 4*a*c;

    return (discriminant > 0);
}


Color ray_color(const Ray &r)
{
    if (hit_sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5, r))
        return Color(1.0f, 0.0f, 0.0f);
    Vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}


#endif //RAYTRACING_RAY_H
