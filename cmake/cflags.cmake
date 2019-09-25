# ~Some notes~
#
# WINDOWS:
#
#   - /EHs cannot be /EHsc because with SDL we have to extern "C" some things
#     that might actually throw some exceptions.

set(CMAKE_CXX_STANDARD 17)

if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wshadow -pedantic -std=c++0x -Wno-invalid-offsetof -fno-exceptions")
	set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O0")
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wshadow -pedantic -std=c90 -fno-exceptions")
	set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3 -O0")
	set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++0x /DWIN32_LEAN_AND_MEAN /EHs /utf-8")
	set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /Od /GS /RTCsu")
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /O2")

	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /DWIN32_LEAN_AND_MEAN /EHs /utf-8")
	set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd /Od /GS /RTCsu")
	set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT /O2")

	set (CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG:FULL")
endif ()
