CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

if (NOT nlohmann_json_FOUND)
  INCLUDE(FetchContent)

  FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(json)

endif()