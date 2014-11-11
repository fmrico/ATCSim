cmake_minimum_required (VERSION 2.8.3)
project (ATCSim)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(CMAKE_CXX_FLAGS "-g")

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

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(ATCSim ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
