#include "GLTFLoader.h"
#ifdef max
#undef max
#endif

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION
#include <tiny_gltf.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>
#include <set>
#include <cmath>


