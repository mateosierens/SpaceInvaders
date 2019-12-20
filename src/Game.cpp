//
// Created by mateo on 05.12.19.
//

#include "Game.h"
#include "PlayerShip.h"
#include "PlayerShipView.h"

Game::Game() {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Space Invaders", sf::Style::Close);

    // TEST: CREATING SPRITE WITH TEXTURE
//    sf::Texture texture;
//    texture.loadFromFile("playerShip.png");
//    sf::Sprite player;
//    player.setTexture(texture);
//    player.setPosition(sf::Vector2f(0.f, 0.f)); // absolute position



}

void Game::runGame() {

    //Create entities
    std::shared_ptr<Entity> ship = std::make_shared<PlayerShip>(0,0);
    std::shared_ptr<View> shipView = std::make_shared<PlayerShipView>(ship);
    std::shared_ptr<PlayerShipView> test = std::dynamic_pointer_cast<PlayerShipView>(shipView);
    test.get()->makeThisObserver(ship);
    views.push_back(shipView);

    //Game loop
    while (window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window->close();
            else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    // left key is pressed: move our character
                    std::shared_ptr<PlayerShip> player = std::dynamic_pointer_cast<PlayerShip>(ship);
                    player->moveLeft();
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    // right key is pressed: move our character
                    std::shared_ptr<PlayerShip> player = std::dynamic_pointer_cast<PlayerShip>(ship);
                    player->moveRight() ;
                }
            }
        }


        // clear the window with black color
        window->clear(sf::Color::Black);

        // draw everything here..q.
        for (std::shared_ptr<View> view: views) {
            if (PlayerShipView* pview = dynamic_cast<PlayerShipView*>(view.get())) {
                //std::cout << std::to_string(pview->getPlayerSprite().getPosition().x) << " , ";
                //std::cout << std::to_string(pview->getPlayerSprite().getPosition().y) << std::endl;
                window->draw(pview->getPlayerSprite());
            }
        }

        // end the current frame
        window->display();
    }

}
