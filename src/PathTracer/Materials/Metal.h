#pragma once

#include <PathTracer/Materials/Material.h>
#include <PathTracer/Ray.h>

#include <glm/glm.hpp>

class Metal : public Material {

public:

	Metal(const glm::vec3& Albedo, const float Fuzz);
	~Metal() override;
	Ray scatter(const Ray& inRay, const glm::vec3& hit, const glm::vec3& normal, bool& isAbsorbed) override;

private:

	float m_fuzz;

};