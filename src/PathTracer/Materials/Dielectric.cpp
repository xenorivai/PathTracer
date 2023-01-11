#include <PathTracer/Materials/Dielectric.h>

#include <PathTracer/Ray.h>
#include <PathTracer/util.h>

#include <glm/glm.hpp>

Dielectric::Dielectric(const float RefractiveIndex, const glm::vec3 albedo)
	: m_refractiveIndex(RefractiveIndex) {

	/* 
		- ALbedo should always be 1, because dielectric surfaces absorb nothing.
		- But here albedo is b/w (0, 1] , to add tint to the color of the glass.
	*/
	m_albedo = glm::clamp(albedo, 0.0f, 1.0f);
}

Dielectric::~Dielectric() {}

Ray Dielectric::scatter(
	const Ray& inRay,
	const glm::vec3& hit,
	const glm::vec3& normal,
	bool& isAbsorbed
) {

	isAbsorbed = false;

	glm::vec3 outwardNormal;

	// Ratio of the indices of refraction
	float indexRatio;
	float cosine;

	// Step #1:
	// Deal with the ray entering/exiting the surface
	if (util::isRayEnteringIntoSurface(inRay, normal)) {
		outwardNormal = normal;
		indexRatio = 1.0 / m_refractiveIndex;
		cosine = -glm::dot(glm::normalize(inRay.getDirection()), normal);

	}
	else {
		outwardNormal = -normal;
		indexRatio = m_refractiveIndex;
		cosine = glm::dot(glm::normalize(inRay.getDirection()), normal);
	}

	// Step #2:
	// Calculate the refraction and reflection vector

	bool refractionExists = false;
	//glm::vec3 refraction = glm::refract(inRay.getDirection(), outwardNormal, indexRatio);
	glm::vec3 refraction = util::getRefraction(
		inRay.getDirection(),
		outwardNormal,
		indexRatio,
		refractionExists
	);
	glm::vec3 reflection = glm::reflect(inRay.getDirection(), normal);

	// Step #3:
	// Decide if we scatter the reflection or the refraction vector.
	// In real life both reflection and refraction occur,
	// but since we are PathTracing, we randomly pick one out of reflection or refraction.

	float reflectionProb;
	if (refractionExists)
		reflectionProb = util::schlick(cosine, m_refractiveIndex);
	else
		reflectionProb = 1.0;

	return (util::getRand01() < reflectionProb) ? Ray(hit, reflection) : Ray(hit, refraction);
}