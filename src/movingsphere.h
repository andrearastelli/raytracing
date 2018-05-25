#ifndef RAYTRACING_MOVINGSPHERE_H
#define RAYTRACING_MOVINGSPHERE_H


#include "hitable.h"
#include "material.h"


class MovingSphere : public Hitable
{

private:
    Vec3 center0, center1;
    float time0, time1;
    float radius;
    Material *mat_ptr;

public:

    /**
     *
     */
    MovingSphere() = default;

    /**
     *
     * @param c0
     * @param c1
     * @param t0
     * @param t1
     * @param r
     * @param m
     */
    MovingSphere(Vec3 c0, Vec3 c1, float t0, float t1, float r, Material *m)
            : center0{c0}, center1{c1}, time0{t0}, time1{t1}, radius{r}, mat_ptr{m} {};

    /**
     *
     * @param r
     * @param tmin
     * @param tmax
     * @param rec
     * @return
     */
    virtual bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;


    /**
     *
     * @param t0
     * @param t1
     * @param box
     * @return
     */
    virtual bool bounding_box(float t0, float t1, AABB &box) const;


    /**
     *
     * @param time
     * @return
     */
    Vec3 center(float time) const;

};


Vec3 MovingSphere::center(float time) const
{
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}


bool MovingSphere::hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const
{
    auto oc = r.origin() - center(r.time());
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
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = mat_ptr;

            return true;
        }

        temp = (-b + std::sqrt(discriminant)) / a;
        if (temp < tmax && temp > tmin)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = mat_ptr;

            return true;
        }
    }

    return false;
}


bool MovingSphere::bounding_box(float t0, float t1, AABB &box) const
{
    auto box0 = center0 - Vec3{radius, radius, radius};
    auto box1 = center1 - Vec3{radius, radius, radius};

    box = AABB(box0, box1);

    return true;
}


#endif //RAYTRACING_MOVINGSPHERE_H
