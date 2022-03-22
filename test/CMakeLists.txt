include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test Behaviour Library
add_executable(behaviourTest behaviourTest.cpp)
target_link_libraries(behaviourTest gtest_main)
target_link_libraries(behaviourTest behaviour)


add_executable(detectionTest detectionTest.cpp)
target_link_libraries(detectionTest gtest_main)
target_link_libraries(detectionTest aquarium)

include(GoogleTest)
gtest_discover_tests(behaviourTest)