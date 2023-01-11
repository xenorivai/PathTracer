#pragma once

#include <PathTracer/Surface.h>
#include <PathTracer/Ray.h>
#include <PathTracer/HitInfo.h>
#include <PathTracer/Materials/Material.h>

#include <glm/glm.hpp>

class Triangle : public Surface {
public:

	Triangle();
	Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, Material* material);
	~Triangle();
	bool hit(
		const Ray& ray, const float tMin, const float tMax, HitInfo& hitInfo
	) override;
	void setTransform(Transform& xform);

private:
	glm::vec3 m_v0;
	glm::vec3 m_v1;
	glm::vec3 m_v2;

};