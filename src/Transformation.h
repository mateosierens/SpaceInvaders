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

    std::pair<double, double> transform(const double &x, const double &y) {
        double window_x = (x+4)*(window->getSize().x/8.0);
        double window_y = (y-3)*(-1)*(window->getSize().y/6.0);

        return std::make_pair(window_x, window_y);
    }

    double toGameCoordsX(double window_x) {
        return (window_x/(window->getSize().x/8.0))-4;
    }

    double toGameCoordsY(double window_y) {
        return (window_y/(-(window->getSize().y/6.0)))+3;
    }

    void setWindow(const std::shared_ptr<sf::RenderWindow> &window) {
        Transformation::window = window;
    }

private:
    Transformation() {}
};


#endif //SPACEINVADERS_TRANSFORMATION_H
