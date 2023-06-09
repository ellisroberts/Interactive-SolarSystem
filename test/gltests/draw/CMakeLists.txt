add_executable(drawtest "${GL_MAIN_PATH}" drawtest.cpp)

target_link_libraries(drawtest
                      PRIVATE GLObject
                      PRIVATE Catch2::Catch2
                      PRIVATE window)

catch_discover_tests(drawtest)
