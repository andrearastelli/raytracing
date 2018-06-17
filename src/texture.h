#ifndef TEXTUREH
#define TEXTUREH 

#include "vec3.h"
#include "color.h"
#include "perlin.h"


class Texture 
{
    public:
        virtual Color value(float u, float v, const Vec3& p) const = 0;
};


class ConstantTexture: public Texture
{
    public:
        ConstantTexture() {}

        ConstantTexture(Color c) : color(c) {}

        virtual Color value(float u, float v, const Vec3& p) const
        {
            return color;
        }

        Color color;
};


class CheckerTexture: public Texture
{
    public:
        CheckerTexture() {}

        CheckerTexture(Texture *t0, Texture *t1): even(t0), odd(t1) {}

        virtual Color value(float u, float v, const Vec3& p) const
        {
            float sines = sin(10*p.x()) * sin(10*p.y()) *sin(10*p.z());

            if (sines < 0)
                return odd->value(u, v, p);
            else
                return even->value(u, v, p);
        }

        Texture *odd;
        
        Texture *even;
};


class ImageTexture: public Texture
{
public:
    ImageTexture() {}

    ImageTexture(unsigned char *pixels, int A, int B) : data(pixels), nx(A), ny(B) {}

    virtual Color value(float u, float v, const Vec3& p) const;

    unsigned char *data;
    int nx;
    int ny;
};


Color ImageTexture::value(float u, float v, const Vec3& p) const 
{
    int i = static_cast<int>(u * nx);
    int j = static_cast<int>((1 - v) * ny - 0.001f);

    if (i < 0) i = 0;
    if (j < 0) j = 0;

    if (i > nx - 1) i = nx - 1;
    if (j > ny - 1) i = ny - 1;

    float r = int(data[3 * i + 3 * nx * j]) / 255.0f;
    float g = int(data[3 * i + 3 * nx * j + 1]) / 255.0f;
    float b = int(data[3 * i + 3 * nx * j + 2]) / 255.0f;

    return Color(r, g, b);
}


/**
 *
 * NOISE TEXTURE
 *
 */
class NoiseTexture : public Texture
{

private:
    Perlin noise;
    float scale = 1.0f;

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
    virtual Color value(float u, float v, const Vec3 &p) const;

};


Color NoiseTexture::value(float u, float v, const Vec3 &p) const
{
    return Color(1.0f, 1.0f, 1.0f) * noise.noise(scale * p);
}


#endif
