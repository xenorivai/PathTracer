#pragma once

#include <PathTracer/Ray.h>
#include <PathTracer/HitInfo.h>
#include <glm/glm.hpp>

#include <limits>

/*
	Box : 3D Bounding Box.

	based on PBRT and darts2022.
*/

struct Box {
	glm::vec3 m_min;
	glm::vec3 m_max;

	Box() : m_min(std::numeric_limits<float>::max()), m_max(std::numeric_limits<float>::lowest()) {

	}

	Box(const glm::vec3& p) : m_min(p), m_max(p) {

	}

	Box(const glm::vec3& min, const glm::vec3& max) : m_min(min), m_max(max) {

	}

	bool is_empty() const {
		for (int i = 0; i < 3; i++)
			if (m_min[i] > m_max[i])
				return true;
		return false;
	}

	//Enclose another box
	void enclose(const Box& box2) {
		m_min = glm::min(m_min, box2.m_min);
		m_max = glm::max(m_max, box2.m_max);
	}

	//Enclose another point
	void enclose(const glm::vec3& p) {
		m_min = glm::min(m_min, p);
		m_max = glm::max(m_max, p);
	}

	bool contains(const glm::vec3& point, bool proper = false) const {

		// min < point < max
		return proper ? !(glm::any(glm::lessThanEqual(point, m_min)) || glm::any(glm::greaterThanEqual(point, m_max)))
			: !(glm::any(glm::lessThan(point, m_min)) || glm::any(glm::greaterThan(point, m_max)));
	}


	bool is_finite() const {
		return !(std::numeric_limits<float>::has_infinity && (glm::any(glm::equal(glm::vec3(std::numeric_limits<float>::infinity()), m_min)) ||
			glm::any(glm::equal(glm::vec3(std::numeric_limits<float>::infinity()), m_max))));
	}

	glm::vec3 center() const {
		if (!is_finite())
			return glm::vec3();
		else
			return (m_min + m_max) / 2.0f;
	}

	glm::vec3 diagonal() const {
		return m_max - m_min;
	}

	//from darts2022
	bool intersect(const Ray& ray, float tMin, float tMax) const {

		for (int i = 0; i < 3; i++) {
			float inv_d = 1.0f / ray.getDirection()[i];
			float t0 = (m_min[i] - ray.getOrigin()[i]) * inv_d;
			float t1 = (m_max[i] - ray.getOrigin()[i]) * inv_d;
			if (inv_d < 0.0f)
				std::swap(t0, t1);

			tMin = t0 > tMin ? t0 : tMin;
			tMax = t1 < tMax ? t1 : tMax;
			if (tMax < tMin)
				return false;
		}
		return true;
	}
};