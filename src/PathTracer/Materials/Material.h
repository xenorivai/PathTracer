#pragma once

#include <PathTracer/Ray.h>
#include <PathTracer/HitInfo.h>

#include <glm/glm.hpp>

class Material {

public:

	virtual Ray scatter(
		const Ray& inRay, const glm::vec3& hit, const glm::vec3& normal, bool& isAbsorbed
	) = 0;
	virtual ~Material() {}

	glm::vec3 getAlbedo() const { return m_albedo; }

protected:
	/*

	*Fraction of light reflected by a material
	* 0 --> Zero reflection
	* 1 --> Full relflection

	* Across all channels
	* example : m_albedo = (1,0,0) --> all red light is reflected, green and blue are absorbed;

	*/
	glm::vec3 m_albedo;
};
