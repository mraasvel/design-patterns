set(LIB design)

add_library(${LIB}
	lib.cpp
)

target_include_directories(${LIB} PUBLIC ../include)
target_compile_options(${LIB} PRIVATE -Wall -Wextra -Werror)
target_compile_options(${LIB} PRIVATE -Wno-unused -Wno-unused-parameter)
