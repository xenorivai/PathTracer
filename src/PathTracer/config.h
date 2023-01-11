#pragma once

namespace config {
	inline constexpr char* IMG_TITLE = (char*)"img";

	inline constexpr int RESOLUTION_W = 900;  //200
	inline constexpr int RESOLUTION_H = 480;  //100

	// Antialiasing
	inline constexpr int N_SAMPLES = 50;

	//Multithreading
	inline constexpr bool MULTITHREADING = 1;

	//MAX Reflection Depth
	inline constexpr int MAX_DEPTH = 10;


	namespace Camera {
		inline glm::vec3 origin = glm::vec3(0.0);
		inline glm::vec3 lowerLeftCorner = glm::vec3(-2.0, -1.0, -1.0);
		inline glm::vec3 horizontal = glm::vec3(4.0, 0.0, 0.0);
		inline glm::vec3 vertical = glm::vec3(0.0, 2.0, 0.0);
	}

	namespace Color {
		inline glm::vec3 red(1.0, 0.0, 0.0);
		inline glm::vec3 green(0.0, 1.0, 0.0);
		inline glm::vec3 blue(0.0, 0.0, 1.0);
		inline glm::vec3 background(0.9, 0.8, 0.5);
	}
}
