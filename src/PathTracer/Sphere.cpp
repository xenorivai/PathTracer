#include <PathTracer/Sphere.h>
#include <PathTracer/HitInfo.h>
#include <PathTracer/Materials/Material.h>

#include <glm/glm.hpp>

#include <iostream>

Sphere::Sphere() : m_center(0), m_radius(0) {}

Sphere::Sphere(const float Radius, Material* material, const Transform& xform) : m_center(0), m_radius(Radius) {
	m_material = material;
	m_xform = xform;

}

Sphere::Sphere(const glm::vec3& Center, const float Radius, Material* material)
	: m_center(Center), m_radius(Radius) 
{

	m_material = material; // protected member of base class "Surface"
}

void Sphere::setTransform(Transform& xform) {
	m_xform = xform;
}

glm::vec3 Sphere::getCenter() const {
	return m_center;
}

float Sphere::getRadius() const {
	return m_radius;
}

bool Sphere::hit(
	const Ray& ray, const float tMin, const float tMax, HitInfo& hitInfo
) {


	Ray xformed_ray = m_xform.getInverse().ray(ray);
	glm::vec3 oc = xformed_ray.getOrigin();

	float a = glm::dot(xformed_ray.getDirection(), xformed_ray.getDirection());
	float b = glm::dot(xformed_ray.getDirection(), oc); //half_b
	float c = glm::dot(oc, oc) - (m_radius * m_radius);

	float discriminant = b * b - a * c;

	if (discriminant > 0.0f) {

		// We return the 't' that is closer to the ray origin,
		// since we need the closest intersection along the ray.
		float sqrt_d = std::sqrt(discriminant);
		float t1 = (-b - sqrt_d) / a;
		float t2 = (-b + sqrt_d) / a;

		if (t1 < t2 && t1 > tMin && t1 < tMax) {
			hitInfo.t = t1;
			hitInfo.pos = xformed_ray(t1);
		}
		else if (t2 < t1 && t2 > tMin && t2 < tMax) {
			hitInfo.t = t2;
			hitInfo.pos = xformed_ray(t2);
		}
		else
			return false;
		
		hitInfo.normal = (hitInfo.pos) / m_radius;
		hitInfo.pos = m_xform.point(hitInfo.pos);
		hitInfo.normal = m_xform.normal(hitInfo.normal);

		return true;
	}

	return false;
}

Sphere::~Sphere() {
	delete m_material;
}
