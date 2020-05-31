cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

include(FetchContent)
project(ProjetCPP VERSION 1.0.0 LANGUAGES CXX)

set (BUILD_SHARED_LIBS FALSE)


FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG v1.10
)
FetchContent_MakeAvailable(pugixml)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(sfml)

FetchContent_Declare(
    box2d
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(box2d)



add_subdirectory(mainLauncher)
add_subdirectory(src)
add_subdirectory(unitTests)
