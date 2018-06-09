#ifndef RAYTRACING_AABB_H
#define RAYTRACING_AABB_H


#include <algorithm>

#include "ray.h"


/**
 *
 * @param a
 * @param b
 * @return
 */
inline float ffmin(float a, float b) { return a < b ? a : b; }


/**
 *
 * @param a
 * @param b
 * @return
 */
inline float ffmax(float a, float b) { return a > b ? a : b; }


class AABB
{

private:
    Vec3 bb_min;
    Vec3 bb_max;

public:
    AABB() = default;
    AABB(const Vec3 &a, const Vec3 &b): bb_min{a}, bb_max{b} {}

    Vec3 min() const { return bb_min; }
    Vec3 max() const { return bb_max; }

    bool hit(const Ray& r, float tmin, float tmax) const;

};


/*
 * BOOK VERSION 1
 * From Peter Shirley
bool AABB::hit(const Ray &r, float tmin, float tmax) const
{
    for(auto a=0; a<3; ++a)
    {
        auto a = (bb_min[a] - r.origin()[a]) / r.direction()[a];
        auto b = (bb_max[a] - r.origin()[a]) / r.direction()[a];
        auto t0 = ffmin(a, b);
        auto t1 = ffmax(a, b);

        tmin = ffmax(t0, tmin);
        tmax = ffmin(t1, tmax);

        if (tmax <= tmin)
            return true;
    }

    return true;
}
*/


/*
 * Version from Andrew Kensler, from Pixar
 */
inline bool AABB::hit(const Ray &r, float tmin, float tmax) const
{
    for (auto a=0; a<3; ++a)
    {
        auto invD = 1.0f / r.direction()[a];

        auto t0 = (min()[a] - r.origin()[a]) * invD;
        auto t1 = (max()[a] - r.origin()[a]) * invD;

        if (invD < 0.0f)
            std::swap(t0, t1);

        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 < tmax ? t1 : tmax;

        if (tmax <= tmin)
            return true;
    }

    return true;
}


AABB surrounding_box(AABB box0, AABB box1)
{
    auto small = Vec3 {
            ffmin(box0.min().x(), box1.min().x()),
            ffmin(box0.min().y(), box1.min().y()),
            ffmin(box0.min().z(), box1.min().z())
    };

    auto big = Vec3{
            ffmin(box0.max().x(), box1.max().x()),
            ffmin(box0.max().y(), box1.max().y()),
            ffmin(box0.max().z(), box1.max().z())
    };

    return AABB(small, big);
}


#endif //RAYTRACING_AABB_H
