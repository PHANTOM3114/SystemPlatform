# CMake generated Testfile for 
# Source directory: /Users/mykhailokhymochko/SystemPlatform/tests
# Build directory: /Users/mykhailokhymochko/SystemPlatform/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[SystemPlatformUnitTests]=] "/Users/mykhailokhymochko/SystemPlatform/build/tests/Debug/system_platform_tests")
  set_tests_properties([=[SystemPlatformUnitTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/mykhailokhymochko/SystemPlatform/tests/CMakeLists.txt;31;add_test;/Users/mykhailokhymochko/SystemPlatform/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[SystemPlatformUnitTests]=] "/Users/mykhailokhymochko/SystemPlatform/build/tests/Release/system_platform_tests")
  set_tests_properties([=[SystemPlatformUnitTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/mykhailokhymochko/SystemPlatform/tests/CMakeLists.txt;31;add_test;/Users/mykhailokhymochko/SystemPlatform/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[SystemPlatformUnitTests]=] "/Users/mykhailokhymochko/SystemPlatform/build/tests/MinSizeRel/system_platform_tests")
  set_tests_properties([=[SystemPlatformUnitTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/mykhailokhymochko/SystemPlatform/tests/CMakeLists.txt;31;add_test;/Users/mykhailokhymochko/SystemPlatform/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[SystemPlatformUnitTests]=] "/Users/mykhailokhymochko/SystemPlatform/build/tests/RelWithDebInfo/system_platform_tests")
  set_tests_properties([=[SystemPlatformUnitTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/mykhailokhymochko/SystemPlatform/tests/CMakeLists.txt;31;add_test;/Users/mykhailokhymochko/SystemPlatform/tests/CMakeLists.txt;0;")
else()
  add_test([=[SystemPlatformUnitTests]=] NOT_AVAILABLE)
endif()
