#pragma once

//turn on for TESTS
#define TEST_ON 0
#include <PathTracer/config.h>
#include <PathTracer/util.h>

#include <PathTracer/Camera.h>
#include <PathTracer/Ray.h>
#include <PathTracer/Sphere.h>
#include <PathTracer/Triangle.h>
#include <PathTracer/Materials/Material.h>
#include <PathTracer/Materials/Diffuse.h>
#include <PathTracer/Materials/Metal.h>
#include <PathTracer/Materials/Dielectric.h>
#include <PathTracer/Transform.h>

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

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

//transform tests
namespace TEST {

	void transform_tests(void) {
		glm::mat4 transformation_matrix(
			{ -0.846852f, 0.107965f, -0.520755f, 0.0f },
			{ -0.492958f, -0.526819f, 0.692427f, 0.0f },
			{ -0.199586f, 0.843093f, 0.499359f, 0.0f },
			{ -0.997497f, 0.127171f, -0.613392f, 1.0f }
		);

		Transform test_transform{ transformation_matrix };

		glm::vec3 test_vector{ -0.997497f, 0.127171f, -0.6133920f };
		glm::vec3 test_point{ 0.617481f, 0.170019f, -0.0402539f };
		glm::vec3 test_normal{ -0.281208f, 0.743764f, 0.6064130f };
		Ray test_ray{ {-0.997497f, 0.127171f, -0.613392f}, {0.962222f, 0.264941f, -0.0627278f} };

		fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan), "\nvector    : {} ", glm::to_string(test_vector));
		fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan), "\npoint     : {} ", glm::to_string(test_point));
		fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan), "\nnormal    : {} ", glm::to_string(test_normal));
		fmt::print(fmt::emphasis::bold | fg(fmt::color::cyan), "\nray.o     : {}\nray.d     : {}\n",
			glm::to_string(test_ray.getOrigin()),
			glm::to_string(test_ray.getDirection()));

		glm::vec3 transformed_vector = test_transform.vector(test_vector);
		glm::vec3 transformed_point = test_transform.point(test_point);
		glm::vec3 transformed_normal = test_transform.normal(test_normal);
		Ray transformed_ray = test_transform.ray(test_ray);

		glm::vec3 correct_transformed_vector(0.904467f, -0.6918370f, 0.301205f);
		glm::vec3 correct_transformed_point(-1.596190f, 0.0703303f, -0.837324f);
		glm::vec3 correct_transformed_normal(-0.249534f, 0.0890737f, 0.96426f);
		glm::vec3 correct_transformed_ray_position(-0.0930302f, -0.564666f, -0.312187f);
		glm::vec3 correct_transformed_ray_direction(-0.932945f, -0.088575f, -0.348953f);

		fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "\nxform_vector    : {} ", glm::to_string(transformed_vector - correct_transformed_vector));
		fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "\nxform_point     : {} ", glm::to_string(transformed_point - correct_transformed_point));
		fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "\nxform_normal    : {} ", glm::to_string(transformed_normal - correct_transformed_normal));
		fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "\nxform_ray.o     : {}\nxform_ray.d     : {}\n",
			glm::to_string(transformed_ray.getOrigin() - correct_transformed_ray_position),
			glm::to_string(transformed_ray.getDirection() - correct_transformed_ray_direction));
	}
}