#ifndef IMAGE_H
#define IMAGE_H

#include <glm/glm.hpp>
#include <vector>

class Image {
	std::vector<glm::vec3> data;
	int m_h;
	int m_w;
	int m_spp;
public:
	Image(const int h, const int w);
	Image(const int h, const int w, const int spp);
	~Image();

	int getWidth() { return m_w; }
	int getHeight() { return m_h; }
	bool save(char const* filename);
	void write_color(glm::vec3& pixel_color, int i, int j);

};

#endif