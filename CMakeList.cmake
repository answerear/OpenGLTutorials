CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Tutorials)

FIND_PACKAGE(OpenGL REQUIRED)

IF (CMAKE_BINARY_DIR STREUQAL CMAKE_SOURCE_DIR)
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

