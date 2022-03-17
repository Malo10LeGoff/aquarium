include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
#Accessories
add_library(accessories Accessories.h Accessories.cpp)

# Behaviour
add_library(behaviour Behaviour.h Behaviour.cpp)
target_link_libraries(behaviour PRIVATE random_selection)

#Sensors
add_library(sensors Sensors.h Sensors.cpp)

#Creature
add_library(creature Creature.h Creature.cpp)
target_link_libraries(creature PRIVATE accessories)
target_link_libraries(creature PRIVATE sensors)
target_link_libraries(creature PRIVATE behaviour)

#Milieu
add_library(milieu Milieu.h Milieu.cpp)
target_link_libraries(milieu PRIVATE creature)

#Aquarium
add_library(aquarium Aquarium.h Aquarium.cpp)
target_link_libraries(aquarium PRIVATE milieu)

# main
add_executable(main main.cpp)
target_link_libraries(main accessories behaviour sensors creature milieu aquarium)

find_package(Threads REQUIRED)
target_link_libraries(main X11)
target_link_libraries(main Threads::Threads)