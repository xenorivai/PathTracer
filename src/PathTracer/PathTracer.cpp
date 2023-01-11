#include <PathTracer/PathTracer.h>

#include <PathTracer/config.h>
#include <PathTracer/util.h>
#include <PathTracer/test.h>

#include <PathTracer/Camera.h>
#include <PathTracer/Ray.h>
#include <PathTracer/Sphere.h>
#include <PathTracer/Triangle.h>
#include <PathTracer/Materials/Material.h>
#include <PathTracer/Materials/Diffuse.h>
#include <PathTracer/Materials/Metal.h>
#include <PathTracer/Materials/Dielectric.h>
#include <PathTracer/Transform.h>
#include <PathTracer/Box.h>

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <limits>
#include <random>
#include <algorithm>
#include <execution>
#include <chrono>

//fmt
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/format-inl.h>
#include <fmt/color.h>

#define MAX_FLOAT std::numeric_limits<float>::max()

PathTracer::PathTracer() : m_image(config::RESOLUTION_H, config::RESOLUTION_W, config::N_SAMPLES) {}

void PathTracer::run() {

	printScene();

	auto startTime = std::chrono::high_resolution_clock::now();

	render();

	auto timeSpan = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startTime);
	int frameTime = static_cast<int>(timeSpan.count());

	std::string filename = config::IMG_TITLE + std::to_string(frameTime) + "sec.png";
	if (m_image.save(filename.c_str()))
		fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "\tImage was rendered successfully! as : {} ", filename.c_str());
	else
		fmt::print(fmt::emphasis::bold | fg(fmt::color::crimson), "\tImage was NOT rendered !");
	return;
}

glm::vec3 PathTracer::getColor(const Ray& ray, std::vector<std::unique_ptr<Surface>>& world, const int depth) const {

	if (depth >= config::MAX_DEPTH)
		return glm::vec3(0.0f);

	HitInfo hitInfo;
	Material* material; //running material
	glm::vec3 normal(0.0f);
	glm::vec3 closestHit(0.0f);
	float closestT = MAX_FLOAT;

	bool somethingWasHit = false;

	//linearly loop over all objects, and test for intersection [ TODO - BVH ]

	for (auto& object : world) {
		if (object->hit(ray, 0.001f, closestT, hitInfo)) {

			//Update only if the hit is closer than what we already have.
			closestHit = hitInfo.pos;
			normal = hitInfo.normal;
			material = object->getMaterial();
			closestT = hitInfo.t;

			somethingWasHit = true;
		}
	}

	if (somethingWasHit) {	//if somethingWasHit recurse : 
		bool isAbsorbed = false;
		Ray scatteredRay = material->scatter(ray, closestHit, normal, isAbsorbed);
		if (isAbsorbed) return glm::vec3(0.0f);
		else {
			glm::vec3 attenuation = material->getAlbedo();

			return (attenuation * getColor(scatteredRay, world, depth + 1));
		}
	}
	//else return background
	return config::Color::background;
}

void PathTracer::render() {

	#if TEST_ON
	//defined in "PathTracer/test.h"

	//perform the tests
	TEST::transform_tests();

	#else

	Camera camera(
		config::Camera::origin,				// origin
		config::Camera::lowerLeftCorner,	// lowerLeftCorner
		config::Camera::horizontal,			// horizontal
		config::Camera::vertical			// vertical
	);

	std::vector<std::unique_ptr<Surface>> world; //list of surfaces
	auto mat1 = new Diffuse(config::Color::red * 0.8f);
	auto mat2 = new Diffuse(glm::vec3(0.1f));
	auto mat3 = new Metal(config::Color::blue * 0.5f + glm::vec3(0.2, 0.2, 0.0), 0.0);
	auto mat4 = new Dielectric(2.42f, glm::vec3(1.0f)); //diamond
	auto mat5 = new Diffuse(config::Color::green * 0.8f);
	auto mat6 = new Diffuse(config::Color::blue * 0.8f);

	//world.push_back(std::make_unique<Sphere>(glm::vec3(0.0, -100.5, -1.0), 100.0, mat2)); //ground
	//world.push_back(std::make_unique<Sphere>(glm::vec3(0.5, 0.0, -1.0), 0.4, mat1));
	//world.push_back(std::make_unique<Sphere>(glm::vec3(-0.5, 0.0, -1.0), 0.4, mat3));
	//world.push_back(std::make_unique<Sphere>(glm::vec3(0.0, 0.0, -1.0), 0.4, mat4));
	//world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, 0.1, -0.5), glm::vec3(0.3, 0.1, -0.5), glm::vec3(0.0, -0.2, -0.5), mat4)); //glass triangle
	//world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, -0.1, -0.7), glm::vec3(0.3, -0.1, -0.7), glm::vec3(0.0, 0.2, -0.5), mat5));


	//transfomed objects
	Transform xfrm1(glm::mat4(1.0f)); //default transform

	world.push_back(std::make_unique<Sphere>(100.0f, mat2, xfrm1.translate(glm::vec3( 0.0, -100.5, -1.0 )))); //ground
	world.push_back(std::make_unique<Sphere>(0.1f, mat1, xfrm1.translate(glm::vec3( 0.5, 0.0, -0.5 )))); //diffuse red ball
	world.push_back(std::make_unique<Sphere>(0.1f, mat3, xfrm1.translate(glm::vec3(-0.5, 0.0, -0.5 )))); //metal blue ball
	world.push_back(std::make_unique<Sphere>(0.1f, mat4, xfrm1.translate(glm::vec3( 0.0, 0.0, -0.5 )))); //glass ball
	world.push_back(std::make_unique<Sphere>(0.01f, mat6, xfrm1.translate(glm::vec3( 0.0, 0.0,-0.65 )))); //small diffuse blue ball
	world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, 0.1, -0.5), glm::vec3(0.3, 0.1, -0.5), glm::vec3(0.0, -0.2, -0.5), mat4)); //glass triangle
	//world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, -0.1, -0.8), glm::vec3(0.3, -0.1, -0.8), glm::vec3(0.0, 0.2, -0.5), mat5)); //green triangle

	world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, -0.1, -0.4), glm::vec3(-0.3, -0.1, -0.7), glm::vec3(-0.3, 0.2, -0.4), mat5)); //lt1
	world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, 0.2 , -0.4), glm::vec3(-0.3, -0.1, -0.7), glm::vec3(-0.3, 0.2, -0.7), mat1)); //lt2

	world.push_back(std::make_unique<Triangle>(glm::vec3(0.3, -0.1, -0.4), glm::vec3(0.3, -0.1, -0.7), glm::vec3(0.3, 0.2, -0.4), mat5)); //rt1
	world.push_back(std::make_unique<Triangle>(glm::vec3(0.3, 0.2 , -0.4), glm::vec3(0.3, -0.1, -0.7), glm::vec3(0.3, 0.2, -0.7), mat1)); //rt2

	world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, 0.2, -0.4), glm::vec3(0.3, 0.2, -0.4) , glm::vec3(-0.3, 0.2, -0.7), mat5)); //ut1
	world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, 0.2, -0.7), glm::vec3(0.3, 0.2, -0.4) , glm::vec3(0.3, 0.2, -0.7), mat1));  //ut2

	world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, -0.1, -0.4), glm::vec3(0.3, -0.1, -0.4), glm::vec3(-0.3, -0.1, -0.7), mat5)); //dt1
	world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, -0.1, -0.7), glm::vec3(0.3, -0.1, -0.4), glm::vec3(0.3 , -0.1, -0.7), mat1)); //dt2

	world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, -0.1, -0.7), glm::vec3(0.3, -0.1, -0.7), glm::vec3(-0.3, 0.2, -0.7), mat5)); //bt1
	world.push_back(std::make_unique<Triangle>(glm::vec3(-0.3, 0.2 , -0.7), glm::vec3(0.3, -0.1, -0.7), glm::vec3(0.3 , 0.2, -0.7), mat1)); //bt2



	if (config::MULTITHREADING) {

		std::vector<int> image_verticals;
		image_verticals.resize(config::RESOLUTION_H);
		for (int i = 0; i < config::RESOLUTION_H; i++) {
			image_verticals[i] = i;
		}

		std::for_each(std::execution::par, image_verticals.begin(), image_verticals.end(),
			[&] (int i) {
				for (int j = 0; j < config::RESOLUTION_W; j++) {
					glm::vec3 pixelColor = glm::vec3(0.0);

					// Antialiasing
					for (int s = 0; s < config::N_SAMPLES; s++) {
						const float u = float(j + util::getRand01()) / float(config::RESOLUTION_W);
						const float v = float(i + util::getRand01()) / float(config::RESOLUTION_H);

						Ray ray = camera.getRay(u, v);
						pixelColor += getColor(ray, world, 0);
					}
					m_image.write_color(pixelColor, i, j);
				}
			});
	}

	else {

		for (int i = 0; i < config::RESOLUTION_H; i++) {
			for (int j = 0; j < config::RESOLUTION_W; j++) {
				glm::vec3 pixelColor = glm::vec3(0.0);

				// Antialiasing
				for (int s = 0; s < config::N_SAMPLES; s++) {
					const float u = float(j + util::getRand01()) / float(config::RESOLUTION_W);
					const float v = float(i + util::getRand01()) / float(config::RESOLUTION_H);

					Ray ray = camera.getRay(u, v);
					pixelColor += getColor(ray, world, 0);
				}
				m_image.write_color(pixelColor, i, j);
			}
		}
	}
	#endif

}

void PathTracer::printScene() const {

	std::vector<std::string> output = {
			fmt::format(fmt::emphasis::bold | fg(fmt::color::cyan),
						"- RESOLUTION_H    : {} ", config::RESOLUTION_H),
			fmt::format(fmt::emphasis::bold | fg(fmt::color::cyan),
						"- RESOLUTION_W    : {} ", config::RESOLUTION_W),
			fmt::format(fmt::emphasis::bold | fg(fmt::color::cyan),
						"- N_SAMPLES       : {} ", config::N_SAMPLES),
			fmt::format(fmt::emphasis::bold | fg(fmt::color::cyan),
						"- MAX_DEPTH       : {} ", config::MAX_DEPTH),
			fmt::format(fmt::emphasis::bold | (config::MULTITHREADING ? fg(fmt::color::lime_green) : fg(fmt::color::crimson)),
						"- MULTITHREADING  : {} ", config::MULTITHREADING),
			fmt::format(fmt::emphasis::bold | fg(fmt::color::cyan),
						"- IMG_TITLE       : {} ", config::IMG_TITLE)
	};
	for (auto& o : output) std::cout << o << std::endl;
	return;
}

PathTracer::~PathTracer() = default;
