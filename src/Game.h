//
// Created by mateo on 05.12.19.
//

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "Views/View.h"
#include "Controllers/Controller.h"
#include "Controllers/PlayerShipController.h"
#include "Controllers/EnemyShipController.h"


class Game {
private:
    sf::Sprite background;
    sf::Texture bgTexture;
    std::shared_ptr<PlayerShipController> player;
    std::shared_ptr<sf::RenderWindow> window;
    std::vector<std::shared_ptr<View>> views;
    std::vector<std::shared_ptr<Controller>> controllers;
    std::vector<std::shared_ptr<EnemyShipController>> enemyShips;

public:
    Game();

    // initializes all entities
    // TODO: read from file
    void startGame();

    // runs the game, holds game loop
    void runGame();

};


#endif //SPACEINVADERS_GAME_H
