

set(command "${make}")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "/Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-build-out.log"
  ERROR_FILE "/Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-build-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  /Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-build-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "googletest build command succeeded.  See also /Users/Pablo/git/ATCSim/build_MacOS/googletest-prefix/src/googletest-stamp/googletest-build-*.log")
  message(STATUS "${msg}")
endif()
