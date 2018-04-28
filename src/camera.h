#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H


#include "ray.h"


class Camera
{

private:
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;

public:
    Camera(float vfov, float aspect);
    Camera(Vec3 lookfrom, Vec3 lookat, Vec3 up, float vfov, float aspect);
    Ray get_ray(float u, float v);

};


Camera::Camera(float vfov, float aspect)
{
    auto theta = static_cast<float>(vfov * M_PI / 180.0f);
    auto half_height = static_cast<float>(tan(theta / 2.0f));
    auto half_width = aspect * half_height;

    lower_left_corner = {-half_width, -half_height, -1.0f};
    horizontal = {2 * half_width, 0.0f, 0.0f};
    vertical = {0.0f, 2 * half_height, 0.0f};
    origin = {0.0f, 0.0f, 0.0f};
}


Camera::Camera(Vec3 lookfrom, Vec3 lookat, Vec3 up, float vfov, float aspect)
{
    Vec3 u, v, w;
    auto theta = static_cast<float>(vfov * M_PI / 180.0f);
    auto half_height = static_cast<float>(tan(theta / 2.0f));
    auto half_width = aspect * half_height;

    origin = lookfrom;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(up, w));
    v = cross(w, u);

    lower_left_corner = origin - half_width * u - half_height * v - w;
    horizontal = 2 * half_width * u;
    vertical = 2 * half_height * v;
}


Ray Camera::get_ray(float u, float v)
{
    return {origin, lower_left_corner + u * horizontal + v * vertical - origin};
}


#endif //RAYTRACING_CAMERA_H
