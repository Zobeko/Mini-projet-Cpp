# CMake generated Testfile for 
# Source directory: C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/unitTests
# Build directory: C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/build/unitTests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(that-test-I-made "C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/build/unitTests/Debug/unitTests.exe")
  set_tests_properties(that-test-I-made PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/unitTests/CMakeLists.txt;43;add_test;C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/unitTests/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(that-test-I-made "C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/build/unitTests/Release/unitTests.exe")
  set_tests_properties(that-test-I-made PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/unitTests/CMakeLists.txt;43;add_test;C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/unitTests/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(that-test-I-made "C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/build/unitTests/MinSizeRel/unitTests.exe")
  set_tests_properties(that-test-I-made PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/unitTests/CMakeLists.txt;43;add_test;C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/unitTests/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(that-test-I-made "C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/build/unitTests/RelWithDebInfo/unitTests.exe")
  set_tests_properties(that-test-I-made PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/unitTests/CMakeLists.txt;43;add_test;C:/Users/louis/Documents/ProjetCPP/Mini-projet-Cpp/Code/unitTests/CMakeLists.txt;0;")
else()
  add_test(that-test-I-made NOT_AVAILABLE)
endif()
subdirs("googletest-build")
