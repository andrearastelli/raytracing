#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

/**
*
* Material description.
*
*/

#include "ray.h"
#include "hitable.h"
#include "texture.h"


/**
*
* Base class for the materials.
*
*/
class Material
{
	
public:
    virtual bool scatter(const Ray& ray_in, const HitRecord& hit, Color& attenuation, Ray& scattered) const = 0;

    virtual Color emitted(float u, float v, const Vec3& p) const 
    {
        return Color(0.0f, 0.0f, 0.0f);
    }

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


bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted)
{
    Vec3 v_normalized = unit_vector(v);
    float dt = dot(v_normalized, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
    
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (v_normalized - n * dt) - n * sqrt(discriminant);
        return true;
    }
    else
    {
        return false;
    }
}


float schlick(float cosine, float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;

    return r0 + (1 - r0) * static_cast<float>(std::pow((1 - cosine), 5));
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
	explicit Lambertian(Texture *a) : albedo(a) {};

	Texture *albedo;

	bool scatter(const Ray& ray_in, const HitRecord& hit, Color& attenuation, Ray& scattered) const override
	{
		Vec3 target = hit.p + hit.normal + random_in_unit_sphere();
		scattered = Ray(hit.p, target - hit.p, ray_in.time());
		attenuation = albedo->value(hit.u, hit.v, hit.p);
    
		return true;
	}

};

class Metal : public Material
{
public:
	Metal(const Color& a, float f) : albedo(a) { if (f < 1) fuzziness = f; else fuzziness = 1; };
	
	Color albedo;
	float fuzziness;

	bool scatter(const Ray& ray_in, const HitRecord& hit, Color& attenuation, Ray& scattered) const override
	{
		Vec3 reflected = reflect(unit_vector(ray_in.direction()), hit.normal);
		scattered = Ray(hit.p, reflected + fuzziness * random_in_unit_sphere(), ray_in.time());
		attenuation = albedo;

		return (dot(scattered.direction(), hit.normal) > 0);
	}
};


class Dielectric : public Material
{
public:
    float ref_idx;

    explicit Dielectric(float ri) : ref_idx(ri) {}

    bool scatter(const Ray& r_in, const HitRecord& hit, Color& attenuation, Ray& scattered) const override
    {
        Vec3 outward_normal;
        Vec3 reflected = reflect(r_in.direction(), hit.normal);
        
        float ni_over_nt;
        attenuation = Color(1.0f, 1.0f, 1.0f);
        Vec3 refracted;
        float reflect_prob;
        float cosine;
        
        if (dot(r_in.direction(), hit.normal) > 0)
        {
            outward_normal = -hit.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(r_in.direction(), hit.normal) / r_in.direction().length();
        }
        else
        {
            outward_normal = hit.normal;
            ni_over_nt = 1.0f / ref_idx;
            cosine = -dot(r_in.direction(), hit.normal) / r_in.direction().length();
        }

        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
            reflect_prob = schlick(cosine, ref_idx);
        else
            reflect_prob = 1.0;

        if (dist(m) < reflect_prob)
            scattered = Ray(hit.p, reflected, r_in.time());
        else
            scattered = Ray(hit.p, refracted, r_in.time());

        return true;
    }

};


class DiffuseLight: public Material
{
	
public:
    Texture *emit;

    explicit DiffuseLight(Texture *a): emit(a) {}

    bool scatter(const Ray& ray_in, const HitRecord& hit, Color& attenuation, Ray& scattered) const override
    { 
        return false; 
    }

    Color emitted(float u, float v, const Vec3& p) const override
    {
        return emit->value(u, v, p);
    }
};


class Isotropic : public Material
{

private:
    Texture *albedo;

public:
    explicit Isotropic(Texture *a) : albedo(a) {}

    bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override;

};

bool Isotropic::scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const
{
    scattered = Ray(rec.p, random_in_unit_sphere());
    attenuation = albedo->value(rec.u, rec.v, rec.p);

    return true;
}


#endif //RAYTRACING_MATERIAL_H