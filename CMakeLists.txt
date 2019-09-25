project (memswap)
cmake_minimum_required (VERSION 3.0)

include (cmake/cflags.cmake)

add_library (memswap STATIC memswap.c)
target_include_directories (memswap PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if (BUILD_TESTING)
	enable_testing ()
	add_executable (memswap-test test.c)
	add_test (NAME memswap COMMAND $<TARGET_FILE:memswap-test>)
endif ()
