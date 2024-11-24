add_executable(vector_v4_test 
vector_v4_test.cpp)

add_executable(vector_v3_test 
vector_v3_test.cpp)

add_executable(vector_v2_test 
vector_v2_test.cpp)

add_executable(vector_test 
vector_test.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fsanitize=address -g)
    add_link_options(-fsanitize=address)
endif()