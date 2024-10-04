
ADD_EXECUTABLE(Vector
main.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Vector PRIVATE -fsanitize=address -g)
    target_link_libraries(Vector PRIVATE -fsanitize=address)
endif()