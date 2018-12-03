

set(command "/usr/local/Cellar/cmake/3.12.4/bin/cmake;-GUnix Makefiles;/Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-configure-out.log"
  ERROR_FILE "/Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-configure-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-configure-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "googletest configure command succeeded.  See also /Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-configure-*.log")
  message(STATUS "${msg}")
endif()
