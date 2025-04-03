function(find_untracked_files src_list dir pattern)
    message(
        STATUS
            "Checking for untracked ${pattern} files in ${CMAKE_CURRENT_LIST_DIR}/${dir}"
    )

    file(GLOB_RECURSE src_found ${CMAKE_CURRENT_LIST_DIR}/${dir}/${pattern})
    list(TRANSFORM src_found REPLACE "${CMAKE_CURRENT_LIST_DIR}/" "")
    list(REMOVE_ITEM src_found ${src_list})
    if(src_found)
        string(REPLACE ";" ", " src_found "${src_found}")
        message(
            FATAL_ERROR
                "Found untracked files in ${CMAKE_CURRENT_LIST_DIR}/${dir}: ${src_found}"
        )
    endif()
    message(STATUS "Checking for untracked files - done")
endfunction(find_untracked_files)
