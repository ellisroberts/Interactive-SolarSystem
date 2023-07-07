add_executable(shadertest shaderobjecttest.cpp shadertest.cpp)

target_compile_definitions(shadertest PUBLIC WRONG_VERT_SHADER="vertexshaderwrong.txt")
target_compile_definitions(shadertest PUBLIC CORRECT_VERT_SHADER="vertshader1.txt")
target_compile_definitions(shadertest PUBLIC CORRECT_FRAG_SHADER="fragshader1.txt")
target_compile_definitions(shadertest PUBLIC LINK_TEST_VERT_SHADER="shadervertuniforms.txt")
target_compile_definitions(shadertest PUBLIC LINK_TEST_FRAG_SHADER="shaderfraguniform.txt")

target_link_libraries(shadertest
                      PRIVATE glhelperfunctions
                      PRIVATE Catch2::Catch2
                      PRIVATE glmain)

set(TEST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shadertestdir")

add_custom_command(TARGET shadertest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/ShaderTestFiles" "${TEST_DIR}")
                   
catch_discover_tests(shadertest WORKING_DIRECTORY "${TEST_DIR}")

