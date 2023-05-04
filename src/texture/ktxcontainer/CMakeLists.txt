add_library(ktxcontainer OBJECT ktxcontainer.cpp)

target_include_directories(ktxcontainer PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(ktxcontainer PRIVATE KTX::ktx KTX::astcenc-avx2-static)
