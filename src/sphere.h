#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include "hitable.h"
#include "material.h"

#define M_PI 3.14159265358979323846


void get_sphere_uv(const Vec3& p, float& u, float& v)
{
	float phi = atan2(p.z(), p.x());
	float theta = asin(p.y());
	u = 1.0f - (phi + M_PI) / (2.0f * M_PI);
	v = (theta + M_PI / 2.0f) / M_PI;
}


class Sphere: public Hitable
{

private:
    Vec3 center;
    float radius;
    Material *mat_ptr;

public:
    Sphere() = default;
    Sphere(Vec3 center, float radius, Material *mat) : center{ center }, radius{ radius }, mat_ptr{ mat } {}

    virtual bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;
	virtual bool bounding_box(float t0, float t1, AABB &box) const;

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
            get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;

            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / a;

        if (temp < tmax && temp > tmin)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;

            return true;
        }
    }

    return false;
}


bool Sphere::bounding_box(float t0, float t1, AABB &box) const
{
    box = AABB(
            center - Vec3{radius, radius, radius},
            center + Vec3{radius, radius, radius}
    );

    return true;
}


#endif //RAYTRACING_SPHERE_H
