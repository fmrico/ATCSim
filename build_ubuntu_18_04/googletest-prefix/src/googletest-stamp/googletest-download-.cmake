

set(command "/usr/bin/cmake;-P;/home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/tmp/googletest-gitclone.cmake")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-stamp/googletest-download-out.log"
  ERROR_FILE "/home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-stamp/googletest-download-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-stamp/googletest-download-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "googletest download command succeeded.  See also /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-stamp/googletest-download-*.log")
  message(STATUS "${msg}")
endif()
