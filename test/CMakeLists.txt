vcpkg_install(gtest)
vcpkg_install(rapidcheck)

find_package(GTest CONFIG REQUIRED)
find_package(rapidcheck CONFIG REQUIRED)
target_compile_options(rapidcheck INTERFACE -Wno-deprecated-declarations)

set(TEST_LIB GTest::gtest GTest::gtest_main GTest::gmock rapidcheck_gtest)
set(TEST_SRC
    src/concepts/eq.cpp
    src/concepts/monoid.cpp
    # src/monads/option/option_get.cpp
    # src/monads/option/option_map.cpp
    src/monads/option/option_some.cpp
    # src/syntax.cpp
)

# find_untracked_files("${TEST_SRC}" src "*.cpp")

add_executable(${PROJECT_NAME}_test ${TEST_SRC})
target_include_directories(${PROJECT_NAME}_test PRIVATE include)
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${TEST_LIB})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}_test)
