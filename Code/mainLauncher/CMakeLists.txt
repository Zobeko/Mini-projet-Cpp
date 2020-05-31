
add_executable(mainLauncher mainLauncher.cpp)

target_link_libraries(mainLauncher PUBLIC src pugixml sfml-graphics)

add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Hero.png)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Hero.png
                   DEPENDS ${CMAKE_SOURCE_DIR}/resources/Hero.png
                   COMMAND ${CMAKE_COMMAND} -E copy
                           ${CMAKE_SOURCE_DIR}/resources/Hero.png
                           ${CMAKE_CURRENT_BINARY_DIR})
