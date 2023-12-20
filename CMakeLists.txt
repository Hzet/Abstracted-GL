cmake_minimum_required (VERSION 3.12)

include(FetchContent)
include(ExternalProject)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DAGL_DEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLFW_INCLUDE_NONE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLFW_WIN32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTB_IMAGE_IMPLEMENTATION")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_ENABLE_EXPERIMENTAL")
set(BUILD_SHARED_LIBS false)

option(AGL_ENABLE_PROFILING "Collet profiling measurements" true)

project (AGL)

# AGL_LOGGER
# ----------
file (
	GLOB_RECURSE 
	AGL_LOGGER_SOURCES 
	CONFIGURE_DEPENDS 
	"logger/src/*.cpp"
)

file (
	GLOB_RECURSE 
	AGL_LOGGER_HEADERS 
	CONFIGURE_DEPENDS 
	"logger/include/*.hpp" 
	"logger/include/*.inl"
)

add_library(
	AGL_LOGGER 
	${AGL_LOGGER_SOURCES}
	${AGL_LOGGER_HEADERS}
)

target_include_directories(
	AGL_LOGGER
	PUBLIC "logger/include/"
)

# AGL_DEBUG
# ---------
file (
	GLOB_RECURSE 
	AGL_DEBUG_SOURCES 
	CONFIGURE_DEPENDS 
	"debug/src/*.cpp"
)

file (
	GLOB_RECURSE 
	AGL_DEBUG_HEADERS 
	CONFIGURE_DEPENDS 
	"debug/include/*.hpp" 
	"debug/include/*.inl"
)

add_library(
	AGL_DEBUG 
	${AGL_DEBUG_SOURCES}
	${AGL_DEBUG_HEADERS}
)

add_dependencies(
	AGL_DEBUG 
	AGL_LOGGER
)

target_include_directories(
	AGL_DEBUG
	PUBLIC "debug/include/"
)

target_link_libraries(
	AGL_DEBUG
	PUBLIC AGL_LOGGER
)

# AGL_PROFILER
# ------------
if(AGL_ENABLE_PROFILING)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAGL_ENABLE_PROFILING")

	file (
		GLOB_RECURSE 
		AGL_PROFILER_SOURCES 
		CONFIGURE_DEPENDS 
		"profiler/src/*.cpp"
	)

	file (
		GLOB_RECURSE 
		AGL_PROFILER_HEADERS 
		CONFIGURE_DEPENDS 
		"profiler/include/*.hpp" 
		"profiler/include/*.inl"
	)

	add_library(
		AGL_PROFILER
		${AGL_PROFILER_SOURCES}
		${AGL_PROFILER_HEADERS}
	)

	add_dependencies(
		AGL_PROFILER
		AGL_DEBUG
	)

	target_include_directories(
		AGL_PROFILER
		PUBLIC "profiler/include/"
	)

	target_link_libraries(
		AGL_PROFILER
		PUBLIC AGL_DEBUG
	)
endif()


# AGL_UID
# -------
file (
	GLOB_RECURSE 
	AGL_UID_SOURCES 
	CONFIGURE_DEPENDS 
	"uid/src/*.cpp"
)

file (
	GLOB_RECURSE 
	AGL_UID_HEADERS 
	CONFIGURE_DEPENDS 
	"uid/include/*.hpp" 
	"uid/include/*.inl"
)

add_library(
	AGL_UID 
	${AGL_UID_SOURCES}
	${AGL_UID_HEADERS}
)

add_dependencies(
	AGL_UID
	AGL_DEBUG 
)

target_include_directories(
	AGL_UID
	PUBLIC "uid/include/"
)

if(AGL_ENABLE_PROFILING)
	target_link_libraries(
		AGL_UID
		PUBLIC AGL_PROFILER
	)
else()
	target_link_libraries(
		AGL_UID
		PUBLIC AGL_DEBUG
	)
endif()

# AGL_ECS
# -------
file (
	GLOB_RECURSE 
	AGL_ECS_SOURCES 
	CONFIGURE_DEPENDS 
	"ecs/src/*.cpp"
)

file (
	GLOB_RECURSE 
	AGL_ECS_HEADERS 
	CONFIGURE_DEPENDS 
	"ecs/include/*.hpp" 
	"ecs/include/*.inl"
)

add_library(
	AGL_ECS 
	${AGL_ECS_SOURCES}
	${AGL_ECS_HEADERS}
)

add_dependencies(
	AGL_ECS
	AGL_UID
)

target_include_directories(
	AGL_ECS
	PUBLIC "ecs/include/"
)

target_link_libraries(
	AGL_ECS
	PUBLIC AGL_UID
)

# AGL_LIB dependencies
# --------------------

# OpenGL
# ------
find_package(OpenGL 4.2 REQUIRED)

# GLFW
# -----
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.2.1
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
	FetchContent_Populate(glfw)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

# GLM
# ----
FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG		   0.9.9.2
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
	FetchContent_Populate(glm)
	set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
	add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()


# STB
# ---
FetchContent_Declare(
	stb
	GIT_REPOSITORY https://github.com/nothings/stb.git
)

FetchContent_GetProperties(stb)
if(NOT stb)
	FetchContent_Populate(stb)
	#include the headerfiles and libs
endif()


# Freetype
# --------
FetchContent_Declare(
	freetype
	GIT_REPOSITORY https://github.com/aseprite/freetype2.git
	GIT_TAG		   VER-2-6-3 
)

FetchContent_GetProperties(freetype)
if(NOT freetype_POPULATED)
	FetchContent_Populate(freetype)
	add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
endif()

# AGL_LIB
# -------
file (
	GLOB_RECURSE 
	AGL_LIB_SOURCES 
	CONFIGURE_DEPENDS 
	"agl/src/*.cpp"
	"agl/external/*.c"
	"agl/external/*.cpp"
)

file (
	GLOB_RECURSE 
	AGL_LIB_HEADERS 
	CONFIGURE_DEPENDS 
	"agl/include/*.hpp" 
	"agl/include/*.inl"
	"agl/external/*.h"
	"agl/external/*.hpp"
)

add_library(
	AGL_LIB 
	${AGL_LIB_SOURCES}
	${AGL_LIB_HEADERS}
)

add_dependencies(
	AGL_LIB
	OpenGL::GL
	glfw
	freetype
	glm
	AGL_ECS
)

target_include_directories(
	AGL_LIB
	PUBLIC "agl/include/"
	PUBLIC "agl/external/"
    PUBLIC "${freetype_SOURCE_DIR}/include/"
    PUBLIC "${glfw_SOURCE_DIR}/include/"
	PUBLIC "${glm_SOURCE_DIR}"
    PUBLIC "${stb_SOURCE_DIR}/include/"
)

target_link_libraries(
	AGL_LIB
	PUBLIC OpenGL::GL
	PUBLIC glfw
	PUBLIC freetype
	PUBLIC glm
	PUBLIC AGL_ECS
)	

# AGL_EDITOR
file (
	GLOB_RECURSE 
	AGL_EDITOR_SOURCES 
	CONFIGURE_DEPENDS 
	"editor/src/*.cpp"
)

file (
	GLOB_RECURSE 
	AGL_EDITOR_HEADERS 
	CONFIGURE_DEPENDS 
	"editor/include/*.hpp" 
	"editor/include/*.inl"
)

file (
	GLOB_RECURSE 
	AGL_EDITOR_RESOURCES
	CONFIGURE_DEPENDS 
	"editor/resource/*.*" 
)

# copy 
set(AGL_EDITOR_RESOURCES_DIR "editor/resource/")
file(
	COPY
	${AGL_EDITOR_RESOURCES}
	DESTINATION
	"${AGL_BINARY_DIR}/resource/"
)

add_executable(
	AGL_EDITOR 
	${AGL_EDITOR_SOURCES}
	${AGL_EDITOR_HEADERS}
	${AGL_EDITOR_RESOURCES}
)

add_dependencies(
	AGL_EDITOR
	AGL_LIB
)

target_include_directories(
	AGL_EDITOR
	PUBLIC "editor/include/"
)

target_link_libraries(
	AGL_EDITOR
	PUBLIC AGL_LIB
)

target_compile_options(AGL_EDITOR PRIVATE "-Wall" "-std=c++17") #"-Wpedantic"