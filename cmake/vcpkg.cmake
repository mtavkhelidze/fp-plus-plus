function(vcpkg_install package)
    message(STATUS "vcpkg nstalling ${package}")
    execute_process(
        COMMAND ./vcpkg install ${package}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg
        OUTPUT_FILE /dev/null
        RESULT_VARIABLE res
    )
    message(STATUS "vcpkg installing ${package} - done")
endfunction(vcpkg_install)

function(enable_vcpkg)
    message(STATUS "Bootstrapping vcpkg")
    set(VCPKG_MANIFEST_INSTALL OFF)
    execute_process(
        COMMAND ./bootstrap-vcpkg.sh -disableMetrics
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg
        OUTPUT_FILE /dev/null
        RESULT_VARIABLE res
    )
    if(res)
        message(FATAL_ERROR "Failed to bootstrap vcpkg")
    endif()

    set(VCPKG_ROOT
        "${CMAKE_SOURCE_DIR}/vcpkg"
        CACHE STRING "Path to vcpkg"
    )
    set(ENV{VCPKG_ROOT} "${VCPKG_ROOT}")
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE FILEPATH "Path to vcpkg toolchain file"
    )

    message(STATUS "Bootstrapping vcpkg - done")
endfunction(enable_vcpkg)
