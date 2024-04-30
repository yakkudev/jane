cmake_minimum_required(VERSION 3.16)
project(jane LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")
add_executable(jane ${SOURCE_FILES})
target_include_directories(jane PRIVATE src)
target_link_libraries(jane PRIVATE sfml-graphics)
target_compile_features(jane PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET jane
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:jane>
        VERBATIM)
endif()

add_custom_command(
    TARGET jane
    COMMENT "Copy Assets"
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:jane>/assets
    VERBATIM)

install(TARGETS jane)
