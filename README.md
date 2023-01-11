# PathTracer

It's a Path Tracer !

---
#### Results : 
- [ TODO ] Add result images.
#### Features : 
- Multi Threading : `std::for_each` and `std::execution_policy::par` based multi-threading. 
	- Get to know more [here](https://www.youtube.com/watch?v=46ddlUImiQA) 
- Materials : Diffuse, Metal, Dielectric. 
	- [ TODO ] Add textures?
- Surfaces & Acceleration Structures : Spheres, Triangles, Quads[ WIP ]. 
	- [ TODO ] Add Acceleration structures(bvh).
- MSAA (Multi sampling Anti aliasing)

### How to Build and Run :

Tested working on `Windows 10 + Visual Studio 2022`, probably also works on `Linux` ヽ(￣～￣　)ノ.

#### Prerequisites : 
- [CMake](https://cmake.org/download/) >= 3.16.0
- `C++ 17` Compiler (`ninja` + `MSVC` + VS2022 tested)
- [GLM](https://github.com/g-truc/glm.git)
- [fmt](https://fmt.dev/latest/index.html)


#### Build :
If using `Visual Studio 2022` : 
- Just open the folder in VS2022, it should pickup the `CMakeLists.txt` and `CMakeSettings.json` file, and configure everything accordingly, then you can build and run (or debug) the project in VS2022.
	- Add a `x64-Release` configuration in `CMakeSettings.json` (in VS2022) if not configured properly.
- [ TODO ] : Add an image explaining above steps.

or 

```
$ git clone --recurse-submodules https://github.com/xenorivai/PathTracer.git
$ mkdir build
$ mkdir bin
$ cd build
$ cmake ..
$ cmake --build .
```

#### Usage :
Run the executable in generated in `/bin/<config_name>/` either by double clicking or :
```
$ cd bin
$ cd <config>
$ ./PathTracer.exe
```
And then the output image would be generated.

[ TODO ] Add an image of `bin/<config_name>` directory.
#### Directory Structure :
```
	PathTracer/
	├── bin/
	│   ├── debug/
	│   └── release/
	├── build/
	│   ├── x64-Debug/
	│   └── x64-Release/
	├── include/
	│   └── ext/
	│       ├── fmt/
	│       └── glm/
	└── src/
		├── PathTracer/              
		|   ├── Materials/
		│   ├── PathTracer.cpp
		│   ├── PathTracer.h
		│   ├── config.h             .... config for scene
		│   ├── test.h               .... small tests
		|   ├── ... [other files]
		└── main.cpp                 .... entry point.
```
Note : `build/` directory's structure might differ according to the CMake Generator used.
#### References and Resources :
- Ray - Triangle Intersection Test (Moller-Trumbore) : [Scratch-A-Pixel](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection.html)
- [Dartmouth College, Rendering Algorithms (Fall 2022)](https://cs87-dartmouth.github.io/Fall2022/)
- [PBRT 3rd Edition](https://pbr-book.org/3ed-2018/contents)
