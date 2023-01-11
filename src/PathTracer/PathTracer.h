#pragma once

#include <PathTracer/Ray.h>
#include <PathTracer/Sphere.h>
#include <PathTracer/Surface.h>
#include <PathTracer/HitInfo.h>
#include <PathTracer/Image.h>

#include <memory>
#include <fstream>
#include <vector>
#include <string>

class PathTracer {
public:

	PathTracer();
	~PathTracer();
	void run();

private:

	Image m_image;
	void render();
	void printScene() const;
	glm::vec3 getColor(const Ray& ray, std::vector<std::unique_ptr<Surface>>& world, const int depth) const;
};
