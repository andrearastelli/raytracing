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


/* === INSTANCING SYSTEM === */


/**
 * Translate Class
 */
class Translate : public Hitable
{

private:
    Hitable *ptr;
    Vec3 offset;

public:
    /**
     * Assignment constructor to store the values of the hitable object
     * and the transformation information.
     *
     * @param p Hitable object.
     * @param displacement Transformation information (offset the initial object location)
     */
    Translate(Hitable *p, const Vec3 &displacement): ptr(p), offset(displacement) {}

    virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const;
    virtual bool bounding_box(float t0, float t1, AABB &box) const;

};


bool Translate::hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const
{
    Ray moved_r(r.origin() - offset, r.direction(), r.time());

    if (ptr->hit(moved_r, t_min, t_max, rec))
    {
        rec.p += offset;
        return true;
    }

    return false;
}


bool Translate::bounding_box(float t0, float t1, AABB &box) const
{
    if (ptr->bounding_box(t0, t1, box))
    {
        box = AABB(box.min() + offset, box.max() + offset);
        return true;
    }

    return false;
}


/**
 * Rotate Y Class
 */
class RotateY : public Hitable
{

private:
    Hitable *ptr;
    float sin_theta;
    float cos_theta;
    bool hasbox;
    AABB bbox;

public:
    /**
     * Rotation Constructor.
     * Evaluate the rotation in terms of sin and cos for the specified angle.
     * Also evaluate the new BBOX for the rotated object.
     *
     * @param p
     * @param angle
     */
    RotateY(Hitable *p, float angle);

    virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const;
    virtual bool bounding_box(float t0, float t1, AABB &box) const { box = bbox; return hasbox; }

};


RotateY::RotateY(Hitable *p, float angle) : ptr(p)
{
    auto radians = static_cast<float>((M_PI / 180.0f) * angle);

    sin_theta = std::sin(radians);
    cos_theta = std::cos(radians);
    hasbox = ptr->bounding_box(0, 1, bbox);

    float FLT_MAX = std::numeric_limits<float>::max();

    auto min = Vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    auto max = Vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for (auto i=0; i<2; ++i)
        for (auto j=0; j<2; ++j)
            for (auto k=0; k<2; ++k)
            {
                auto x = i * bbox.max().x() + (1 - i) * bbox.min().x();
                auto y = j * bbox.max().y() + (1 - j) * bbox.min().y();
                auto z = k * bbox.max().z() + (1 - k) * bbox.min().z();
                auto newx = cos_theta * x + sin_theta * z;
                auto newz = -sin_theta * x + cos_theta * z;

                auto tester = Vec3(newx, y, newz);

                for (auto c=0; c<3; ++c)
                {
                    if (tester[c] > max[c]) max[c] = tester[c];
                    if (tester[c] < min[c]) min[c] = tester[c];
                }
            }

    bbox = AABB(min, max);
}


bool RotateY::hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const
{
    auto origin = r.origin();
    auto direction = r.direction();

    origin[0] = cos_theta * r.origin().x() - sin_theta * r.origin().z();
    origin[2] = -sin_theta * r.origin().x() + cos_theta * r.origin().z();

    direction[0] = cos_theta * r.direction().x() - sin_theta * r.direction().z();
    direction[2] = -sin_theta * r.direction().x() + cos_theta * r.direction().z();

    auto rotated_r = Ray(origin, direction, r.time());

    if (ptr->hit(rotated_r, t_min, t_max, rec))
    {
        auto p = rec.p;
        auto normal = rec.normal;

        p[0] = cos_theta * rec.p.x() + sin_theta * rec.p.z();
        p[2] = -sin_theta * rec.p.x() + cos_theta * rec.p.z();

        normal[0] = cos_theta * rec.normal.x() + sin_theta * rec.normal.z();
        normal[2] = -sin_theta * rec.normal.x() + cos_theta * rec.normal.z();

        rec.p = p;
        rec.normal = normal;

        return true;
    }

    return false;
}


#endif //RAYTRACING_HITABLE_H
