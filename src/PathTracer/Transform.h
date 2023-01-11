#pragma once

#include <PathTracer/Ray.h>
#include <PathTracer/HitInfo.h>

#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


/*
	Homogeneous Coordinate transformation : 

	- This struct stores a general 4D homogeneous coordinate transformation, 
	(such as rotation, translation, scaling, and perspective transformations). 

	- Inverse of the transformation is also stored, required for transforming normal vectors.

	- heavily influenced by darts2022
*/


struct Transform {
	glm::mat4 m_xform; //The xform
	glm::mat4 m_inv; //inverse xform

	Transform() : m_xform(glm::mat4(1.0f)), m_inv(glm::mat4(1.0f)) {

	}

	Transform(const glm::mat4& xform) : m_xform(xform), m_inv(glm::inverse(xform)) {
	
	}

	Transform(const glm::mat4& xform, const glm::mat4& inv) : m_xform(xform), m_inv(inv) {
	
	}

	// Return the inverse transformation
	Transform getInverse() const {
		return Transform(m_inv, m_xform);
	}

	// Concatenate with another transform
	Transform operator*(const Transform& t) const {
		return Transform((m_xform * t.m_xform), (t.m_inv * m_inv));
	}

	// Apply the homogeneous transformation to a 3D direction vector
	glm::vec3 vector(const glm::vec3& v) const {
		// A direction vector is transformed without any translation applied -- 
		// the vector v is to treated as a 4D-vector with a 0 in the 4th component.
		return glm::vec3((m_xform * glm::vec4(v, 0.0f)));
	}

	// Apply the homogeneous transformation to a 3D normal
	glm::vec3 normal(const glm::vec3& n) const {
		// Transformation of a normal by the transform matrix m. 
		//		Normals need to be transformed differently than direction vectors;
		//		need to multiply by the transpose of the inverse matrix.
		return glm::normalize(glm::vec3(glm::transpose(m_inv) * glm::vec4(n, 0.f)));
	}

	// Transform a point by an arbitrary matrix in homogeneous coordinates
	glm::vec3 point(const glm::vec3& p) const {
		// Apply translation - interpret the point p to be a 4D-vector with a 1 in the 4th component.
		//
		// return first 3 elements of this vector, divided by the 4th coordinate.

		glm::vec4 temp = (m_xform * glm::vec4(p, 1.0f));
		temp /= temp.w;
		return glm::vec3(temp);
	}

	// Translate this transform according to given 3D translation vector.
	Transform translate(glm::vec3& t) {
		return Transform(m_xform * (glm::translate(glm::mat4(1.0f), t)));
	}

	// Apply the homogeneous transformation to a ray
	Ray ray(const Ray& r) const {

		Ray tempRay = Ray(point(r.getOrigin()), vector(r.getDirection()));

		//NOTE : possible overflow of ray's tMin and tMax
		return tempRay;
	}

};