cmake_minimum_required(VERSION 3.17)

project("bomberman" VERSION 0.0.1 LANGUAGES CXX)

###############################################################################
# BUILD DEPENDENCIES
###############################################################################

if (POLICY CMP0072)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()

add_subdirectory(./deps/)

###############################################################################
# BUILD PROJECT
###############################################################################

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(PROJECT_SOURCES
    src/ECS/ECSErrors.cpp
    src/ECS/Core/EntitiesManager.cpp
    src/ECS/Core/System.cpp
    src/ECS/Core/SystemsManager.cpp
    src/ECS/Core/EventsManager.cpp
    src/ECS/Core/Coordinator.cpp
    src/ECS/Components/Animation.cpp
    src/ECS/Components/RenderableText3d.cpp
    src/ECS/Components/RenderableImage2d.cpp
    src/ECS/Components/RenderableImage3d.cpp
    src/ECS/Components/RenderableRelief3d.cpp
    src/ECS/Components/RenderableCubicMap3d.cpp
    src/ECS/Components/RenderableObject3d.cpp
    src/ECS/Components/Music.cpp
    src/ECS/Systems/TransformSystem.cpp
    src/ECS/Systems/CollisionSystem.cpp
    src/ECS/Systems/CameraSystem.cpp
    src/ECS/Systems/AnimationSystem.cpp
    src/ECS/Systems/Text2dRenderSystem.cpp
    src/ECS/Systems/Text3dRenderSystem.cpp
    src/ECS/Systems/Image2dRenderSystem.cpp
    src/ECS/Systems/Image3dRenderSystem.cpp
    src/ECS/Systems/Relief3dRenderSystem.cpp
    src/ECS/Systems/CubicMap3dRenderSystem.cpp
    src/ECS/Systems/Object3dRenderSystem.cpp
    src/ECS/Systems/Relief3dBoundsSystem.cpp
    src/ECS/Systems/CubicMap3dBoundsSystem.cpp
    src/ECS/Systems/Object3dBoundsSystem.cpp
    src/ECS/Systems/MusicSystem.cpp
    src/Game/HUD.cpp
    src/Game/Room.cpp
    src/Game/PlayersManager.cpp
    src/Game/SettingsManager.cpp
    src/Game/Map/Error.cpp
    src/Game/Map/Map.cpp
    src/Game/Map/MapLoader.cpp
    src/Game/Map/MapPart.cpp
    src/Game/Map/MapReader.cpp
    src/Game/Map/Position.cpp
    src/Game/Map/Items/Bomb.cpp
    src/Game/Map/Items/Box.cpp
    src/Game/Map/Items/Fire.cpp
    src/Game/Map/Items/Ground.cpp
    src/Game/Map/Items/Wall.cpp
    src/Game/Map/Player/AIPlayer.cpp
    src/Game/Map/Player/APlayer.cpp
    src/Game/Map/Player/KeyBoardPlayer.cpp
    src/Game/Map/Player/OnlinePlayer.cpp
    src/Game/Map/PowerUp/APowerUp.cpp
    src/Game/Map/PowerUp/BombNumberPowerUp.cpp
    src/Game/Map/PowerUp/BombRangePowerUp.cpp
    src/Game/Map/PowerUp/LifePowerUp.cpp
    src/Game/Map/PowerUp/SpeedPowerUp.cpp
    src/Graphic/HitboxDisplayer.cpp
    src/Graphic/PointDisplayer.cpp
    src/Graphic/Renderer.cpp
    src/Graphic/RessourcesManager.cpp
    src/Graphic/Window.cpp
    src/Scenes/ScenesManager.cpp
    src/Scenes/MainMenuScene.cpp
    src/Scenes/ServerConnectionScene.cpp
    src/Scenes/WaitingScene.cpp
    src/Scenes/IntroScene.cpp
    src/Scenes/SettingsScene.cpp
    src/Scenes/GameScene.cpp
    src/Scenes/EndScene.cpp
    src/Scenes/TutoScene.cpp
    src/Scenes/CreditsScene.cpp
    src/Scenes/MapSelectionScene.cpp
    src/Scenes/PlayerSelectionScene.cpp
    src/Scenes/MultiPlayerSelectionScene.cpp
    src/Network/Client.cpp
    src/Network/Packers.cpp
    src/Clock.cpp
    src/Vector.cpp
    src/IndieError.cpp
    src/Redirect.cpp
    src/AudioPlayer.cpp
    src/FileReader.cpp
    src/Utils.cpp
    )

add_executable(${PROJECT_NAME}
    src/Main.cpp
    ${PROJECT_SOURCES}
    )

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    include/
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    raylib
    fmt::fmt
    nlohmann_json::nlohmann_json
)

###############################################################################
# BUILD TESTS
###############################################################################

set(TESTS_SOURCES
    tests/StartTests.cpp
    tests/CollisionsTests.cpp
    tests/ECSTests.cpp
    tests/GraphicTests.cpp
    tests/StartTests.cpp
    tests/TransformTests.cpp
    tests/UtilsTests.cpp
    tests/PlayersManagerTests.cpp
    tests/RendererTests.cpp
    tests/VectorTests.cpp
    )

add_executable(unit_tests
    ${PROJECT_SOURCES}
    ${TESTS_SOURCES}
    )

target_include_directories(
    unit_tests
    PRIVATE
    include/
)

enable_testing()

target_link_libraries(
    unit_tests
    PRIVATE
    raylib
    fmt::fmt
    nlohmann_json::nlohmann_json
    gtest
    gtest_main
)
