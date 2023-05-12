add_executable(shadertest "${GL_MAIN_PATH}" shaderobjecttest.cpp shadertest.cpp)

target_compile_definitions(shadertest PUBLIC WRONG_VERT_SHADER="vertexshaderwrong.txt")
target_compile_definitions(shadertest PUBLIC CORRECT_VERT_SHADER="vertshader1.txt")
target_compile_definitions(shadertest PUBLIC CORRECT_FRAG_SHADER="fragshader1.txt")
target_compile_definitions(shadertest PUBLIC LINK_TEST_VERT_SHADER="shadervertuniforms.txt")
target_compile_definitions(shadertest PUBLIC LINK_TEST_FRAG_SHADER="shaderfraguniform.txt")

target_link_libraries(shadertest PRIVATE glhelperfunctions)
target_link_libraries(shadertest PRIVATE Catch2::Catch2)
target_link_libraries(shadertest PRIVATE window)

set(TEST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shadertestdir")

add_custom_command(TARGET shadertest POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/ShaderTestFiles" "${TEST_DIR}")
                   
catch_discover_tests(shadertest WORKING_DIRECTORY "${TEST_DIR}")

