
set(ATCD_ICEFILES_DIR ${CMAKE_CURRENT_LIST_DIR}/../src/ICE/slice)
set(ATCD_OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/../src/ICE/cpp)
set(SLICE2CPP slice2cpp)

file(MAKE_DIRECTORY ${ATCD_OUTPUT_DIR})

set (ATCD_FILES
    ATCDisplay.ice
)

foreach (file ${ATCD_FILES})
 	set (atcd_file ${file})
	GET_FILENAME_COMPONENT (atcd_file_name ${atcd_file} NAME_WE)

	set(args --output-dir=${ATCD_OUTPUT_DIR} -I. -I${ATCD_ICEFILES_DIR} ${ATCD_ICEFILES_DIR}/${atcd_file})

	ADD_CUSTOM_COMMAND (
 		OUTPUT ${ATCD_OUTPUT_DIR}/${atcd_file_name}.cpp ${ATCD_OUTPUT_DIR}/${atcd_file_name}.h
  		DEPENDS ${ATCD_ICEFILES_DIR}/${atcd_file}
  		COMMAND ${SLICE2CPP} ${args}
  	)

  	execute_process(COMMAND ${SLICE2CPP} ${args})

endforeach()
