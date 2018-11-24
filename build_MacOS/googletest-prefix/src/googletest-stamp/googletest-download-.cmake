

set(command "/usr/local/Cellar/cmake/3.12.4/bin/cmake;-P;/Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/tmp/googletest-gitclone.cmake")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-download-out.log"
  ERROR_FILE "/Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-download-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-download-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "googletest download command succeeded.  See also /Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-download-*.log")
  message(STATUS "${msg}")
endif()
