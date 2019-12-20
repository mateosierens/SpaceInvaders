//
// Created by mateo on 05.12.19.
//

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

#include "View.h"

class Game {
private:
    std::shared_ptr<sf::RenderWindow> window;
    std::vector<std::shared_ptr<View>> views;

public:
    Game();

    void runGame();

};


#endif //SPACEINVADERS_GAME_H
