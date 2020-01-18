cmake_minimum_required(VERSION 3.10.2)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 14)

add_executable(SpaceInvaders src/main.cpp src/Entities/Entity.cpp src/Entities/Entity.h src/Entities/PlayerShip.cpp src/Entities/PlayerShip.h src/Entities/EnemyShip.cpp src/Entities/EnemyShip.h src/Entities/Bullet.cpp src/Entities/Bullet.h src/Game.cpp src/Game.h src/Controllers/Controller.cpp src/Controllers/Controller.h src/Views/View.cpp src/Views/View.h src/Controllers/PlayerShipController.cpp src/Controllers/PlayerShipController.h src/Views/PlayerShipView.cpp src/Views/PlayerShipView.h src/Observer.cpp src/Observer.h src/Subject.cpp src/Subject.h src/Transformation.h src/Views/BulletView.cpp src/Views/BulletView.h src/Controllers/BulletController.cpp src/Controllers/BulletController.h src/Stopwatch.h src/Controllers/EnemyShipController.cpp src/Controllers/EnemyShipController.h src/Views/EnemyShipView.cpp src/Views/EnemyShipView.h)

target_link_libraries(SpaceInvaders "-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio")