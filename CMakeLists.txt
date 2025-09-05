cmake_minimum_required(VERSION 4.0)
project(scheduler_tg)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.h src/*.cpp src/*.hpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE other)
target_include_directories(${PROJECT_NAME} PRIVATE src)

include(FetchContent)
FetchContent_Declare(
        TGBM
        GIT_REPOSITORY https://github.com/bot-motherlib/TGBM
        GIT_TAG        origin/master
)
FetchContent_MakeAvailable(TGBM)
target_link_libraries(${PROJECT_NAME} tgbmlib)

# stupid tgbm logger override
target_include_directories(tgbmlib PRIVATE src)
target_include_directories(tgbmlib PRIVATE src/log)
