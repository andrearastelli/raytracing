#include <iostream>
#include <limits>

#include "image.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"


Color ray_color(const Ray &r, Hitable *world);


int main()
{
    Image i("test_hitable.ppm");

    auto lower_corner = Vec3(-2.0f, -1.0f, -1.0f);
    auto horizontal = Vec3(4.0f, 0.0f, 0.0f);
    auto vertical = Vec3(0.0f, 2.0f, 0.0f);
    auto origin = Vec3(0.0f, 0.0f, 0.0f);

    Hitable *list[2];

    list[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f);
    list[1] = new Sphere(Vec3(0.0f, -1000.0f, 0.0f), 1000.0f);

    Hitable *world = new HitableList(list, 2);

    for (int idY=i.height() - 1; idY>=0; --idY)
    {
        for (int idX=0; idX<i.width(); ++idX)
        {
            float u = idX / static_cast<float>(i.width());
            float v = idY / static_cast<float>(i.height());

            auto r = Ray(origin, lower_corner + u * horizontal + v * vertical);

            auto col = ray_color(r, world);

            i.write(col);
        }
    }

    return 0;
}


Color ray_color(const Ray &r, Hitable *world)
{
    HitRecord rec;

    if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
    {
        return 0.5f * Color(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }
    else
    {
        Vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5f * (unit_direction.y() + 1.0f);
        return (1.0f - t) * Color(1.0f, 1.0f, 1.0f) + t * Color(0.5f, 0.7f, 1.0f);
    }
}
