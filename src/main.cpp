#include <iostream>
#include <limits>
#include <random>

#include "image.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "rect.h"
#include "movingsphere.h"
#include "hitablelist.h"
#include "camera.h"
#include "material.h"
#include "parser.h"
#include "texture.h"
#include "box.h"
#include "constantmedium.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Color ray_color(const Ray &r, Hitable *world, int depth);


Hitable *random_scene();
Hitable *test_perlin();
Hitable *cornell_box();


int main(int argc, char *argv[])
{
    auto input_data = parser(argc, argv);

    Image image(input_data.output_path, input_data.width, input_data.height);

    auto samples = input_data.samples;

    //Hitable *world = random_scene();
    //Hitable *world = test_perlin();
    Hitable *world = cornell_box();

    auto lookfrom = Vec3{278.0f, 278.0f, -800.0f};
    auto lookat = Vec3{278.0f, 278.0f, 0.0f};
    auto aperture = 0.0f;
    auto focal_length = (Vec3(-2.0f, 2.0f, 1.0f) - Vec3(0.0f, 0.0f, -1.0f)).length();

    Camera cam{
        lookfrom,
        lookat,
        Vec3::Y,
        40,
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
		
        Color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

        if (depth < 10 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
             return emitted + attenuation * ray_color(scattered, world, depth + 1);
        }
        else
        {
            return emitted;
        }
    }
    else
    {
        return Color(0.0f, 0.0f, 0.0f);
    }
}


Hitable *random_scene()
{
    auto n = 500;
    auto **list = new Hitable*[n+1];
	
	int nx, ny, nn;
	auto file_path = "sample_texture.jpg";
	unsigned char *texture_data = stbi_load(file_path, &nx, &ny, &nn, 0);
	Material *img_mat = new Lambertian(new ImageTexture(texture_data, nx, ny));

    list[0] = new Sphere(
            {0.0f, -1000.0f, 0.0f},
            1000,
            img_mat
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
  
    list[0] = new Sphere({0.0f, 20.0f, 0.0f}, 20.0f, new Lambertian{new NoiseTexture(1.0f)});
    list[1] = new XY_Rect(3, 5, 1, 3, -2, new Lambertian(new ConstantTexture(Color(1.0f, 0.0f, 0.0f))));

    return new HitableList(list, 2);
}


Hitable *simple_light()
{
    Texture *noiseText = new NoiseTexture(4);

    Hitable **list = new Hitable*[4];
    list[0] = new Sphere({0.0f, -1000.0f, 0.0f}, 1000.0f, new Lambertian(noiseText));
    list[1] = new Sphere({0.0f, 2.0f, 0.0f}, 2.0f, new Lambertian(noiseText));
    list[2] = new Sphere({0.0f, 7.0f, 0.0f}, 2.0f, new DiffuseLight(new ConstantTexture(Color(4.0f, 4.0f, 4.0f))));
    list[3] = new XY_Rect(3, 5, 1, 3, -2, new DiffuseLight(new ConstantTexture(Color(4.0f, 4.0f, 4.0f))));

    return new HitableList(list, 4);
}


Hitable *cornell_box()
{
    Hitable **list = new Hitable*[7];
    int i = 0;

    auto c_red = Color(1.0f, 0.0f, 0.0f);
    auto c_green = Color(0.0f, 1.0f, 0.0f);
    auto c_white = Color(0.8f, 0.8f, 0.8f);
    auto c_yellow = Color(1.0f, 1.0f, 0.0f);

    std::cout << c_green << std::endl;

    Material *red = new Lambertian(new ConstantTexture(c_red));
    Material *white = new Lambertian(new ConstantTexture(c_white));
    Material *green = new Lambertian(new ConstantTexture(c_green));
    Material *yellow = new Lambertian(new ConstantTexture(c_yellow));

    Material *light = new DiffuseLight(new ConstantTexture(Color(150, 150, 150)));

    list[i++] = new FlipNormals(new YZ_Rect(0, 555, 0, 555, 555, green));
    list[i++] = new YZ_Rect(0, 555, 0, 555, 0, red);
    std::cout << i << std::endl;

    //list[i++] = new RotateY(new YZ_Rect(0, 555, 0, 555, 555, green), 90.0f);

    //list[i++] = new XZ_Rect(213, 343, 227, 332, 554, light);
    list[i++] = new XZ_Rect(50, 505, 50, 505, 554, light);
    list[i++] = new FlipNormals(new XZ_Rect(0, 555, 0, 555, 555, white));
    list[i++] = new XZ_Rect(0, 555, 0, 555, 0, white);
    list[i++] = new FlipNormals(new XY_Rect(0, 555, 0, 555, 555, white));

    list[i++] = new Translate(new Box(Vec3(0, 0, 0), Vec3(165, 165, 165), white), Vec3(130,0,65));
    list[i++] = new Translate(new Box(Vec3(0, 0, 0), Vec3(165, 330, 165), white), Vec3(265,0,295));

    auto *b1 = new Translate(
            //new RotateY(
                    new Box(
                            Vec3(0, 0, 0), Vec3(165, 330, 165), white
                    )//, 15
            //),
            , Vec3(265,0,295)
    );
    //list[i++] = new ConstantMedium(b1, 0.01f, new ConstantTexture(Color(1.0f, 1.0f, 1.0f)));

    return new HitableList(list, i);
}
