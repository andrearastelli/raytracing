#ifndef RAYTRACING_HITABLE_H
#define RAYTRACING_HITABLE_H


#include "aabb.h"
#include "ray.h"


class Material;


struct HitRecord
{
    float t;
    Vec3 p;
    Vec3 normal;
	Material *mat_ptr;
};


class Hitable
{

public:
    virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const = 0;
    virtual bool bounding_box(float t0, float t1, AABB &box) const = 0;

};


#endif //RAYTRACING_HITABLE_H
