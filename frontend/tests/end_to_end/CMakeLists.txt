add_test(
    NAME end_to_end 
    COMMAND ${CMAKE_COMMAND} -E env VERBOSE=1 bash ${CMAKE_CURRENT_SOURCE_DIR}/check_program_termination.sh
)

set_tests_properties(end_to_end PROPERTIES 
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    LABELS "end_to_end"
)