set(target ${OQS_LIB})

FILE(GLOB hdrs "*.h")
FILE(GLOB hdrs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})

if(MKL_FOUND)
	include_directories("${MKL_INCLUDE_DIRS}")
	target_link_libraries(${target} ${MKL_SEQUENTIAL_LAYER_LIBRARY})
endif()