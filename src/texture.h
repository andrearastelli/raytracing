#ifndef TEXTUREH
#define TEXTUREH 

#include "vec3.h"
#include "color.h"


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
    int i = u * nx;
    int j = (1 - v) * ny - 0.001f;

    if (i < 0) i = 0;
    if (j < 0) j = 0;

    if (i > nx - 1) i = nx - 1;
    if (j > ny - 1) i = ny - 1;

    float r = int(data[3 * i + 3 * nx * j]) / 255.0f;
    float g = int(data[3 * i + 3 * nx * j + 1]) / 255.0f;
    float b = int(data[3 * i + 3 * nx * j + 2]) / 255.0f;

    return Color(r, g, b);
}

#endif
