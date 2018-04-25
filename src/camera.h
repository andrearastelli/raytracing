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
    Camera();
    Ray get_ray(float u, float v);

};


Camera::Camera()
{
    lower_left_corner = {-2.0f, -1.0f, -1.0f};
    horizontal = {4.0f, 0.0f, 0.0f};
    vertical = {0.0f, 2.0f, 0.0f};
    origin = {0.0f, 0.0f, 0.0f};
}


Ray Camera::get_ray(float u, float v)
{
    return {origin, lower_left_corner + u * horizontal + v * vertical - origin};
}


#endif //RAYTRACING_CAMERA_H
