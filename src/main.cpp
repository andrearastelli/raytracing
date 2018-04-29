#include <iostream>
#include <limits>
#include <random>

#include "image.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"

std::random_device d;
std::mt19937 m{d()};
std::uniform_real_distribution<float> dist(0.0f, 1.0f);

Vec3 random_in_unit_sphere();

Color ray_color(const Ray &r, Hitable *world);


int main()
{
    Image image("test_camera.ppm");

    auto samples = 256;

    auto R = static_cast<float>(cos(M_PI / 4.0f));

    Hitable *list[3];

    int i = 0;
    list[i++] = new Sphere(Vec3(0.0f, -1000.0f, 0.0f), 1000.0f - 0.5f);
    list[i++] = new Sphere(Vec3(-R, 0.0f, -1.0f), 0.5f);
    list[i++] = new Sphere(Vec3(R, 0.0f, -1.0f), 0.5f);

    Hitable *world = new HitableList(list, i);

    // Camera cam(90, static_cast<float>(image.width()) / static_cast<float>(image.height()));
    Camera cam{
        Vec3(-2.0f, 2.0f, 1.0f),
        Vec3(0.0f, 0.0f, -1.0f),
        Vec3::Y,
        20,
        static_cast<float>(image.width()) / static_cast<float>(image.height())
    };

    // RANDOM GENERATORS
    std::random_device d;
    std::mt19937 m{d()};
    auto max_rand_jitter = 1.0f - 1.0f / samples;
    std::uniform_real_distribution<float> jitter(0.0f, max_rand_jitter);

    // IMAGE PROCESSING
    for (int idY=image.height() - 1; idY>=0; --idY)
    {
        for (int idX=0; idX<image.width(); ++idX)
        {
            auto col = Color(0.0f, 0.0f, 0.0f);

            for (int s=0; s<samples; ++s)
            {
                float u = (idX + jitter(m)) / static_cast<float>(image.width());
                float v = (idY + jitter(m)) / static_cast<float>(image.height());

                auto r = cam.get_ray(u, v);
                col += ray_color(r, world);
            }

            col /= static_cast<float>(samples);

            image.write(col.gamma());
        }
    }

    return 0;
}


Vec3 random_in_unit_sphere()
{
    Vec3 p;

    do {

        p = 2.0f * Vec3(dist(m), dist(m), dist(m)) - Vec3(1.0f, 1.0f, 1.0f);

    } while(p.squared_length() >= 1.0f);

    return p;
}


Color ray_color(const Ray &r, Hitable *world)
{
    HitRecord rec;

    if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
    {
        auto target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5f * ray_color(Ray(rec.p, target - rec.p), world);
    }
    else
    {
        Vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5f * (unit_direction.y() + 1.0f);
        return (1.0f - t) * Color(1.0f, 1.0f, 1.0f) + t * Color(0.5f, 0.7f, 1.0f);
    }
}
