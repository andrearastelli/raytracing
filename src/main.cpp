#include <iostream>
#include <limits>
#include <random>

#include "image.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"
#include "material.h"
#include "parser.h"


Color ray_color(const Ray &r, Hitable *world, int depth);


int main(int argc, char *argv[])
{
    auto input_data = parser(argc, argv);

    Image image(input_data.output_path, input_data.width, input_data.height);

    auto samples = input_data.samples;
    
    Hitable *list[4];

    std::size_t i = 0;
    list[i++] = new Sphere(Vec3(0.0f, -1000.0f, 0.0f), 1000.0f - 0.1f, new Lambertian(Color(0.8f, 0.3f, 0.3f)));
    list[i++] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(Color(0.8f, 0.8f, 0.0f)));
    list[i++] = new Sphere(Vec3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Color(0.8f, 0.6f, 0.2f), 0.3f));
	list[i++] = new Sphere(Vec3(-1.0f, 0.0f, -1.0f), 0.5f, new Metal(Color(0.8f, 0.8f, 0.8f), 0.5f));

    Hitable *world = new HitableList(list, i);

    auto lookfrom = Vec3{-2.0f, 2.0f, 1.0f};
    auto lookat = Vec3{0.0f, 0.0f, -1.0f};
    auto aperture = 2.0f;
    auto focal_length = (Vec3(-2.0f, 2.0f, 1.0f) - Vec3(0.0f, 0.0f, -1.0f)).length();

    Camera cam{
        lookfrom,
        lookat,
        Vec3::Y,
        35,
        static_cast<float>(image.width()) / static_cast<float>(image.height()),
        aperture,
        focal_length
    };

	// RANDOM GENERATORS
	std::random_device d;
	std::mt19937 m{ d() };
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
                col += ray_color(r, world, 0);
            }

            col /= static_cast<float>(samples);

            image.write(col.gamma());
        }
    }

    return 0;
}


Color ray_color(const Ray &r, Hitable *world, int depth)
{
    HitRecord rec;

    if (world->hit(r, 0.001f, std::numeric_limits<float>::max(), rec))
    {
        Ray scattered;
        Color attenuation;

        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
             return attenuation * ray_color(scattered, world, depth + 1);
        }
        else
        {
            return Color(0, 0, 0);
        }
    }
    else
    {
        Vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5f * (unit_direction.y() + 1.0f);
        return (1.0f - t) * Color(1.0f, 1.0f, 1.0f) + t * Color(0.5f, 0.7f, 1.0f);
    }
}
