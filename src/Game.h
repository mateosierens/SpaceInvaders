//
// Created by mateo on 05.12.19.
//

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

#include "Views/View.h"
#include "Controllers/Controller.h"
#include "Controllers/PlayerShipController.h"

class Game {
private:
    std::shared_ptr<PlayerShipController> player;
    std::shared_ptr<sf::RenderWindow> window;
    std::vector<std::shared_ptr<View>> views;
    std::vector<std::shared_ptr<Controller>> controllers;

public:
    Game();

    // initializes all entities
    // TODO: read from file
    void startGame();

    // runs the game, holds game loop
    void runGame();

};


#endif //SPACEINVADERS_GAME_H
