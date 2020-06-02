#
# For googletest
#
# Contents coming from https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project

cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        "C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/build/unitTests/googletest-src"
  BINARY_DIR        "C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/build/unitTests/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
