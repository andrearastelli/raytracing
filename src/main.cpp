#include <iostream>
#include <limits>
#include <random>

#include "image.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"


Color ray_color(const Ray &r, Hitable *world);


int main()
{
    Image i("test_antialiasing.ppm");

    auto samples = 100;

    Hitable *list[2];

    list[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f);
    list[1] = new Sphere(Vec3(0.0f, -1000.0f, 0.0f), 1000.0f);

    Hitable *world = new HitableList(list, 2);

    Camera cam;

    // RANDOM GENERATORS
    std::random_device d;
    std::mt19937 m{d()};
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (int idY=i.height() - 1; idY>=0; --idY)
    {
        for (int idX=0; idX<i.width(); ++idX)
        {
            auto col = Color(0.0f, 0.0f, 0.0f);

            for (int s=0; s<samples; ++s)
            {
                float u = (idX + dist(m)) / static_cast<float>(i.width());
                float v = (idY + dist(m)) / static_cast<float>(i.height());

                auto r = cam.get_ray(u, v);
                col += ray_color(r, world);
            }

            col /= static_cast<float>(samples);

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
