#include <PathTracer/util.h>

// Get a random direction in the unit sphere
glm::vec3 util::getRandDirection() {
	glm::vec3 newDirection;

	do {
		newDirection = glm::vec3(
			(util::getRand01() * 2.0) - 1.0,
			(util::getRand01() * 2.0) - 1.0,
			(util::getRand01() * 2.0) - 1.0
		);
	} while (glm::dot(newDirection, newDirection) >= 1.0);

	return newDirection;
}

float util::getRand01() {
	return rand01(gen);
}

glm::vec3 util::getRefraction(const glm::vec3 in, const glm::vec3 normal, const float ratioIndex, bool& refractionExists) {

	const glm::vec3 normIn = glm::normalize(in);
	const float cos_theta = glm::dot(normIn, normal); //angle of incidence

	const float discriminant = 1.0 - ratioIndex * ratioIndex * (1 - cos_theta * cos_theta); // ratioIndex * sin(theta) <= 1

	if (discriminant > 0.0) {
		refractionExists = true;

		glm::vec3 refractionDir =
			ratioIndex * (normIn - normal * cos_theta) - normal * std::sqrt(discriminant);

		return refractionDir;

	}
	else {
		refractionExists = false;

		return glm::vec3(0);
	}

}

float util::schlick(const float cosine, const float refractiveIndex) {
	float r0 = (1.0f - refractiveIndex) / (1.0f + refractiveIndex);
	r0 = r0 * r0;

	return r0 + (1.0f - r0) * glm::pow((1.0f - cosine), 5);
}

bool util::isRayEnteringIntoSurface(const Ray& in, glm::vec3 normal) {
	return (glm::dot(in.getDirection(), normal) <= 0.0f);
}