#pragma once

#include <PathTracer/Surface.h>
#include <PathTracer/Ray.h>
#include <PathTracer/HitInfo.h>
#include <PathTracer/Materials/Material.h>

#include <glm/glm.hpp>
#include <vector>

class Quad : public Surface {
public:

	Quad();
	Quad(const glm::vec3& x, const glm::vec3& y, const float h, const float w, Material* material);
	~Quad();
	bool hit(
		const Ray& ray, const float tMin, const float tMax, HitInfo& hitInfo
	) override;

private:
	glm::vec3 m_x; //x coordinate of topleft corner
	glm::vec3 m_y; //y coordinate of topleft corner
	float m_h; //quad height
	float m_w; //quad width
};