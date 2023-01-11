#include <PathTracer/Ray.h>

Ray::Ray() : m_origin(0), m_direction(0) {}

Ray::Ray(const glm::vec3& Origin, const glm::vec3& Direction)
	: m_origin(Origin), m_direction(Direction) {}

Ray::~Ray() = default;

glm::vec3 Ray::getOrigin() const {
	return m_origin;
}

glm::vec3 Ray::getDirection() const {
	return m_direction;
}


glm::vec3 Ray::getPointAtParameter(const float t) const {
	return m_origin + (t * m_direction);
}

glm::vec3 Ray::operator()(const float t) const {
	return m_origin + (t * m_direction);
}