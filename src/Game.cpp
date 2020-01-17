//
// Created by mateo on 05.12.19.
//

#include <fstream>
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
        bgTexture.loadFromFile("background.png");
        background.setTexture(bgTexture);
        // scale bgTexture to correct window size
        float bgScale_x = window->getSize().x/(float)bgTexture.getSize().x;
        float bgScale_y = window->getSize().y/(float)bgTexture.getSize().y;
        background.setScale(bgScale_x, bgScale_y);

        // create window background
        goTexture.loadFromFile("gameOver.png");
        gameOver.setTexture(goTexture);
        // scale bgTexture to correct window size
        float goScale_x = window->getSize().x/(float)goTexture.getSize().x;
        float goScale_y = window->getSize().y/(float)goTexture.getSize().y;
        gameOver.setScale(goScale_x, goScale_y);

        // create font
        comicSans.loadFromFile("COMIC.TTF");

        // create playership
        std::string stringPlayerX = j["player"]["x"];
        std::string stringPlayerY = j["player"]["y"];
        double playerX = std::stod(stringPlayerX);
        double playerY = std::stod(stringPlayerY);
        std::shared_ptr<Entity> ship = std::make_shared<PlayerShip>(playerX, playerY);
        std::shared_ptr<View> shipView = std::make_shared<PlayerShipView>(ship, "playerShip.png");
        player = std::make_shared<PlayerShipController>(ship);
        shipView->makeThisObserver(ship);
        views.push_back(shipView);
        controllers.push_back(player);

        playerLives.setFont(comicSans);
        playerLives.setCharacterSize(50);
    }

    // create enemies
    for (int i = 0; i < j["enemies"].size(); ++i) {
        std::string strX = j["enemies"][i]["x"];
        std::string strY = j["enemies"][i]["y"];
        double enemyX = std::stod(strX);
        double enemyY = std::stod(strY);
        std::shared_ptr<Entity> enemy = std::make_shared<EnemyShip>(enemyX, enemyY);
        std::shared_ptr<View> enemyView = std::make_shared<EnemyShipView>(enemy, "enemyShip.png");
        enemyView->makeThisObserver(enemy);
        views.push_back(enemyView);
        std::shared_ptr<EnemyShipController> enemyController = std::make_shared<EnemyShipController>(enemy);

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
                    k = enemyShips.size()-1;
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
    gameMusic.openFromFile("megalovania.ogg");

    sf::Music gameOverMusic;
    gameOverMusic.openFromFile("gameOverSound.ogg");

    gameMusic.play();

    int counter = 0;

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
        sf::Event event;
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
                // TODO: create win screen
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
                    std::shared_ptr<Entity> bullet = std::make_shared<Bullet>(player->getCoords().first,
                                                                              player->getCoords().second + player->getEntityHeight()/2);

                    // make bullet view and make it observer of the bullet we created
                    std::shared_ptr<View> bulletView = std::make_shared<BulletView>(bullet, "bullet.png");
                    bulletView->makeThisObserver(bullet);

                    // make a controller for the bullet we just created
                    std::shared_ptr<Controller> bulletController = std::make_shared<BulletController>(bullet);
                    views.push_back(bulletView);
                    controllers.push_back(bulletController);

                    // let playerShip have access to bulletController
                    std::shared_ptr<BulletController> playerBulletController =
                            std::dynamic_pointer_cast<BulletController>(bulletController);
                    player->setBullet(playerBulletController);
                    // playerShipController now uses update function so it needs to be in list of controllers


                    for (std::shared_ptr<EnemyShipController> enemy: enemyShips) {
                        enemy->setPlayerBullet(playerBulletController);
                    }
                }
            }

            /*
            * UPDATE BLOCK
            */

            // let controllers update their entities (e.g. Bullets)
            std::vector<std::shared_ptr<Controller>> newControllers;
            for (std::shared_ptr<Controller> controller: controllers) {
                // if bullet flies out of the window we want to delete it so we also want to delete the controller
                // out of the vector of controllers
                if (controller->getEntity() != nullptr) {
                    controller->update();
                    newControllers.push_back(controller);
                }
            }
            controllers = newControllers;

            // now update enemies seperately as we want all enemies to be moving in sync
            std::vector<std::shared_ptr<EnemyShipController>> newEnemies;
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
            int rightmost = enemyShips.size()-1;

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
                int toShoot = randomInt(0, enemyShips.size()-1);
                std::shared_ptr<EnemyShipController> enemyShooter = enemyShips[toShoot];

                // initialise enemy bullet, tell player there is a new enemyBullet on screen
                // and add enemy bullet to controllers
                // we want to initialise bullet beneath the enemy location
                std::shared_ptr<Entity> bullet = std::make_shared<Bullet>(enemyShooter->getCoords().first,
                                                                          enemyShooter->getCoords().second - enemyShooter->getEntityHeight()/2);

                // make bullet view and make it observer of the bullet we created
                std::shared_ptr<View> bulletView = std::make_shared<BulletView>(bullet, "bullet.png");
                bulletView->makeThisObserver(bullet);

                // make a controller for the bullet we just created
                std::shared_ptr<BulletController> bulletController = std::make_shared<BulletController>(bullet);
                bulletController->makeEnemyBullet();
                views.push_back(bulletView);
                controllers.push_back(bulletController);

                player->addEnemyBullet(bulletController);

                counter = 0;
            } else counter++;

            // if the game is game over we want to handle the fade in transparency in this loop as well,
            // so the fade in happens at the same speed on every pc
            if (!player->alive() && !gameWin) {
                // changing transparency of game over window for fade in
                if (transparency < 255) {
                    transparency += 1;
                    sf::Color gameOverColor = gameOver.getColor();
                    gameOverColor.a = (int) transparency;
                    gameOver.setColor(gameOverColor);
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

            std::vector<std::shared_ptr<View>> newViews;
            for (std::shared_ptr<View> view: views) {
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
            sf::Text winText;
            winText.setFont(comicSans);
            winText.setString("Congratulations! You won!");
            winText.setCharacterSize(50);
            window->draw(winText);
        }

        // check if enemies collide with player, if so player dies
        for (std::shared_ptr<EnemyShipController> enemyShip: enemyShips) {
            if (enemyShip->getEntity() != nullptr && enemyShip->getEntity()->collision(player->getEntity()))
                player->kill();
        }

        // end the current frame
        window->display();
    }
}