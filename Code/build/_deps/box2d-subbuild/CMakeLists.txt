# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.16.19112601-MSVC_2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(box2d-populate NONE)

include(ExternalProject)
ExternalProject_Add(box2d-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/erincatto/box2d.git" "GIT_TAG" "origin/master"
                    SOURCE_DIR          "D:/Documents/Cours/Info/CSC4526/TutoSFML/build/_deps/box2d-src"
                    BINARY_DIR          "D:/Documents/Cours/Info/CSC4526/TutoSFML/build/_deps/box2d-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
