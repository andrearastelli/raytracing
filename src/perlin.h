#ifndef RAYTRACING_PERLIN_H
#define RAYTRACING_PERLIN_H


#include "vec3.h"
#include "ray.h"


class Perlin
{

private:
    static int *perm_x;
    static int *perm_y;
    static int *perm_z;
    static float *ranfloat;

public:
    float noise(const Vec3 &p) const;

};


float Perlin::noise(const Vec3 &p) const
{
    auto u = p.x() - std::floor(p.x());
    auto v = p.y() - std::floor(p.y());
    auto w = p.z() - std::floor(p.z());

    auto i = static_cast<int>(4 * p.x()) & 255;
    auto j = static_cast<int>(4 * p.y()) & 255;
    auto k = static_cast<int>(4 * p.z()) & 255;

    return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
}


static float* perlin_generate()
{
    auto *p = new float[256];
    for (auto i=0; i<256; ++i)
    {
        p[i] = dist(m);
    }

    return p;
}


void permute(int *p, int n)
{
    for (auto i=n-1; i>0; i--)
    {
        auto target = static_cast<int>(dist(m) * (i+1));
        auto tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}


static int* perlin_generate_perm()
{
    auto *p = new int[256];

    for (auto i=0; i<256; ++i)
        p[i] = i;

    permute(p, 256);

    return p;
}


float *Perlin::ranfloat = perlin_generate();
int *Perlin::perm_x = perlin_generate_perm();
int *Perlin::perm_y = perlin_generate_perm();
int *Perlin::perm_z = perlin_generate_perm();


#endif //RAYTRACING_PERLIN_H
