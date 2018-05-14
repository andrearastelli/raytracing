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

    /**
     * Noise processing function.
     *
     * This function gives the noise at the given point in space.
     *
     * @param p The space coordinate to use for calculating the Perlin noise value.
     *
     * @return The scalar value for the perlin noise.
     */
    float noise(const Vec3 &p) const;

};


/**
 * Trilinear interpolation function.
 *
 * @todo This function may be better placed into the texture.h header file.
 *
 * @param c
 * @param u
 * @param v
 * @param w
 *
 * @return
 */
inline float trilinear_interpolation(float c[2][2][2], float u, float v, float w)
{
    auto accum = 0.0f;

    for (auto i=0; i<2; ++i)
        for (auto j=0; j<2; ++j)
            for (auto k=0; k<2; ++k)
                accum += (i * u + (1 - i) * (1 - u)) *
                         (j * v + (1 - j) * (1 - v)) *
                         (k * w + (1 - k) * (1 - w)) *
                         c[i][j][k];

    return accum;
}


/*
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
*/


float Perlin::noise(const Vec3 &p) const
{
    auto u = p.x() - std::floor(p.x());
    auto v = p.y() - std::floor(p.y());
    auto w = p.z() - std::floor(p.z());

    // Hermite cubic - smooth the interpolation artifacts.
    u = u * u * (3 - 2 * u);
    v = v * v * (3 - 2 * v);
    w = w * w * (3 - 2 * w);

    auto i = static_cast<int>(std::floor(p.x()));
    auto j = static_cast<int>(std::floor(p.y()));
    auto k = static_cast<int>(std::floor(p.z()));

    float c[2][2][2];

    for (auto di=0; di<2; ++di)
        for (auto dj=0; dj<2; ++dj)
            for (auto dk=0; dk<2; ++dk)
                c[di][dj][dk] = ranfloat[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];

    return trilinear_interpolation(c, u, v, w);
}


/**
 * This function generates a distribution of 256 random [0, 1] values.
 *
 * @return The float[256] array of random [0, 1] values.
 */
static float* perlin_generate()
{
    auto *p = new float[256];
    for (auto i=0; i<256; ++i)
    {
        p[i] = dist(m);
    }

    return p;
}


/**
 * Permutation of an array of values.
 *
 * @param p The source array to permute.
 * @param n The amount of elements to permute.
 */
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


/**
 * Generate an array of integer values [0, 256) and permutes it.
 *
 * @return The resulting permuted array.
 */
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
