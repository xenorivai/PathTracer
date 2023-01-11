#pragma once

#include <PathTracer/Materials/Material.h>
#include <PathTracer/Ray.h>

#include <glm/glm.hpp>

class Dielectric : public Material {
public:

	Dielectric(const float RefractiveIndex, const glm::vec3 albedo = glm::vec3(1.0f));
	~Dielectric() override;

	Ray scatter(
		const Ray& inRay,
		const glm::vec3& hit,
		const glm::vec3& normal,
		bool& isAbsorbed
	) override;

private:

	float m_refractiveIndex;

};
