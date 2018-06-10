#ifndef RAYTRACING_BOX_H
#define RAYTRACING_BOX_H


#include "rect.h"
#include "hitablelist.h"


class Box : public Hitable
{

private:
    Vec3 min;
    Vec3 max;
    Hitable *list_ptr;

public:
    Box() = default;
    Box(const Vec3 &p0, const Vec3 &p1, Material *ptr);

    virtual bool hit(const Ray &r, float t0, float t1, HitRecord &rec) const;
    virtual bool bounding_box(float t0, float t1, AABB &box) const;

};


Box::Box(const Vec3 &p0, const Vec3 &p1, Material *ptr)
{
    min = p0;
    max = p1;

    Hitable **list = new Hitable*[6];

    size_t i = 0;

    auto pxy = new XY_Rect(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr);
    auto pxz = new XZ_Rect(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr);
    auto pyz = new YZ_Rect(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr);

    list[i++] =                 new XY_Rect(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr);
    list[i++] = new FlipNormals(new XY_Rect(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

    list[i++] =                 new XZ_Rect(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr);
    list[i++] = new FlipNormals(new XZ_Rect(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

    list[i++] =                 new YZ_Rect(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr);
    list[i++] = new FlipNormals(new YZ_Rect(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));

    list_ptr = new HitableList(list, i);
}


bool Box::hit(const Ray &r, float t0, float t1, HitRecord &rec) const
{
    return list_ptr->hit(r, t0, t1, rec);
}


bool Box::bounding_box(float t0, float t1, AABB &box) const
{
    box = AABB(min, max);

    return true;
}


#endif //RAYTRACING_BOX_H
