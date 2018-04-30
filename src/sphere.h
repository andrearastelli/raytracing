#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H


#include "hitable.h"
#include "material.h"


class Sphere : public Hitable
{

private:
    Vec3 center;
    float radius;
	Material *mat_ptr;

public:
    Sphere() = default;
	Sphere(Vec3 center, float radius, Material *mat) : center{ center }, radius{ radius }, mat_ptr{ mat } {}

    virtual bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;

};


bool Sphere::hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const
{
    auto oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - a * c;

    if (discriminant > 0)
    {
        auto temp = (-b - std::sqrt(discriminant)) / a;

        if (temp < tmax && temp > tmin)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;

            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / a;

        if (temp < tmax && temp > tmin)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;

            return true;
        }
    }

    return false;
}


#endif //RAYTRACING_SPHERE_H
