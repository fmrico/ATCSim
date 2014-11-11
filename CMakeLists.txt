cmake_minimum_required (VERSION 2.8.3)
project (ATCSim)

SET(CMAKE_CXX_FLAGS “-std=c++11 -stdlib=libc++”)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-g -Wno-deprecated-declarations")

# add the executable
add_executable(ATCSim
	GUI.h GUI.cpp
	Flight.h Flight.cpp
	Airport.h Airport.cpp
	Position.h Position.cpp
	AirController.h AirController.cpp
	TextDisplay.h TextDisplay.cpp
	Singleton.h
	Common.h
	ATCSim.cpp )

target_link_libraries(ATCSim ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
