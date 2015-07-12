CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Tutorials)

FIND_PACKAGE(OpenGL REQUIRED)

IF (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
	MESSAGE(FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)")
ENDIF()

IF (CMAKE_SOURCE_DIR MATCHES " ")
	MESSAGE("Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause.")
ENDIF()

IF (CMAKE_BINARY_DIR MATCHES " ")
	MESSAGE("Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause.")
ENDIF()

# Compile external dependencies
ADD_SUBDIRECTORY(external)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
INCLUDE(CreateLaunchers)
INCLUDE(MSVCMultipleProcessCompile) # /MP

INCLUDE_DIRECTORIES(
	external/AntTweakBar-1.16/include/
	external/glfw-3.0.3/include/GLFW/
	external/glm-0.9.4.0/
	external/glew-1.9.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)

SET(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_303
	GLEW_190
)

ADD_DEFINITIONS(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)


# Tutorial 01
ADD_EXECUTABLE(tutorial01_first_window 
	tutorial01_first_window/tutorial01.cpp)
TARGET_LINK_LIBRARIES(tutorial01_first_window ${ALL_LIBS})
# Xcode and Visual working directories
SET_TARGET_PROPERTIES(tutorial01_first_window PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01_first_window/")
CREATE_TARGET_LAUNCHER(tutorial01_first_window WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01_first_window/")


# Tutorial 02
ADD_EXECUTABLE(tutorial02_red_triangle 
	tutorial02_red_triangle/tutorial02.cpp
	common/shader.cpp
	common/shader.h
	tutorial02_red_triangle/SimpleVertexShader.glsl
	tutorial02_red_triangle/SimpleFragmentShader.glsl)
TARGET_LINK_LIBRARIES(tutorial02_red_triangle ${ALL_LIBS})
# Xcode and Visual working directories
SET_TARGET_PROPERTIES(tutorial02_red_triangle PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/")
CREATE_TARGET_LAUNCHER(tutorial02_red_triangle WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/")
CREATE_DEFAULT_TARGET_LAUNCHER(tutorial02_red_triangle WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/") # tut 1 is not the default or people would complain that tut 2 doesn't work


# Tutorial 03
ADD_EXECUTABLE(tutorial03_matrices
	tutorial03_matrices/tutorial03.cpp
	common/shader.cpp
	common/shader.h
	tutorial03_matrices/SimpleTransformVertex.glsl
	tutorial03_matrices/SingleColorFragment.glsl)
TARGET_LINK_LIBRARIES(tutorial03_matrices ${ALL_LIBS})
# Xcode and Visual working directories
SET_TARGET_PROPERTIES(tutorial03_matrices PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial03_matrices/")
CREATE_TARGET_LAUNCHER(tutorial03_matrices WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial03_matrices/") # Visual


# Tutorial 04
ADD_EXECUTABLE(tutorial04_colored_cube
	tutorial04_colored_cube/tutorial04.cpp
	common/shader.cpp
	common/shader.h
	tutorial04_colored_cube/TransformVertexShader.glsl
	tutorial04_colored_cube/ColorFragmentShader.glsl)
TARGET_LINK_LIBRARIES(tutorial04_colored_cube ${ALL_LIBS})
# Xcode and Visual working directories
SET_TARGET_PROPERTIES(tutorial04_colored_cube PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial04_colored_cube/")
CREATE_TARGET_LAUNCHER(tutorial04_colored_cube WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial04_colored_cube/")


# Tutorial 05
ADD_EXECUTABLE(tutorial05_textured_cube
	tutorial05_textured_cube/tutorial05.cpp
	common/shader.cpp
	common/shader.h
	common/texture.cpp
	common/texture.h
	tutorial05_textured_cube/TransformVertexShader.glsl
	tutorial05_textured_cube/TextureFragmentShader.glsl)
TARGET_LINK_LIBRARIES(tutorial05_textured_cube ${ALL_LIBS})
# Xcode and Visual working directories
SET_TARGET_PROPERTIES(tutorial05_textured_cube PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial05_textured_cube/")
CREATE_TARGET_LAUNCHER(tutorial05_textured_cube WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial05_textured_cube/")



SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*glsl$" )

IF (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
ADD_CUSTOM_COMMAND(
	TARGET tutorial01_first_window POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial01_first_window${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01_first_window/"
)
ADD_CUSTOM_COMMAND(
	TARGET tutorial02_red_triangle POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial02_red_triangle${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/"
)
ELSEIF (${CMAKE_GENERATOR} MATCHES "Xcode" )

ENDIF (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
