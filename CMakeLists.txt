cmake_minimum_required(VERSION 3.12)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 14)

add_executable(SpaceInvaders src/main.cpp src/Entity.cpp src/Entity.h src/PlayerShip.cpp src/PlayerShip.h src/EnemyShip.cpp src/EnemyShip.h src/Bullet.cpp src/Bullet.h src/World.cpp src/World.h src/Game.cpp src/Game.h src/Controller.cpp src/Controller.h src/View.cpp src/View.h src/PlayerShipController.cpp src/PlayerShipController.h src/PlayerShipView.cpp src/PlayerShipView.h src/Observer.cpp src/Observer.h src/Subject.cpp src/Subject.h src/Transformation.cpp src/Transformation.h)

target_link_libraries(SpaceInvaders "-lsfml-graphics -lsfml-window -lsfml-system")