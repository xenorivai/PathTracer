#pragma once

#include <PathTracer/Materials/Material.h>

#include <glm/glm.hpp>

class Diffuse : public Material {

public:

	Diffuse(const glm::vec3& Albedo);

	Ray scatter(
		const Ray& inRay, const glm::vec3& hit, const glm::vec3& normal, bool& isAbsorbed
	) override;
	virtual ~Diffuse();

};