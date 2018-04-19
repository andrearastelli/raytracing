#include <iostream>

#include "image.h"
#include "vec3.h"
#include "ray.h"

int main()
{
    Image i("test.ppm");

    auto lower_corner = Vec3(-2.0f, -1.0f, -1.0f);
    auto horizontal = Vec3(4.0f, 0.0f, 0.0f);
    auto vertical = Vec3(0.0f, 2.0f, 0.0f);
    auto origin = Vec3(0.0f, 0.0f, 0.0f);

    for (int idY=i.height() - 1; idY>=0; --idY)
    {
        for (int idX=0; idX<i.width(); ++idX)
        {
            float u = idX / static_cast<float>(i.width());
            float v = idY / static_cast<float>(i.height());

            auto r = Ray(origin, lower_corner + u * horizontal + v * vertical);
            auto col = ray_color(r);

            i.write(col);
        }
    }

    return 0;
}
