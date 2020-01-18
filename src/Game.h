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
    // main textures and window
    sf::Sprite background;
    sf::Texture bgTexture;
    sf::Sprite gameOver;
    sf::Texture goTexture;
    std::shared_ptr<sf::RenderWindow> window;
    double transparency = 0; // fade in over game over screen
    sf::Font comicSans;
    sf::Text playerLives;
    sf::Sprite winScreen;
    sf::Texture wsTexture;

    // game objects
    std::shared_ptr<Controllers::PlayerShipController> player;
    std::vector<std::shared_ptr<Views::View>> views;
    std::vector<std::shared_ptr<Controllers::Controller>> controllers;
    std::vector<std::shared_ptr<Controllers::EnemyShipController>> enemyShips;

    // game logic
    int currentLevel = 0;
    int levelCount = 2;
    int enemyShootPeriod = 100;
    bool gameOverBool = false;
    bool gameWin = false;
    bool winMusicPlaying = false;

public:
    Game();

    // initializes all entities
    void startGame();

    // runs the game, holds game loop
    void runGame();

};


#endif //SPACEINVADERS_GAME_H
