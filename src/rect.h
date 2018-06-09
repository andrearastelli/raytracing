#ifndef RAYTRACING_RECT_H
#define RAYTRACING_RECT_H


#include "hitable.h"
#include "material.h"


class XY_Rect : public Hitable
{

private:
    Material *material;
    float x0, x1, y0, y1;
    float k;

public:
    XY_Rect() = default;
    XY_Rect(float x0, float x1, float y0, float y1, float k, Material *material)
            : x0(x0), x1(x1), y0(y0), y1(y1), k(k), material(material) {}

    virtual bool hit(const Ray &r, float t0, float t1, HitRecord &rec) const;
    virtual bool bounding_box(float t0, float t1, AABB &box) const;

};


bool XY_Rect::hit(const Ray &r, float t0, float t1, HitRecord &rec) const
{
    auto t = (k - r.origin().z()) / r.direction().z();

    if (t < t0 || t > t1) return false;

    auto x = r.origin().x() + t * r.direction().x();
    auto y = r.origin().y() + t * r.direction().y();

    if (x < x0 || x > x1 || y < y0 || y > y1) return false;

    // rec.u = (x - x0) / (x1 - x0);
    // rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    rec.mat_ptr = material;
    rec.p = r.point_at_parameter(t);
    rec.normal = Vec3(.0f, .0f, 1.0f);

    return true;
}


bool XY_Rect::bounding_box(float t0, float t1, AABB &box) const
{
    box = AABB(Vec3(x0, y0, k-0.0001f), Vec3(x1, y1, k+0.0001f));

    return true;
}




class XZ_Rect : public Hitable
{

private:
    Material *material;
    float x0, x1, z0, z1;
    float k;

public:
    XZ_Rect() = default;
    XZ_Rect(float x0, float x1, float z0, float z1, float k, Material *material)
            : x0(x0), x1(x1), z0(z0), z1(z1), k(k), material(material) {}

    virtual bool hit(const Ray &r, float t0, float t1, HitRecord &rec) const;
    virtual bool bounding_box(float t0, float t1, AABB &box) const;

};


bool XZ_Rect::hit(const Ray &r, float t0, float t1, HitRecord &rec) const
{
    auto t = (k - r.origin().y()) / r.direction().y();

    if (t < t0 || t > t1) return false;

    auto x = r.origin().x() + t * r.direction().x();
    auto z = r.origin().z() + t * r.direction().z();

    if (x < x0 || x > x1 || z < z0 || z > z1) return false;

    // rec.u = (x - x0) / (x1 - x0);
    // rec.v = (z - z0) / (z1 / z0);
    rec.t = t;
    rec.mat_ptr = material;
    rec.p = r.point_at_parameter(t);
    rec.normal = Vec3(.0f, 1.0f, .0f);

    return true;
}


bool XZ_Rect::bounding_box(float t0, float t1, AABB &box) const
{
    box = AABB(Vec3(x0, k-0.0001f, z0), Vec3(x1, k+0.0001f, z1));

    return true;
}




class YZ_Rect : public Hitable
{

private:
    Material *material;
    float y0, y1, z0, z1;
    float k;

public:
    YZ_Rect() = default;
    YZ_Rect(float y0, float y1, float z0, float z1, float k, Material *material)
            : y0(y0), y1(y1), z0(z0), z1(z1), k(k), material(material) {}

    virtual bool hit(const Ray &r, float t0, float t1, HitRecord &rec) const;
    virtual bool bounding_box(float t0, float t1, AABB &box) const;

};


bool YZ_Rect::hit(const Ray &r, float t0, float t1, HitRecord &rec) const
{
    auto t = (k - r.origin().x()) / r.direction().x();

    if (t < t0 || t > t1) return false;

    auto y = r.origin().y() + t * r.direction().y();
    auto z = r.origin().z() + t * r.direction().z();

    if (y < y0 || y > y1 || z < z0 || z > z1) return false;

    // rec.u = (y - y0) / (y1 - y0);
    // rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    rec.mat_ptr = material;
    rec.p = r.point_at_parameter(t);
    rec.normal = Vec3(1.0f, .0f, .0f);

    return true;
}

bool YZ_Rect::bounding_box(float t0, float t1, AABB &box) const
{
    box = AABB(Vec3(k-0.0001f, y0, z0), Vec3(k+0.0001f, y1, z1));

    return true;
}


#endif //RAYTRACING_RECT_H
