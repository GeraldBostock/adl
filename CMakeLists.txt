cmake_minimum_required(VERSION 2.6)

# lets name the project
project(adl)

MESSAGE("Starting cmake")

# add the -c and -Wall flags
if(MSVC)
	add_definitions(
		-c
		-W4
	)
else()
	add_definitions(
		-c
		-Wall
		-msse2
	)
endif()

if ( CMAKE_BUILD_TYPE STREQUAL "" )
	# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
	# differentiation between debug and release builds.
	set(
		CMAKE_BUILD_TYPE
			"Debug"
		CACHE STRING
			"Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
		FORCE
	)
endif ( CMAKE_BUILD_TYPE STREQUAL "" )

if ( CMAKE_BUILD_TYPE STREQUAL "Release" )
add_definitions( -O2 )
endif ( CMAKE_BUILD_TYPE STREQUAL "Release" )

# Lets LOAD app our headers!
file(GLOB_RECURSE HDRS
	${PROJECT_SOURCE_DIR}/source/*.h
	${PROJECT_SOURCE_DIR}/source/*.hpp
)

# Lets LOAD app our sources!
file(GLOB_RECURSE SRCS
	${PROJECT_SOURCE_DIR}/source/*.cpp
	${PROJECT_SOURCE_DIR}/source/*.c
)

# Define the executable
add_executable(adl ${HDRS} ${SRCS})

# We need a CMAKE_DIR with some code to find external dependencies
SET(ADL_CMAKE_DIR "${PROJECT_SOURCE_DIR}/cmake")

#######################################
# LOOK for the packages that we need! #
#######################################

# OpenGL
find_package(OpenGL REQUIRED)

# GLEW
INCLUDE(${ADL_CMAKE_DIR}/FindGLEW.cmake)

# SDL2
INCLUDE(${ADL_CMAKE_DIR}/FindSDL2.cmake)

# Define the include DIRs
include_directories(
	${PROJECT_SOURCE_DIR}/headers
	${PROJECT_SOURCE_DIR}/sources
	${PROJECT_SOURCE_DIR}/source
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIRS}
)

# Define the link libraries
target_link_libraries( adl
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARIES}
	${ASSIMP_LIBRARIES}
)

if(WIN32)
	string(REPLACE "/" "\\" source_path_windows "${PROJECT_SOURCE_DIR}/res")
	string(REPLACE "/" "\\" build_path_windows "${PROJECT_BINARY_DIR}/res")
	execute_process(COMMAND cmd.exe /c mklink /J "${build_path_windows}" "${source_path_windows}" RESULT_VARIABLE exitcode)
else()
	execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/res ${PROJECT_BINARY_DIR}/res RESULT_VARIABLE exitcode)
endif()

if(NOT ${exitcode} EQUAL 0)
	MESSAGE("SYMLINKING FAILED: ${exitcode}")
	MESSAGE("FALLING BACK TO COPYING")
endif()

#Copy file if the build resource folder contains an older version. This is ignored when the symlink was succesful because the files are already the newest version.
file(GLOB_RECURSE RES RELATIVE ${PROJECT_SOURCE_DIR}/res/ ${PROJECT_SOURCE_DIR}/res/*.*)
foreach(file IN LISTS RES)
	configure_file(${PROJECT_SOURCE_DIR}/res/${file} ${PROJECT_BINARY_DIR}/res/${file} COPYONLY)
endforeach()

#Create virtual folders to make it look nicer in VS
if(MSVC_IDE)
	foreach(source IN LISTS SRCS HDRS)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${PROJECT_SOURCE_DIR}" "" relative_source_path "${source_path}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
		source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()