//
// Created by mateo on 05.12.19.
//

#include "Game.h"
#include "Entities/PlayerShip.h"
#include "Views/PlayerShipView.h"
#include "Controllers/PlayerShipController.h"
#include "Views/BulletView.h"
#include "Stopwatch.h"
#include "Entities/EnemyShip.h"
#include "Views/EnemyShipView.h"
#include "Controllers/EnemyShipController.h"


Game::Game() {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Space Invaders", sf::Style::Close);
}

void Game::startGame() {
    // create window background
    bgTexture.loadFromFile("background.png");
    background.setTexture(bgTexture);

    // create playership
    std::shared_ptr<Entity> ship = std::make_shared<PlayerShip>(0,-2);
    std::shared_ptr<View> shipView = std::make_shared<PlayerShipView>(ship, "playerShip.png");
    player = std::make_shared<PlayerShipController>(ship);
    shipView->makeThisObserver(ship);
    views.push_back(shipView);
    controllers.push_back(player);

    // TODO: create other entities
    // TEMPORARY: create an enemy to test enemy movements
    std::shared_ptr<Entity> enemy = std::make_shared<EnemyShip>(0, 2);
    std::shared_ptr<View> enemyView = std::make_shared<EnemyShipView>(enemy, "enemyShip.png");
    enemyView->makeThisObserver(enemy);
    views.push_back(enemyView);
    std::shared_ptr<EnemyShipController> enemyController = std::make_shared<EnemyShipController>(enemy);
    enemyShips.push_back(enemyController);
    controllers.push_back(enemyController);
}

void Game::runGame() {

    //Create entities
    startGame();

    sf::Music gameMusic;
    gameMusic.openFromFile("megalovania.ogg");
    gameMusic.play();

    //Game loop
    while (window->isOpen())
    {
        Stopwatch::instance().sleep(1);

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) window->close();

        }

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

        // clear the window with black color
        window->clear(sf::Color::Black);

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

        // draw everything here...
        window->draw(background);

        std::vector<std::shared_ptr<View>> newViews;
        for (std::shared_ptr<View> view: views) {
            if (!view->isDeleted()) {
                window->draw(view->getSprite());
                newViews.push_back(view);
            }
        }
        views = newViews;

        // end the current frame
        window->display();
    }

}
