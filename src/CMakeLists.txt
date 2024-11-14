# Add the executable target
add_executable(Vector
    main.cpp)

# Add the library target (no source file needed for header-only)
add_library(Vectorlib INTERFACE   vector_test.cpp vector_v2_test.cpp vector_v3_test.cpp)

# Specify the include directory for the header file
target_include_directories(Vectorlib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Link the library to the executable
target_link_libraries(Vector PUBLIC Vectorlib)


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Vector PRIVATE -fsanitize=address -g)
    target_link_libraries(Vector PRIVATE -fsanitize=address)
endif()