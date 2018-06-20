#ifndef RAYTRACING_BVHNODE_H
#define RAYTRACING_BVHNODE_H


#include "hitable.h"


int box_x_compare(const void *a, const void *b);
int box_y_compare(const void *a, const void *b);
int box_z_compare(const void *a, const void *b);


class BVHNode : public Hitable
{

private:
    Hitable *left;
    Hitable *right;
    AABB box;

public:
    BVHNode() = default;
    BVHNode(Hitable **l, std::size_t n, float time0, float time1);
    bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const override;
    bool bounding_box(float t0, float t1, AABB &b) const override;

};


BVHNode::BVHNode(Hitable **l, std::size_t n, float time0, float time1)
{
    auto axis = static_cast<int>(3 * dist(m));

    if (axis == 0)
        std::qsort(l, n, sizeof(Hitable*), box_x_compare);
    else if (axis == 1)
        std::qsort(l, n, sizeof(Hitable*), box_y_compare);
    else
        std::qsort(l, n, sizeof(Hitable*), box_z_compare);

    if (n == 1)
    {
        left = right = l[0];
    }
    else if (n == 2)
    {
        left = l[0];
        right = l[1];
    }
    else
    {
        left = new BVHNode(l, n/2, time0, time1);
        right = new BVHNode(l + n/2, n - n/2, time0, time1);
    }

    AABB box_left, box_right;

    if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
        std::cerr << "No bounding box in BVHNode constructor." << std::endl;

    box = surrounding_box(box_left, box_right);

}


bool BVHNode::hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const
{
    if (box.hit(r, tmin, tmax))
    {
        HitRecord left_rec, right_rec;
        auto hit_left = left->hit(r, tmin, tmax, left_rec);
        auto hit_right = right->hit(r, tmin, tmax, right_rec);

        if (hit_left && hit_right)
        {
            if (left_rec.t < right_rec.t)
                rec = left_rec;
            else
                rec = right_rec;

            return true;
        }
        else if (hit_left)
        {
            rec = left_rec;
            return true;
        }
        else if (hit_right)
        {
            rec = right_rec;
            return true;
        }
        else
            return false;
    }

    return false;
}


bool BVHNode::bounding_box(float t0, float t1, AABB &b) const
{
    b = box;
    return true;
}


int box_x_compare(const void *a, const void *b)
{
    AABB box_left, box_right;

    Hitable *ah = *(Hitable**)a;
    Hitable *bh = *(Hitable**)b;

    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
        std::cerr << "No BVH node in BVH constructor" << std::endl;

    if (box_left.min().x() - box_right.min().x() < 0.0f)
        return -1;
    else
        return 1;
}


int box_y_compare(const void *a, const void *b)
{
    AABB box_left, box_right;

    Hitable *ah = *(Hitable**)a;
    Hitable *bh = *(Hitable**)b;

    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
        std::cerr << "No BVH node in BVH constructor" << std::endl;

    if (box_left.min().y() - box_right.min().y() < 0.0f)
        return -1;
    else
        return 1;
}


int box_z_compare(const void *a, const void *b)
{
    AABB box_left, box_right;

    Hitable *ah = *(Hitable**)a;
    Hitable *bh = *(Hitable**)b;

    if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
        std::cerr << "No BVH node in BVH constructor" << std::endl;

    if (box_left.min().z() - box_right.min().z() < 0.0f)
        return -1;
    else
        return 1;
}


#endif //RAYTRACING_BVHNODE_H
