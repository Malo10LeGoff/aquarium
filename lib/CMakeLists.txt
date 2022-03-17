add_library(random_selection STATIC random_selection.cpp)

add_library(CImg INTERFACE)
target_include_directories(CImg INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(UImg INTERFACE)
target_link_libraries(UImg INTERFACE CImg)
target_include_directories(UImg INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


