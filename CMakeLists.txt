cmake_minimum_required(VERSION 3.11)

project(bomberman)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules")

find_package(Irrlicht REQUIRED)

if (MSVC)
	add_compile_options(/W4)
#else()
#	add_compile_options(-W)
endif()

include_directories(include
        ${Irrlicht_INCLUDE_DIRS}
)
file(GLOB_RECURSE SRC src/*.cpp)

add_executable(bomberman ${SRC})

target_link_libraries(bomberman ${Irrlicht_LIBRARIES})
if (UNIX)
	target_link_libraries(bomberman sfml-audio)
endif()

set_target_properties(
	bomberman PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}
)

if (MSVC)
	add_custom_command(TARGET bomberman POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/modules/Irrlicht.dll ${PROJECT_SOURCE_DIR}
	)
endif()