file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(UnitTests
        ${TEST_SOURCES}
)

add_subdirectory(
        ${PROJECT_SOURCE_DIR}/src/Utilities
        ${CMAKE_BINARY_DIR}/Utilities
)


target_include_directories(UnitTests PRIVATE
        ../../External/include
        ../../src
)


target_link_libraries(UnitTests PRIVATE
        Catch2::Catch2WithMain
        glfw
        GL
)



