CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

if (NOT fmt_FOUND)
  INCLUDE(FetchContent)

  FetchContent_Declare(fmt URL https://github.com/fmtlib/fmt/releases/download/8.1.1/fmt-8.1.1.zip)

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(fmt)

endif()