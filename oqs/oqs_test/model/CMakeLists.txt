set(target ${OQS_TEST})

FILE(GLOB hdrs "*.h")
FILE(GLOB hdrs "*.cpp")

include_directories("${OQS_INC}")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest gmock_main ${OQS_LIB})

if(MKL_FOUND)
	include_directories("${MKL_INCLUDE_DIRS}")
	target_link_libraries(${target} ${MKL_SEQUENTIAL_LAYER_LIBRARY})
endif()

# Register the test
add_test(NAME ${target} COMMAND "${target}" --gtest_color=yes)
