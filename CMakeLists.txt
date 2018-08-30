cmake_minimum_required(VERSION 2.6)

# lets name the project
project(adl)

# add the -c and -Wall flags
if(MSVC)
	set(CMAKE_CXX_STANDARD 17)
	add_definitions(
		-c
		-W4
	)
else()
	add_definitions(
		-c
		-Wall
		-msse2
		-fms-extensions
		-std=gnu++17
		-nostartfiles
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
file(GLOB_RECURSE ADL_HDRS
	${PROJECT_SOURCE_DIR}/source/engine/*.h
	${PROJECT_SOURCE_DIR}/source/engine/*.hpp
)

# Lets LOAD app our sources!
file(GLOB_RECURSE ADL_SRCS
	${PROJECT_SOURCE_DIR}/source/engine/*.cpp
	${PROJECT_SOURCE_DIR}/source/engine/*.c
)

# Lets LOAD app our headers!
file(GLOB_RECURSE GAME_HDRS
	${PROJECT_SOURCE_DIR}/source/game/*.h
	${PROJECT_SOURCE_DIR}/source/game/*.hpp
)

# Lets LOAD app our sources!
file(GLOB_RECURSE GAME_SRCS
	${PROJECT_SOURCE_DIR}/source/game/*.cpp
	${PROJECT_SOURCE_DIR}/source/game/*.c
)

# Define the executable
add_executable(game ${GAME_HDRS} ${GAME_SRCS} ${ADL_HDRS} ${ADL_SRCS})

# We need a CMAKE_DIR with some code to find external dependencies
SET(ADL_CMAKE_DIR "${PROJECT_SOURCE_DIR}/cmake")

INCLUDE(${ADL_CMAKE_DIR}/Platform.cmake)

#######################################
# LOOK for the packages that we need! #
#######################################

# OpenGL
find_package(OpenGL REQUIRED)

if(UNIX)
	find_package (Threads REQUIRED)
endif (UNIX)

# GLEW
INCLUDE(${ADL_CMAKE_DIR}/FindGLEW.cmake)

# SDL2
INCLUDE(${ADL_CMAKE_DIR}/FindSDL2.cmake)

# ASSIMP
INCLUDE(${ADL_CMAKE_DIR}/FindASSIMP.cmake)

# SPDLOG
INCLUDE(${ADL_CMAKE_DIR}/FindSPDLOG.cmake)

# RAPIDJSON
INCLUDE(${ADL_CMAKE_DIR}/FindRAPIDJSON.cmake)

# FREETYPE
INCLUDE(${ADL_CMAKE_DIR}/FindFREETYPE.cmake)

# STB_IMAGE
INCLUDE(${ADL_CMAKE_DIR}/FindSTBIMAGE.cmake)

# RTTR
INCLUDE(${ADL_CMAKE_DIR}/FindRTTR.cmake)

# IMGUI
# INCLUDE(${ADL_CMAKE_DIR}/FindIMGUI.cmake)

# Google Test
# INCLUDE(${ADL_CMAKE_DIR}/AddGoogleTest.cmake)


# ADL Includes
include_directories(
	${PROJECT_SOURCE_DIR}/headers/
	${PROJECT_SOURCE_DIR}/sources/
	${PROJECT_SOURCE_DIR}/source/
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIR}
	${SDL2_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIRS}
	${SPDLOG_INCLUDE_DIRS}
	${RAPIDJSON_INCLUDE_DIRS}
	${FREETYPE_INCLUDE_DIRS}
	${STBIMAGE_INCLUDE_DIRS}
	${RTTR_INCLUDE_DIRS}
)

# ADL Libs
target_link_libraries( game
	${OPENGL_LIBRARIES}
	${SDL2_LIBRARY}
	${GLEW_LIBRARY}
	${GLEW_LIBRARIES}
	${SDL2_LIBRARIES}
	${ASSIMP_LIBRARIES}
	${FREETYPE_LIBRARIES}
	${RTTR_LIBRARIES}
)

if(UNIX)
	target_link_libraries( game
	${CMAKE_THREAD_LIBS_INIT}
	)
endif(UNIX)

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
	foreach(source IN LISTS ADL_SRCS ADL_HDRS)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${PROJECT_SOURCE_DIR}" "" relative_source_path "${source_path}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
		source_group("${source_path_msvc}" FILES "${source}")
	endforeach()

	foreach(source IN LISTS GAME_SRCS GAME_HDRS)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${PROJECT_SOURCE_DIR}" "" relative_source_path "${source_path}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
		source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()

if(MSVC_IDE)
	foreach(source IN LISTS TEST_HEADERS TEST_SOURCES)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "${PROJECT_SOURCE_DIR}" "" relative_source_path "${source_path}")
		string(REPLACE "/" "\\" source_path_msvc "${relative_source_path}")
		source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
endif()
