cmake_minimum_required (VERSION 2.8.3)
project (ATCSim)

include(makeice.cmake)

SET(CMAKE_CXX_FLAGS “-std=c++11 -stdlib=libc++”)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR} 
	src/lib/
	src/ICE/cpp
)
find_package(Threads REQUIRED)

FIND_LIBRARY(ice_lib Ice)
FIND_LIBRARY(iceutil_lib IceUtil)

set(CMAKE_CXX_FLAGS "-g -Wno-deprecated-declarations")

# add the executable
add_executable(ATCSim
	src/simulator/Flight.h src/simulator/Flight.cpp
	src/simulator/Storm.h src/simulator/Storm.cpp
	src/simulator/Airport.h src/simulator/Airport.cpp
	src/simulator/Position.h src/simulator/Position.cpp
	src/simulator/AirController.h src/simulator/AirController.cpp
	src/simulator/IceComms.h src/simulator/IceComms.cpp
	src/ICE/cpp/ATCDisplay.h src/ICE/cpp/ATCDisplay.cpp
	src/lib/Singleton.h
	src/lib/Common.h
	src/simulator/ATCSim.cpp )
	
add_executable(cppgui
	src/CppGUI/GUI.h src/CppGUI/GUI.cpp
	src/CppGUI/TextDisplay.h src/CppGUI/TextDisplay.cpp
	src/ICE/cpp/ATCDisplay.h src/ICE/cpp/ATCDisplay.cpp
	src/CppGUI/colours.h
	src/lib/Singleton.h
	src/CppGUI/cppgui.cpp )

target_link_libraries(ATCSim
   ${ice_lib}
   ${iceutil_lib}
   ${CMAKE_THREAD_LIBS_INIT}
)

target_link_libraries(cppgui 
 	${ice_lib}
   	${iceutil_lib}
	${CMAKE_THREAD_LIBS_INIT}
	${OPENGL_LIBRARIES} 
	${GLUT_LIBRARY} 
)
