add_executable(texturetest "${GL_MAIN_PATH}" texturecontainertest.cpp texturetest.cpp)

set(TEST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/texturetestdir")
set(TOKTX_COMMAND "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/tools/ktx/toktx")

add_custom_command(OUTPUT "${TEST_DIR}/test.ktx" "${TEST_DIR}/fail.ktx"
                   COMMAND "${CMAKE_COMMAND}" -E make_directory "${TEST_DIR}"
                   COMMAND "${TOKTX_COMMAND}" --2d --target_type "RGB" "${TEST_DIR}/test.ktx" "${CMAKE_CURRENT_SOURCE_DIR}/images/earth.jpg"
                   COMMAND "${TOKTX_COMMAND}" --2d --t2 --target_type "RGB" --encode "uastc" "${TEST_DIR}/fail.ktx" "${CMAKE_CURRENT_SOURCE_DIR}/images/earth.jpg")
add_custom_target(texturetestfiles DEPENDS "${TEST_DIR}/test.ktx" "${TEST_DIR}/fail.ktx")
add_dependencies(texturetest texturetestfiles)

target_compile_definitions(texturetest PUBLIC CONTAINER_FILE_2D="${TEST_DIR}/test.ktx")
target_compile_definitions(texturetest PUBLIC KTX_EXCEPTION_FILE="${TEST_DIR}/fail.ktx")

target_link_libraries(texturetest
                      PRIVATE ktxcontainer
                      PRIVATE gltexture
                      PRIVATE window
                      PRIVATE Catch2::Catch2)

catch_discover_tests(texturetest WORKING_DIRECTORY "${TEST_DIR}")
