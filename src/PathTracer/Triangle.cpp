#include <PathTracer/Triangle.h>
#include <PathTracer/HitInfo.h>
#include <PathTracer/Materials/Material.h>

#include <glm/glm.hpp>

#include <iostream>

Triangle::Triangle() :m_v0(glm::vec3(0)), m_v1(glm::vec3(0)), m_v2(glm::vec3(0)) {

}

Triangle::Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, Material* material) : m_v0(v0), m_v1(v1), m_v2(v2) {

	m_material = material; // protected member of base class "Surface"
}

void Triangle::setTransform(Transform& xform) {
	m_xform = xform;
}

bool Triangle::hit(
	const Ray& ray, const float tMin, const float tMax, HitInfo& hitInfo
) {
	//Moller-Trumbore Triangle Intersection Test : (not using barycentric coords)
	const float EPSILON = 0.0000001f;
	glm::vec3 e1 = m_v1 - m_v0;
	glm::vec3 e2 = m_v2 - m_v0;

	float det, inv_det;
	glm::vec3 pvec = glm::cross(ray.getDirection(), e2);
	det = glm::dot(e1, pvec);

	if (det > -EPSILON && det < EPSILON)
		return false;

	inv_det = 1.0f / det;
	glm::vec3 tvec = ray.getOrigin() - m_v0;

	float u = glm::dot(tvec, pvec) * inv_det;
	if (u < 0.0f || u > 1.0f)
		return false;

	glm::vec3 qvec = glm::cross(tvec, e1);
	float v = glm::dot(ray.getDirection(), qvec) * inv_det;
	if (v < 0.0f || u + v > 1.0f)
		return false;

	float t = glm::dot(e2, qvec) * inv_det;

	if (t < tMin || t > tMax)
		return false;

	// n : geometric normal of the triangle(normalized cross product of two edges)
	glm::vec3 n = normalize(cross(e1, e2));

	// Because we've hit the triangle, fill in the intersection data
	hitInfo.t		= t;
	hitInfo.pos		= ray(t);
	hitInfo.normal	= n;

	return true;
}

Triangle::~Triangle() {
	delete m_material;
};