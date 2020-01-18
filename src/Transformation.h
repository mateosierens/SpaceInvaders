//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_TRANSFORMATION_H
#define SPACEINVADERS_TRANSFORMATION_H

#include <memory>
#include <SFML/Graphics.hpp>

class Transformation {
private:
    std::shared_ptr<sf::RenderWindow> window;
public:
    static Transformation& instance() {
        static Transformation instance_;
        return instance_;
    }

    std::pair<float, float> transform(const float &x, const float &y) {
        float window_x = (x+4)*((float) window->getSize().x / (float) 8.0);
        float window_y = (y-3)*(-1)*((float) window->getSize().y / (float) 6.0);

        return std::make_pair(window_x, window_y);
    }

    float toGameCoordsX(float window_x) {
        return (window_x / (float) (window->getSize().x/8.0)) - 4;
    }

    float toGameCoordsY(float window_y) {
        return (window_y / (float)(-(window->getSize().y/6.0))) + 3;
    }

    void setWindow(const std::shared_ptr<sf::RenderWindow> &window) {
        Transformation::window = window;
    }

private:
    Transformation() = default;
};


#endif //SPACEINVADERS_TRANSFORMATION_H
