#pragma once

#include <glm/glm.hpp>

class Ray {
public:

	Ray();
	Ray(const glm::vec3& Origin, const glm::vec3& Direction);
	~Ray();

	glm::vec3 getOrigin() const;
	glm::vec3 getDirection() const;
	glm::vec3 getPointAtParameter(const float t) const;
	glm::vec3 operator()(const float t) const;

private:

	glm::vec3 m_origin;
	glm::vec3 m_direction;
};
