//
// Created by mateo on 05.12.19.
//

#include <fstream>
#include <exception>
#include "Game.h"
#include "Entities/PlayerShip.h"
#include "Views/PlayerShipView.h"
#include "Controllers/PlayerShipController.h"
#include "Views/BulletView.h"
#include "Stopwatch.h"
#include "Entities/EnemyShip.h"
#include "Views/EnemyShipView.h"
#include "Controllers/EnemyShipController.h"
#include "json.hpp"

/*
 * RANDOM INT GENERATOR BETWEEN TWO VALUES, SOURCE:
 * https://stackoverflow.com/questions/11758809/what-is-the-optimal-algorithm-for-generating-an-unbiased-random-integer-within-a?answertab=votes#tab-top
 */
int randomInt (int min, int max){
    int n = max - min + 1;
    int remainder = RAND_MAX % n;
    int x;
    do{
        x = rand();
    } while (x >= RAND_MAX - remainder);
    return min + x % n;
}

Game::Game() {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1200, 900), "Space Invaders", sf::Style::Close);
    Transformation::instance().setWindow(window);
}

void Game::startGame() {
    // read from json file
    std::string level = "Level" + std::to_string(currentLevel) + ".json";
    std::ifstream file(level);
    nlohmann::json j;
    file >> j;

    if (currentLevel == 0) {
        // create window background
        try {
            if (!bgTexture.loadFromFile("./resources/background.png")) {
                throw std::runtime_error ("Couldn't find background image, "
                                          "please include an image with filename background.png"
                                          "in the resources folder");
            }

        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        background.setTexture(bgTexture);
        // scale bgTexture to correct window size
        float bgScale_x = window->getSize().x/(float)bgTexture.getSize().x;
        float bgScale_y = window->getSize().y/(float)bgTexture.getSize().y;
        background.setScale(bgScale_x, bgScale_y);

        // initialize game over screen
        try {
            if (!goTexture.loadFromFile("./resources/gameOver.png")) {
                throw std::runtime_error ("Couldn't find game over image, "
                                          "please include an image with filename gameOver.png"
                                          "in the resources folder");
            }
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        gameOver.setTexture(goTexture);
        // scale bgTexture to correct window size
        float goScale_x = window->getSize().x/(float)goTexture.getSize().x;
        float goScale_y = window->getSize().y/(float)goTexture.getSize().y;
        gameOver.setScale(goScale_x, goScale_y);

        // initialize win screen
        try {
            if (!wsTexture.loadFromFile("./resources/winScreen.png")) {
                throw std::runtime_error ("Couldn't find game over image, "
                                          "please include an image with filename gameOver.png"
                                          "in the resources folder");
            }
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        winScreen.setTexture(wsTexture);
        // scale bgTexture to correct window size
        float wsScale_x = window->getSize().x/(float)wsTexture.getSize().x;
        float wsScale_y = window->getSize().y/(float)wsTexture.getSize().y;
        winScreen.setScale(wsScale_x, wsScale_y);

        // create font
        try {
            if (!comicSans.loadFromFile("./resources/COMIC.TTF")) {
                throw std::runtime_error ("Couldn't find font, "
                                          "please include a font file with filename COMIC.TTF"
                                          "in the resources folder");
            }
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }

        // create playership
        std::string stringPlayerX = j["player"]["x"];
        std::string stringPlayerY = j["player"]["y"];
        float playerX = std::stof(stringPlayerX);
        float playerY = std::stof(stringPlayerY);
        std::shared_ptr<Entities::Entity> ship = std::make_shared<Entities::PlayerShip>(playerX, playerY);
        std::shared_ptr<Views::View> shipView = std::make_shared<Views::PlayerShipView>(ship, "./resources/playerShip.png");
        player = std::make_shared<Controllers::PlayerShipController>(ship);
        shipView->makeThisObserver(ship);
        views.push_back(shipView);
        controllers.push_back(player);

        playerLives.setFont(comicSans);
        playerLives.setCharacterSize(50);
    }

    // set time between two enemies shooting
    std::string shootPeriod = j["enemyShootPeriod"];
    enemyShootPeriod = std::stoi(shootPeriod);
    counter = 0;

    // create enemies
    for (int i = 0; i < j["enemies"].size(); ++i) {
        std::string strX = j["enemies"][i]["x"];
        std::string strY = j["enemies"][i]["y"];
        float enemyX = std::stof(strX);
        float enemyY = std::stof(strY);
        std::shared_ptr<Entities::Entity> enemy = std::make_shared<Entities::EnemyShip>(enemyX, enemyY);
        std::shared_ptr<Views::View> enemyView = std::make_shared<Views::EnemyShipView>(enemy, "./resources/enemyShip.png");
        enemyView->makeThisObserver(enemy);
        views.push_back(enemyView);
        std::shared_ptr<Controllers::EnemyShipController> enemyController = std::make_shared<Controllers::EnemyShipController>(enemy);

        // make sure enemies are sorted in vector
        if (enemyShips.empty()) enemyShips.push_back(enemyController);
        else {
            bool inserted = false;
            int k = 0;
            while (k != enemyShips.size()) {
                // sort on x
                if (enemyX < enemyShips[k]->getCoords().first
                && enemyShips[k]->getCoords().second == enemyY) {
                    enemyShips.insert(enemyShips.begin()+k, enemyController);
                    inserted = true;
                    k = (int) enemyShips.size()-1;
                }
                k++;
            }
            // if nothing was inserted this means it needs to be placed at the end
            if (!inserted) {
                enemyShips.push_back(enemyController);
            }
        }
    }
}

void Game::runGame() {

    //Create entities
    startGame();

    sf::Music gameMusic;
    try {
        if (!gameMusic.openFromFile("./resources/gameMusic.ogg")) {
            throw std::runtime_error ("Couldn't find file with name gameMusic.ogg, please include this file"
                                      "in the resources folder");
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    sf::Music gameOverMusic;
    try {
        if (!gameOverMusic.openFromFile("./resources/gameOverSound.ogg")) {
            throw std::runtime_error ("Couldn't find file with name gameOverMusic.ogg, please include this file"
                                      "in the resources folder");
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    sf::Music gameWinMusic;
    try {
        if (!gameWinMusic.openFromFile("./resources/winMusic.ogg")) {
            throw std::runtime_error ("Couldn't find file with name winMusic.ogg, please include this file"
                                      "in the resources folder");
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    gameMusic.play();

    Stopwatch::instance().previous = std::chrono::system_clock::now();
    double lag = 0.0;

    double MS_PER_UPDATE = 16; // value for 60 FPS

    //Game loop
    while (window->isOpen())
    {
        Stopwatch::instance().current = std::chrono::system_clock::now();
        Stopwatch::instance().elapsed =
                std::chrono::duration_cast<std::chrono::milliseconds>(Stopwatch::instance().current - Stopwatch::instance().previous).count();
        Stopwatch::instance().previous = Stopwatch::instance().current;
        lag += Stopwatch::instance().elapsed;

        /*
         * INPUT BLOCK
         */

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};
        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed
            or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window->close();

        }

        // loop if enemies are defeated
        if (enemyShips.empty()) {
            if (currentLevel < levelCount-1) {
                currentLevel++;
                startGame();
            }
            // if the last level is beaten
            else {
                gameWin = true;
            }
        }


        while (lag >= MS_PER_UPDATE) {
            // check for keyboard input real-time
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                // left key is pressed: move our character with PlayerShipController
                player->move('Q');
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                // right key is pressed: move our character with PlayerShipController
                player->move('D');
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                // space key is pressed: shoot a bullet from our character with PlayerShipController
                // if there is no bullet on the playfield yet
                if (!player->shotBullet()) {
                    // we want to initialise bullet above the player location
                    std::shared_ptr<Entities::Entity> bullet = std::make_shared<Entities::Bullet>(player->getCoords().first,
                                                                              player->getCoords().second + player->getEntityHeight()/2);

                    // make bullet view and make it observer of the bullet we created
                    std::shared_ptr<Views::View> bulletView = std::make_shared<Views::BulletView>(bullet, "./resources/bullet.png");
                    bulletView->makeThisObserver(bullet);

                    // make a controller for the bullet we just created
                    std::shared_ptr<Controllers::Controller> bulletController = std::make_shared<Controllers::BulletController>(bullet);
                    views.push_back(bulletView);
                    controllers.push_back(bulletController);

                    // let playerShip have access to bulletController
                    std::shared_ptr<Controllers::BulletController> playerBulletController =
                            std::dynamic_pointer_cast<Controllers::BulletController>(bulletController);
                    player->setBullet(playerBulletController);
                    // playerShipController now uses update function so it needs to be in list of controllers


                    for (const std::shared_ptr<Controllers::EnemyShipController> &enemy: enemyShips) {
                        enemy->setPlayerBullet(playerBulletController);
                    }
                }
            }

            /*
            * UPDATE BLOCK
            */

            // let controllers update their entities (e.g. Bullets)
            std::vector<std::shared_ptr<Controllers::Controller>> newControllers;
            for (const std::shared_ptr<Controllers::Controller> &controller: controllers) {
                // if bullet flies out of the window we want to delete it so we also want to delete the controller
                // out of the vector of controllers
                if (controller->getEntity() != nullptr) {
                    controller->update();
                    newControllers.push_back(controller);
                }
            }
            controllers = newControllers;

            // now update enemies seperately as we want all enemies to be moving in sync
            std::vector<std::shared_ptr<Controllers::EnemyShipController>> newEnemies;
            bool noEnemies = enemyShips.empty();
            if (!noEnemies && enemyShips[0]->getEntity() == nullptr) {
                enemyShips.erase(enemyShips.begin());
            }
            noEnemies = enemyShips.empty();
            if (!noEnemies && enemyShips[enemyShips.size()-1]->getEntity() == nullptr) {
                enemyShips.pop_back();
            }
            noEnemies = enemyShips.empty();

            // find index of leftmost and rightmost enemy
            int leftmost = 0;
            int rightmost = (int) enemyShips.size()-1;

            for (int j = 0; j < enemyShips.size(); ++j) {
                if (enemyShips[j]->getEntity() != nullptr &&
                enemyShips[j]->getCoords().first < enemyShips[leftmost]->getCoords().first) leftmost = j;
                if (enemyShips[j]->getEntity() != nullptr &&
                enemyShips[j]->getCoords().first > enemyShips[rightmost]->getCoords().first) rightmost = j;
            }

            // if we are moving left we check if the leftmost enemy changes direction on update
            if (!noEnemies && enemyShips[leftmost]->movingLeft()) {
                enemyShips[leftmost]->update();
                // if direction changes, move all other enemies down and change direction in every enemy
                if (enemyShips[leftmost]->getEntity() != nullptr
                    && !enemyShips[leftmost]->movingLeft()) {
                    for (int i = 0; i < enemyShips.size(); ++i) {
                        if (enemyShips[i]->getEntity() != nullptr && i != leftmost) {
                            enemyShips[i]->moveDown();
                            enemyShips[i]->setMovingLeft(false);
                            newEnemies.push_back(enemyShips[i]);
                        } else if (i == leftmost) newEnemies.push_back(enemyShips[leftmost]);
                    }
                }
                    // if direction is the same, use update function for other ships
                else {
                    for (int i = 0; i < enemyShips.size(); ++i) {
                        if (enemyShips[i]->getEntity() != nullptr && i != leftmost) {
                            enemyShips[i]->update();
                            newEnemies.push_back(enemyShips[i]);
                        } else if (i == leftmost) newEnemies.push_back(enemyShips[leftmost]);
                    }
                }
            }
                // if we are moving right we check if the rightmost enemy changes direction on update
            else if (!noEnemies && !enemyShips[rightmost]->movingLeft()) {
                enemyShips[rightmost]->update();
                // if direction changes, move all other enemies down and change direction in every enemy
                if (enemyShips[rightmost]->getEntity() != nullptr
                    && enemyShips[rightmost]->movingLeft()) {
                    for (int i = 0; i < enemyShips.size(); ++i) {
                        if (enemyShips[i]->getEntity() != nullptr && i != rightmost) {
                            enemyShips[i]->moveDown();
                            enemyShips[i]->setMovingLeft(true);
                            newEnemies.push_back(enemyShips[i]);
                        } else if (i == rightmost) newEnemies.push_back(enemyShips[rightmost]);
                    }
                }
                    // if direction is the same, use update function for other ships
                else {
                    for (int i = 0; i < enemyShips.size(); ++i) {
                        if (enemyShips[i]->getEntity() != nullptr && i != rightmost) {
                            enemyShips[i]->update();
                            newEnemies.push_back(enemyShips[i]);
                        } else if (i == rightmost) newEnemies.push_back(enemyShips[rightmost]);
                    }
                }
            }
            enemyShips = newEnemies;

            // we keep a counter for letting enemies shoot bullets
            if (counter == enemyShootPeriod && !enemyShips.empty()) {

                // filter out killed enemies
                for (int i = 0; i < enemyShips.size(); ++i) {
                    if (enemyShips[i]->getEntity() == nullptr) enemyShips.erase(enemyShips.begin() + i);
                }

                // select random enemy in vector

                int toShoot = randomInt(0, (int) enemyShips.size()-1);
                std::shared_ptr<Controllers::EnemyShipController> enemyShooter = enemyShips[toShoot];

                // initialise enemy bullet, tell player there is a new enemyBullet on screen
                // and add enemy bullet to controllers
                // we want to initialise bullet beneath the enemy location
                std::shared_ptr<Entities::Entity> bullet = std::make_shared<Entities::Bullet>(enemyShooter->getCoords().first,
                                                                          enemyShooter->getCoords().second - enemyShooter->getEntityHeight()/2);

                // make bullet view and make it observer of the bullet we created
                std::shared_ptr<Views::View> bulletView = std::make_shared<Views::BulletView>(bullet, "./resources/enemyBullet.png");
                bulletView->makeThisObserver(bullet);

                // make a controller for the bullet we just created
                std::shared_ptr<Controllers::BulletController> bulletController = std::make_shared<Controllers::BulletController>(bullet);
                bulletController->makeEnemyBullet();
                views.push_back(bulletView);
                controllers.push_back(bulletController);

                player->addEnemyBullet(bulletController);

                counter = 0;
            } else counter++;

            // if the game is game over we want to handle the fade in transparency in this loop as well,
            // so the fade in happens at the same speed on every pc
            if (!player->alive() && !gameWin) {
                // changing transparency of game over screen for fade in
                if (transparency < 255) {
                    transparency += 1;
                    sf::Color gameOverColor = gameOver.getColor();
                    gameOverColor.a = (sf::Uint8) transparency;
                    gameOver.setColor(gameOverColor);
                }
            } else if (gameWin) {
                // changing transparency of win screen for fade in
                if (transparency < 255) {
                    transparency += 1;
                    sf::Color winColor = winScreen.getColor();
                    winColor.a = (sf::Uint8) transparency;
                    winScreen.setColor(winColor);
                }
            }

            lag -= MS_PER_UPDATE;
        }


        /*
         * RENDER BLOCK
         */

        // clear the window with black color
        window->clear(sf::Color::Black);

        // after updating everyone check if player is still alive
        if (player->alive() && !gameWin) {

            // draw everything here...
            window->draw(background);

            // check how many lives player has left
            std::string livesLeft = "Lives: " + std::to_string(player->getLives());
            playerLives.setString(livesLeft);
            window->draw(playerLives);

            std::vector<std::shared_ptr<Views::View>> newViews;
            for (const std::shared_ptr<Views::View> &view: views) {
                if (!view->isDeleted()) {
                    window->draw(view->getSprite());
                    newViews.push_back(view);
                }
            }
            views = newViews;
        } else if (!player->alive() && !gameWin) {
            // stop game music
            gameMusic.stop();

            // if this is the first instance of the loop that the game is over,
            // start the game over music
            if (!gameOverBool) gameOverMusic.play();
            gameOverBool = true;
            window->draw(gameOver);
        } else if (player->alive() && gameWin) {
            gameMusic.stop();

            if (!winMusicPlaying) gameWinMusic.play();
            winMusicPlaying = true;
            window->clear(sf::Color::Black);
            window->draw(winScreen);
        }

        // check if enemies collide with player, if so player dies
        for (const std::shared_ptr<Controllers::EnemyShipController> &enemyShip: enemyShips) {
            if (enemyShip->getEntity() != nullptr && enemyShip->getEntity()->collision(player->getEntity()))
                player->kill();
        }

        // end the current frame
        window->display();
    }
}