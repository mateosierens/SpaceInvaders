//
// Created by mateo on 05.12.19.
//

#include "Game.h"

Game::Game() {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Space Invaders", sf::Style::Close);

    // TEST: CREATING SPRITE WITH TEXTURE
    sf::Texture texture;
    texture.loadFromFile("playerShip.png");
    sf::Sprite player;
    player.setTexture(texture);
    player.setPosition(sf::Vector2f(0.f, 0.f)); // absolute position

    while (window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window->close();
        }

        // clear the window with black color
        window->clear(sf::Color::White);

        // draw everything here...
        window->draw(player);

        // end the current frame
        window->display();
    }
}
