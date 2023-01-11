#include <PathTracer/Materials/Diffuse.h>

#include <PathTracer/Ray.h>
#include <PathTracer/util.h>

#include <glm/glm.hpp>
#include <iostream>

Diffuse::Diffuse(const glm::vec3& Albedo) {
	m_albedo = Albedo;
}

Ray Diffuse::scatter(
	const Ray& inRay, const glm::vec3& hit, const glm::vec3& normal, bool& isAbsorbed
) {
	isAbsorbed = false;

	return Ray(hit, normal + util::getRandDirection());
}

Diffuse::~Diffuse() {}
