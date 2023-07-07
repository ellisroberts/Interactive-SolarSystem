add_executable(drawtest drawtest.cpp)

target_link_libraries(drawtest
                      PRIVATE GLObject
                      PRIVATE Catch2::Catch2
                      PRIVATE glmain)

catch_discover_tests(drawtest)
