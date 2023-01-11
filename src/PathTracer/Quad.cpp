#include <PathTracer/Quad.h>
#include <PathTracer/HitInfo.h>
#include <PathTracer/Materials/Material.h>

#include <glm/glm.hpp>

#include <iostream>

Quad::Quad() : {

}

Quad::Quad(const glm::vec3& x, const glm::vec3& y, const float h, const float w, Material* material) : m_x(x), m_y(y), m_h(h), m_w(w) {

	m_material = material; // protected member of base class "Surface"
}

bool Quad::hit(
	const Ray& ray, const float tMin, const float tMax, HitInfo& hitInfo
) {
	// [ TODO ]
}

Quad::~Quad() {
	delete m_material;
};