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

    virtual bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;

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


#endif //RAYTRACING_HITABLELIST_H
