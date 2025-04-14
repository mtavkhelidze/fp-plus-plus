vcpkg_install(gtest)
vcpkg_install(rapidcheck)

find_package(GTest CONFIG REQUIRED)
find_package(rapidcheck CONFIG REQUIRED)
target_compile_options(rapidcheck INTERFACE -Wno-deprecated-declarations)

set(TEST_LIB fp++ GTest::gtest GTest::gtest_main GTest::gmock rapidcheck_gtest)
set(TEST_SRC
    src/box/box_construction.cpp
    src/box/box_get.cpp
    src/guards.cpp
    src/syntax.cpp
    src/traits/eq.cpp
    src/traits/monoid.cpp
    src/traits/semigroup.cpp
)

# find_untracked_files("${TEST_SRC}" src "*.cpp")

add_executable(${PROJECT_NAME}_test ${TEST_SRC})
target_include_directories(${PROJECT_NAME}_test PRIVATE include)

target_compile_definitions(${PROJECT_NAME}_test PRIVATE __FP_PP_TESTING)
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${TEST_LIB})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME}_test)
