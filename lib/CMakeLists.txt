add_library(random_selection STATIC random_selection.cpp)
target_link_libraries(random_selection PRIVATE vector)

add_library(random_creatures STATIC random_creatures.cpp)
target_include_directories(random_creatures PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

# Vectors
add_library(vector Vector.h Vector.cpp)
target_compile_options(vector PUBLIC  -Wall -Wextra -Wpedantic )

# Hitboxes
add_library(hitbox Hitbox.h Hitbox.cpp random_creatures.cpp)
target_link_libraries(hitbox PRIVATE vector)
target_compile_options(hitbox PUBLIC  -Wall -Wextra -Wpedantic )

add_library(CImg INTERFACE)
target_include_directories(CImg INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(UImg INTERFACE)
target_link_libraries(UImg INTERFACE CImg)
target_include_directories(UImg INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


