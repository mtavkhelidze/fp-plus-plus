function(update_submodules)
    message(STATUS "Updating submodules")
    execute_process(
        COMMAND git submodule update --remote --merge
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_QUIET
        RESULT_VARIABLE res
    )
    if(res)
        message(FATAL_ERROR "Failed to update submodules")
    endif()
endfunction(update_submodules)

function(bootstrap_vcpkg)
    message(STATUS "Bootstrapping vcpkg")
    execute_process(
        COMMAND ./bootstrap-vcpkg.sh -disableMetrics
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg
        OUTPUT_QUIET
        RESULT_VARIABLE res
    )
    if(res)
        message(FATAL_ERROR "Failed to bootstrap vcpkg")
    endif()
    set(VCPKG_ROOT
        ${CMAKE_SOURCE_DIR}/vcpkg
        PARENT_SCOPE
    )
    set(CMAKE_TOOLCHAIN_FILE
        ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        PARENT_SCOPE
    )
endfunction(bootstrap_vcpkg)
