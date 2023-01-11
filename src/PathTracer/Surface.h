#pragma once

#include <PathTracer/Ray.h>
#include <PathTracer/HitInfo.h>
#include <PathTracer/Materials/Material.h>
#include <PathTracer/Transform.h>

#include <memory>
#include <iostream>

#include <glm/glm.hpp>

class Surface {
public:

	virtual bool hit(
		const Ray& ray, const float tMin, const float tMax, HitInfo& hitInfo
	) = 0;

	Transform getTransform() const {
		return m_xform;
	}

	Material* getMaterial() const {
		return m_material;
	}
protected:
	Transform m_xform;
	Material* m_material;
};
