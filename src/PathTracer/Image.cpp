#include <PathTracer/Image.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

Image::Image(const int h, const int w) : m_h(h), m_w(w), m_spp(1) {
	data.resize(m_h * m_w);
}

Image::Image(const int h, const int w, const int spp) : m_h(h), m_w(w), m_spp(spp) {
	data.resize(m_h * m_w);
}

bool Image::save(char const* filename) {
	std::vector<unsigned char> udata(m_w * m_h * 3, 0);
	for (int i = 0; i < m_h; ++i)
		for (int j = 0; j < m_w; ++j) {
			udata[3 * (i * m_w + j) + 0] = data[i * m_w + j].x;
			udata[3 * (i * m_w + j) + 1] = data[i * m_w + j].y;
			udata[3 * (i * m_w + j) + 2] = data[i * m_w + j].z;
		}
	stbi_flip_vertically_on_write(true);
	return stbi_write_png(filename, m_w, m_h, 3, &udata[0], sizeof(unsigned char) * m_w * 3) != 0;
}

void Image::write_color(glm::vec3& pixel_color, int i, int j) {

	/*
		- spp = samples_per_pixel = sampling rate (Hz)
		- for each pixel #spp rays are passed through that pixel
		- then color for each sample is averaged into a single color
		- This effectively is supersample antialiasing(multisampling)
	*/
	/*
		instead of adding fractional contribution of each sample each time a ray is passed through the pixel,
		just add the resultant full color due to each sample ,
		and then divide at the end by the number of samples when writing out the color
	*/

	// gamma correction ,with gamma = 2
	data[i * m_w + j] = 255.999f * glm::clamp(glm::sqrt(pixel_color / float(m_spp)), 0.0f, 0.999f);
	return;
}

Image::~Image() = default;
