cmake_minimum_required(VERSION 3.20)
project(FlappyBinChicken C)
set(CMAKE_C_STANDARD 99)

# Adding code completion for clangd.
if(EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
	message(STATUS "Creating symbolic link between compile_commands.json in build directory to root directory...")
	file(CREATE_LINK
		"${CMAKE_BINARY_DIR}/compile_commands.json"
		"${CMAKE_SOURCE_DIR}/compile_commands.json"
		SYMBOLIC
	)
endif()

# Adding raylib.
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
	raylib
	GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
	GIT_TAG "5.0" # Specifies which release to download.
	GIT_PROGRESS TRUE # Shows download progress.
)

# Making sure raylib is only added if it hasn't been populated before.
FetchContent_GetProperties(raylib)
if (NOT raylib_POPULATED)
	FetchContent_Populate(raylib)
	add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BIN_DIR})
endif()

# Adding our source files.
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.c")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/include")

# Declaring our executable.
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

FetchContent_MakeAvailable(raylib)
