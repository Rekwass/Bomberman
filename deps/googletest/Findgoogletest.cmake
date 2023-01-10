CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

if (NOT googletest_FOUND)
  INCLUDE(FetchContent)

  FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

endif()