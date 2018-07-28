#ifndef RAYTRACING_HITABLELIST_H
#define RAYTRACING_HITABLELIST_H


#include "hitable.h"


class HitableList : public Hitable
{

private:
    Hitable **list;
    std::size_t list_size;

public:
    HitableList() = default;
    HitableList(Hitable **l, std::size_t size) : list{l}, list_size{size} {}

    bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const override;
    bool bounding_box(float t0, float t1, AABB &box) const override;

};


bool HitableList::hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const
{
    HitRecord temp_rec;
    auto hit_anything = false;
    auto closest_so_far = tmax;

    for (std::size_t idx=0; idx < list_size; ++idx)
    {
        if (list[idx]->hit(r, tmin, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}


bool HitableList::bounding_box(float t0, float t1, AABB &box) const
{
    if (list_size < 1)
        return false;

    AABB temp_box;
    auto first_true = list[0]->bounding_box(t0, t1, temp_box);

    if (!first_true)
        return false;
    else
        box = temp_box;

    for (size_t i=1; i<list_size; ++i)
    {
        if (list[i]->bounding_box(t0, t1, temp_box))
        {
            box = surrounding_box(box, temp_box);
        }
        else
            return false;
    }

    return true;
}


#endif //RAYTRACING_HITABLELIST_H
