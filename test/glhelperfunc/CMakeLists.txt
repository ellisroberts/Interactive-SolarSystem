add_executable(glhelpertest glhelpertest.cpp)

target_compile_definitions(glhelpertest PUBLIC TEST_FILE="shadercodeparsetest.txt")

target_link_libraries(glhelpertest PRIVATE glhelperfunctions)
target_link_libraries(glhelpertest PRIVATE Catch2::Catch2WithMain)

set(TEST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glhelpertestdir")

add_custom_command(TARGET glhelpertest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/testcode "${TEST_DIR}")

catch_discover_tests(glhelpertest WORKING_DIRECTORY "${TEST_DIR}")
