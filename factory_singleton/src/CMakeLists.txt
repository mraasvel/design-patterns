add_executable(a.out
	main.cpp
	factory_service.cpp
	user.cpp
	database.cpp
	user_service.cpp
)

target_compile_options(a.out PRIVATE -g3 -fsanitize=address)
target_link_options(a.out PRIVATE -g3 -fsanitize=address)
