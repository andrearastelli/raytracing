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


Color ray_color(const Ray &r)
{
    Vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}


#endif //RAYTRACING_RAY_H
