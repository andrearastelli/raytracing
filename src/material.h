#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

/**
*
* Material description.
*
*/

#include "ray.h"
#include "hitable.h"


/**
*
* Base class for the materials.
*
*/
class Material
{
public:
	virtual bool scatter(const Ray& ray_in, const HitRecord& hit, Color& attenuation, Ray& scattered) const = 0;

};

/**
*
* Utilities functions
*
*/
Vec3 reflect(const Vec3& v, const Vec3& normal)
{
	return v - 2 * dot(v, normal) * normal;
}

Vec3 random_in_unit_sphere()
{
	Vec3 p;

	do {

		p = 2.0f * Vec3(dist(m), dist(m), dist(m)) - Vec3(1.0f, 1.0f, 1.0f);

	} while (p.squared_length() >= 1.0f);

	return p;
}

/**
*
* Materials implementations
*
*/
class Lambertian : public Material
{
public:
	Lambertian(const Color& a) : albedo(a) {};

	Color albedo;

	virtual bool scatter(const Ray& ray_in, const HitRecord& hit, Color& attenuation, Ray& scattered) const
	{
		Vec3 target = hit.p + hit.normal + random_in_unit_sphere();
		scattered = Ray(hit.p, target - hit.p);
		attenuation = albedo;

		return true;
	}

};

class Metal : public Material
{
public:
	Metal(const Color& a, float f) : albedo(a) { if (f < 1) fuzziness = f; else fuzziness = 1; };
	
	Color albedo;
	float fuzziness;

	virtual bool scatter(const Ray& ray_in, const HitRecord& hit, Color& attenuation, Ray& scattered) const
	{
		Vec3 reflected = reflect(unit_vector(ray_in.direction()), hit.normal);
		scattered = Ray(hit.p, reflected + fuzziness * random_in_unit_sphere());
		
		attenuation = albedo;

		return (dot(scattered.direction(), hit.normal) > 0);
	}
};

#endif //RAYTRACING_MATERIAL_H