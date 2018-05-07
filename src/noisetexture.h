#ifndef RAYTRACING_NOISETEXTURE_H
#define RAYTRACING_NOISETEXTURE_H


#include "texture.h"
#include "perlin.h"


class NoiseTexture : public Texture
{

private:
    Perlin noise;

public:
    NoiseTexture() = default;

    virtual Vec3 value(float u, float v, const Vec3 &p) const;

};


Vec3 NoiseTexture::value(float u, float v, const Vec3 &p) const
{
    return Vec3{1.0f, 1.0f, 1.0f} * noise.noise(p);
}


#endif //RAYTRACING_NOISETEXTURE_H
