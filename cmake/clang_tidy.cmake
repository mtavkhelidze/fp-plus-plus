function(enable_clang_tidy)
    # Add the custom target
    add_custom_target(
        tidy
        COMMAND
            clang-tidy -p ${CMAKE_BINARY_DIR} -header-filter=.* test/src/*.cpp
            -- std=c++20 -Iinclude
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        DEPENDS fp++
        COMMENT "Running clang-tidy on src/lib and include/fp only"
    )
endfunction(enable_clang_tidy)
