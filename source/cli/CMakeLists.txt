include_directories(${CMAKE_SOURCE_DIR}/deps/include)
if (WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/deps/lib)
else ()
    link_directories(${CMAKE_SOURCE_DIR}/deps/bin)
endif ()

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CONFIGURATION_TYPES "Release")

add_executable(MAALimbus_CLI main.cpp)
target_link_libraries(MAALimbus_CLI PRIVATE MaaFramework MaaToolKit)

add_dependencies(MAALimbus_CLI AssetsResource)

install(TARGETS MAALimbus_CLI RUNTIME DESTINATION .)
