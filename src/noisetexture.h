#ifndef RAYTRACING_NOISETEXTURE_H
#define RAYTRACING_NOISETEXTURE_H


#include "texture.h"
#include "perlin.h"


class NoiseTexture : public Texture
{

private:
    Perlin noise;
    float scale;

public:
    NoiseTexture() = default;

    /**
     * Constructor with scale value for the noise.
     *
     * @param sc Scale value
     */
    NoiseTexture(float sc) : scale(sc) {}

    /**
     * Evaluate the noise function (Perlin noise) at the given point,
     * in the given u,v coordinate.
     *
     * @param u The U coordinate in UV space.
     * @param v The V coordinate in UV space.
     * @param p The point in space to use for evaluating the noise value.
     *
     * @return The resulting Color, per point, of the Noise function.
     */
    virtual Vec3 value(float u, float v, const Vec3 &p) const;

};


float NoiseTexture::scale = 1.0f;


Vec3 NoiseTexture::value(float u, float v, const Vec3 &p) const
{
    return Vec3{1.0f, 1.0f, 1.0f} * noise.noise(scale * p);
}


#endif //RAYTRACING_NOISETEXTURE_H
