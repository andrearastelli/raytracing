#ifndef RAYTRACING_CONSTANTMEDIUM_H
#define RAYTRACING_CONSTANTMEDIUM_H


#include "hitable.h"
#include "material.h"


class ConstantMedium : public Hitable
{

private:
    Hitable *bounday;
    float density;
    Material *phase_function;

public:
    ConstantMedium(Hitable *b, float d, Texture *a) : bounday(b), density(d) { phase_function = new Isotropic(a); }

    virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const;
    virtual bool bounding_box(float t0, float t1, AABB &box) const;

};

bool ConstantMedium::hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const
{
    bool db = (dist(m) < 0.00001);

    // db = false; // ???

    HitRecord rec1, rec2;

    if (bounday->hit(r, -FLT_MAX, FLT_MAX, rec1))
    {
        if (bounday->hit(r, rec1.t + 0.0001f, FLT_MAX, rec2))
        {
            if (db) std::cerr << std::endl << "t0 t1 " << rec1.t << " " << rec2.t << std::endl;
            if (rec1.t < t_min) rec1.t = t_min;
            if (rec2.t > t_max) rec2.t = t_max;

            if (rec1.t >= rec2.t)
                return false;

            if (rec1.t < 0) rec1.t = 0;

            auto distance_inside_boundary = (rec2.t - rec1.t) * r.direction().length();
            auto hit_distance = -(1.0f / density) * std::log(dist(m));

            if (hit_distance < distance_inside_boundary)
            {
                rec.t = rec1.t + hit_distance / r.direction().length();
                rec.p = r.point_at_parameter(rec.t);
                rec.normal = Vec3(1.0f, 0.0f, 0.0f); // arbitrary... ???
                rec.mat_ptr = phase_function;

                return true;
            }
        }
    }

    return false;
}


bool ConstantMedium::bounding_box(float t0, float t1, AABB &box) const
{
    return bounday->bounding_box(t0, t1, box);
}


#endif //RAYTRACING_CONSTANTMEDIUM_H
