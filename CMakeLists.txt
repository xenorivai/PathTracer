cmake_minimum_required(VERSION 3.16.0)

project(PathTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
set(PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(PROJECT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(PROJECT_LIBRARIES_DIR "${CMAKE_SOURCE_DIR}/include/ext")

# GLM
set(GLM_DIR "${PROJECT_LIBRARIES_DIR}/glm")
add_subdirectory(${GLM_DIR} EXCLUDE_FROM_ALL)

# FMT
set(FMT_DIR "${PROJECT_LIBRARIES_DIR}/fmt")
add_subdirectory(${FMT_DIR} EXCLUDE_FROM_ALL)

# Executable
add_executable(${PROJECT_NAME} 
   "${PROJECT_SOURCE_DIR}/main.cpp"
   "${PROJECT_SOURCE_DIR}/PathTracer/PathTracer.cpp"
   "${PROJECT_SOURCE_DIR}/PathTracer/Camera.cpp"
   "${PROJECT_SOURCE_DIR}/PathTracer/Ray.cpp"
   "${PROJECT_SOURCE_DIR}/PathTracer/Sphere.cpp"
   "${PROJECT_SOURCE_DIR}/PathTracer/Image.cpp"
   "${PROJECT_SOURCE_DIR}/PathTracer/util.cpp" 
   "${PROJECT_SOURCE_DIR}/PathTracer/Materials/Diffuse.cpp"
   "${PROJECT_SOURCE_DIR}/PathTracer/Materials/Metal.cpp" 
   "${PROJECT_SOURCE_DIR}/PathTracer/Materials/Dielectric.cpp"
   "${PROJECT_SOURCE_DIR}/PathTracer/Triangle.cpp"
)

target_include_directories(
   ${PROJECT_NAME}
   PUBLIC
	  "${PROJECT_INCLUDE_DIR}"
   PRIVATE
	  "${PROJECT_SOURCE_DIR}"
)

target_link_libraries(${PROJECT_NAME} PUBLIC glm)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)


message([PROJECT_SOURCE_DIR]    :\t-- ${PROJECT_SOURCE_DIR})
message([PROJECT_INCLUDE_DIR]   :\t-- ${PROJECT_INCLUDE_DIR})
message([PROJECT_LIBRARIES_DIR] :\t-- ${PROJECT_LIBRARIES_DIR})
message([GLM_DIR]               :\t-- ${GLM_DIR})
message([FMT_DIR]               :\t-- ${FMT_DIR})