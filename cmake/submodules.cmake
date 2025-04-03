function(update_submodules)
    message(STATUS "Updating submodules")
    execute_process(
        COMMAND git submodule update --remote --merge
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_FILE /dev/null
        RESULT_VARIABLE res
    )
    if(res)
        message(FATAL_ERROR "Failed to update submodules")
    endif()
    message(STATUS "Updating submodules - done")
endfunction(update_submodules)
