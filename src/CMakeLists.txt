include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

#Accessories
add_library(accessories Accessories.h Accessories.cpp)
target_compile_options(accessories PUBLIC  -Wall -Wextra -Wpedantic )

# Behaviour
add_library(behaviour Behaviour.h Behaviour.cpp)
target_link_libraries(behaviour PRIVATE random_selection)
target_link_libraries(behaviour PRIVATE vector)
target_compile_options(behaviour PUBLIC  -Wall -Wextra -Wpedantic )

#Sensors
add_library(sensors Sensors.h Sensors.cpp)
target_compile_options(sensors PUBLIC  -Wall -Wextra -Wpedantic )

#Creature
add_library(creature Creature.h Creature.cpp)
target_link_libraries(creature PRIVATE accessories)
target_link_libraries(creature PRIVATE sensors)
target_link_libraries(creature PRIVATE behaviour)
target_link_libraries(creature PRIVATE hitbox)
target_link_libraries(creature PRIVATE milieu)
target_compile_options(creature PUBLIC  -Wall -Wextra -Wpedantic )

# Creature Builder
add_library(creature_builder CreatureBuilder.h CreatureBuilder.cpp)
target_link_libraries(creature_builder PRIVATE creature)
target_link_libraries(creature_builder PRIVATE random_creatures)
target_include_directories(creature_builder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
target_compile_options(creature PUBLIC  -Wall -Wextra -Wpedantic )

#Milieu
add_library(milieu Milieu.h Milieu.cpp)
target_link_libraries(milieu PRIVATE creature_builder)
target_compile_options(milieu PUBLIC  -Wall -Wextra -Wpedantic )

#Aquarium
add_library(aquarium Aquarium.h Aquarium.cpp)
target_link_libraries(aquarium PRIVATE milieu)
target_include_directories(aquarium PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
target_compile_options(aquarium PUBLIC  -Wall -Wextra -Wpedantic )

# main
add_executable(main main.cpp)
target_link_libraries(main accessories behaviour sensors creature milieu aquarium)
target_compile_options(main PUBLIC  -Wall -Wextra -Wpedantic )

find_package(Threads REQUIRED)
target_link_libraries(main X11)
target_link_libraries(main Threads::Threads)


# Compile options






