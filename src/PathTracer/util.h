#pragma once

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <PathTracer/Ray.h>
#include <random>

namespace util {
	inline std::mt19937 gen = std::mt19937(time(0));
	inline std::uniform_real_distribution<> rand01(0.0, 1.0);

	float getRand01();
	glm::vec3 getRandDirection();
	glm::vec3 getRefraction(
		const glm::vec3 in,
		const glm::vec3 normal,
		const float ratioIndex,
		bool& refractionExists
	);
	float schlick(const float cosine, const float refractiveIndex);
	bool isRayEnteringIntoSurface(const Ray& in, glm::vec3 normal);
};