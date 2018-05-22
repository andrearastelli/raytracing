#include <iostream>
#include <limits>
#include <random>

#include "image.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "movingsphere.h"
#include "hitablelist.h"
#include "camera.h"
#include "material.h"
#include "parser.h"
#include "texture.h"


Color ray_color(const Ray &r, Hitable *world, int depth);


Hitable *random_scene();
Hitable *test_perlin();


int main(int argc, char *argv[])
{
    auto input_data = parser(argc, argv);

    Image image(input_data.output_path, input_data.width, input_data.height);

    auto samples = input_data.samples;

    //Hitable *world = random_scene();
    Hitable *world = test_perlin();

    auto lookfrom = Vec3{10.0f, 0.0f, 0.0f};
    auto lookat = Vec3{0.0f, 0.0f, 0.0f};
    auto aperture = 0.0f;
    auto focal_length = (Vec3(-2.0f, 2.0f, 1.0f) - Vec3(0.0f, 0.0f, -1.0f)).length();

    Camera cam{
        lookfrom,
        lookat,
        Vec3::Y,
        35,
        static_cast<float>(image.width()) / static_cast<float>(image.height()),
        aperture,
        focal_length,
        0.0f,
        1.0f
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


Hitable *random_scene()
{
    auto n = 500;
    auto **list = new Hitable*[n+1];

    list[0] = new Sphere(
            {0.0f, -1000.0f, 0.0f},
            1000,
            new Lambertian(new CheckerTexture(
				new ConstantTexture(Color(0.2f, 0.3f, 0.1f)),
				new ConstantTexture(Color(0.9f, 0.9f, 0.9f))
				)
			)
    );

    std::size_t i = 1;

    for (auto a = -11; a < 11; ++a)
    {
        for (auto b = -11; b < 11; ++b)
        {
            auto choose_mat = dist(m);
            auto center = Vec3{a + 0.9f * dist(m), 0.2f, b + 0.9f * dist(m)};

            if ((center - Vec3{4.0f, 0.2f, 0.0f}).length() > 0.9f)
            {
                if (choose_mat < 0.8f)
                {
                    list[i++] = new MovingSphere(
                            center,
                            center + Vec3(0.0f, 0.5f * dist(m), 0.0f),
                            0.0f, // Time 0
                            1.0f, // Time 1
                            0.2f,
                            new Lambertian(
                                new ConstantTexture(Color(dist(m) * dist(m), dist(m) * dist(m), dist(m) * dist(m)))
                            )
                    );
                }
                else if (choose_mat < 0.95f)
                {
                    list[i++] = new Sphere(
                            center,
                            // center + Vec3(0.0f, 0.5f * dist(m), 0.0f),
                            // 0.0f,
                            // 0.1f,
                            0.2f,
                            new Metal(
                                    {0.5f * (1 + dist(m)), 0.5f * (1 + dist(m)), 0.5f * (1 + dist(m))},
                                    0.5f * dist(m)
                            )
                    );
                }
                else
                {
                    list[i++] = new Sphere(
                            center,
                            // center + Vec3(0.0f, 0.5f * dist(m), 0.0f),
                            // 0.0f,
                            // 0.1f,
                            0.2f,
                            new Dielectric(1.5f)
                    );
                }
            }
        }
    }

    list[i++] = new Sphere({0.0f, 1.0f, 0.0f}, 1.0f, new Dielectric(1.5));
    list[i++] = new Sphere({-4.0f, 1.0f, 0.0f}, 1.0f, new Lambertian(new ConstantTexture(Color(0.4f, 0.2f, 0.1f))));
    list[i++] = new Sphere({4.0f, 1.0f, 0.0f}, 1.0f, new Metal({0.7f, 0.6f, 0.5f}, 0.0f));

    return new HitableList(list, i);
}


Hitable *test_perlin()
{
    auto **list = new Hitable*[2];

    list[0] = new Sphere({0.0f, 20.0f, 0.0f}, 20.0f, new Lambertian{new NoiseTexture(2.0f)});
    list[1] = new Sphere({0.0f, -20.0f, 0.0f}, 20.0f, new Lambertian{new NoiseTexture(5.0f)});

    return new HitableList(list, 2);
}
