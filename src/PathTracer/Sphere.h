#pragma once

#include <PathTracer/Surface.h>
#include <PathTracer/Ray.h>
#include <PathTracer/HitInfo.h>
#include <PathTracer/Materials/Material.h>

#include <glm/glm.hpp>

class Sphere : public Surface {
public:

	Sphere();
	Sphere(const float Radius, Material* material, const Transform& xform);
	Sphere(const glm::vec3& Center, const float Radius, Material* material);
	~Sphere();
	bool hit(
		const Ray& ray, const float tMin, const float tMax, HitInfo& hitInfo
	) override;
	void setTransform(Transform& xform);
	glm::vec3 getCenter() const;
	float getRadius() const;

private:

	glm::vec3 m_center;
	float m_radius;
};
