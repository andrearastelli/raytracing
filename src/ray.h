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


Color ray_color(const Ray &r)
{
    auto t = hit_sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5, r);
    if (t > 0.0f)
    {
        auto N = unit_vector(r.point_at_parameter(t) - Vec3(0.0f, 0.0f, -1.0f));
        return 0.5f * Vec3(N.x()+1, N.y()+1, N.z()+1);
    }

    auto unit_direction = unit_vector(r.direction());
    t = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}


#endif //RAYTRACING_RAY_H
