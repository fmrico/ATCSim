cmake_minimum_required (VERSION 3.5)
project (ATCSim)

set(CMAKE_BUILD_TYPE Debug)

include(cmake/makeice.cmake)
include(cmake/CppLint.cmake)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(OpenGL REQUIRED)

set(Ice_LIBRARY "/usr/lib/x86_64-linux-gnu/libIce.so")
set(IceUtil_LIBRARY "/usr/lib/x86_64-linux-gnu/libIceutil.so")

find_package(Ice REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR}
	src/lib/
	src/ICE/cpp
  src/simulator
)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wno-deprecated-declarations")

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra ")
endif()


## Building ATCSIM #################################################

set(_link_flags "-lice -liceutils")

set(ATCSIM_SRCS
  src/simulator/Flight.h src/simulator/Flight.cpp
  src/simulator/Storm.h src/simulator/Storm.cpp
  src/simulator/Airport.h src/simulator/Airport.cpp
  src/simulator/Position.h src/simulator/Position.cpp
  src/simulator/AirController.h src/simulator/AirController.cpp
  src/simulator/IceComms.h src/simulator/IceComms.cpp
  src/ICE/cpp/ATCDisplay.h src/ICE/cpp/ATCDisplay.cpp
  src/lib/Singleton.h
  src/lib/Common.h
)

set(CPPGUI_SRCS
  src/CppGUI/GUI.h src/CppGUI/GUI.cpp
  src/CppGUI/TextDisplay.h src/CppGUI/TextDisplay.cpp
  src/ICE/cpp/ATCDisplay.h src/ICE/cpp/ATCDisplay.cpp
  src/CppGUI/colours.h
  src/lib/Singleton.h
  src/CppGUI/cppgui.cpp
)

add_library(ATCSimLib SHARED ${ATCSIM_SRCS})
target_link_libraries(ATCSimLib
  ${Ice_LIBRARIES}
  ${IceUtil_LIBRARIES}
)

# add the executable
add_executable(ATCSim
  src/simulator/ATCSim.cpp
)

add_executable(cppgui ${CPPGUI_SRCS})

target_link_libraries(ATCSim
  ${Ice_LIBRARIES}
  ${IceUtil_LIBRARIES}
   ${CMAKE_THREAD_LIBS_INIT}
   ATCSimLib
)

target_link_libraries(cppgui
  ${Ice_LIBRARIES}
  ${IceUtil_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
	${OPENGL_LIBRARIES}
	${GLUT_LIBRARY}
)

## CppLint #################################################

add_style_check_target(ATCSim_cpplint "${ATCSIM_SRCS}")
add_style_check_target(cppgui_cpplint "${CPPGUI_SRCS}")

## Testing #################################################

include(cmake/gtest.cmake)
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
foreach(_test_file ${TEST_SRC_FILES})
    get_filename_component(_test_name ${_test_file} NAME_WE)
    add_executable(${_test_name} ${_test_file})
    add_dependencies(${_test_name} googletest)
    target_link_libraries(${_test_name} gtest gtest_main
      ${CMAKE_THREAD_LIBS_INIT}
      ${Ice_LIBRARIES}
      ${IceUtil_LIBRARIES}
      ATCSimLib)
    add_test(${_test_name} ${_test_name})
    set_tests_properties(${_test_name} PROPERTIES TIMEOUT 5)
endforeach()
