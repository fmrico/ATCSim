

set(command "/usr/bin/cmake;-GUnix Makefiles;/home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-stamp/googletest-configure-out.log"
  ERROR_FILE "/home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-stamp/googletest-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-stamp/googletest-configure-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "googletest configure command succeeded.  See also /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-stamp/googletest-configure-*.log")
  message(STATUS "${msg}")
endif()
