# CMake generated Testfile for 
# Source directory: /home/pablo/git/ATCSim
# Build directory: /home/pablo/git/ATCSim/build_ubuntu_18_04
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Flight_test "Flight_test")
set_tests_properties(Flight_test PROPERTIES  TIMEOUT "5")
add_test(Position_test "Position_test")
set_tests_properties(Position_test PROPERTIES  TIMEOUT "5")
