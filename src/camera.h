/**
 * Camera definition.
 *
 * The camera class defines a very simple camera that has:
 * - Position
 * - Point to look at
 * - Vertical FOV
 * - Aspect ratio
 *
 * To properly orient in 3D space, the camera has to be given
 * the UP vector.
 */

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
    /**
     * Simple constructor that defines a custom oriented camera
     * using only vertical fov and aspect ratio.
     *
     * @param vfov Vertical FOV of the camera.
     * @param aspect Aspect ratio of the camera.
     */
    Camera(float vfov, float aspect);

    /**
     * Custom positionable camera with specific definition for
     * looking at a specific point in space, from a specific point,
     * with vertical FOV and aspect ratio.
     *
     * @param lookfrom Point defining the source position of the camera.
     * @param lookat Point defining the lookat point for the camera.
     * @param up Up vector to help define the orientation of the camera.
     * @param vfov Vertical FOV.
     * @param aspect Aspect ratio.
     */
    Camera(Vec3 lookfrom, Vec3 lookat, Vec3 up, float vfov, float aspect);

    /**
     * Ray "emitted" from the camera into the world using the
     * (U, V) coordinate of the frame.
     *
     * @param u U coordinate of the frame.
     * @param v V coordinate of the frame.
     *
     * @return The Ray emitted from the camera into the world.
     */
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
