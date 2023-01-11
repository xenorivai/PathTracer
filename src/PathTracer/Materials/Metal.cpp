#include <PathTracer/Materials/Metal.h>

#include <PathTracer/Ray.h>
#include <PathTracer/util.h>

#include <glm/glm.hpp>

Metal::Metal(const glm::vec3& Albedo, const float Fuzz) {
	//protected member m_albedo
	m_albedo = Albedo;

	if (Fuzz > 1.0f || Fuzz < 0.0f)
		m_fuzz = 1.0f;
	else
		m_fuzz = Fuzz;
}

Ray Metal::scatter(const Ray& inRay, const glm::vec3& hit, const glm::vec3& normal, bool& isAbsorbed) {

	glm::vec3 normInRay = glm::normalize(inRay.getDirection()); //normalized incident ray

	//glm::vec3 reflDirection = (normInRay - 2 * glm::dot(normInRay, normal) * normal);
	//reflDirection += m_fuzz * util::getRandDirection();

	glm::vec3 reflDirection = glm::reflect(normInRay, normal);
	reflDirection += m_fuzz * util::getRandDirection();

	Ray reflectedRay(hit, reflDirection);
	isAbsorbed = (glm::dot(reflDirection, normal) < 0); //if internal reflection,then ray is absorbed
	return reflectedRay;
}

Metal::~Metal() {}
