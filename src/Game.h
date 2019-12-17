//
// Created by mateo on 05.12.19.
//

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

class Game {
private:
    std::shared_ptr<sf::RenderWindow> window;
public:
    Game();

};


#endif //SPACEINVADERS_GAME_H
