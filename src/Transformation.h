//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_TRANSFORMATION_H
#define SPACEINVADERS_TRANSFORMATION_H

#include <memory>

class Transformation {
public:
    static Transformation& instance() {
        static Transformation instance_;
        return instance_;
    }

    std::pair<double, double> transform(const double &x, const double &y) {
        double window_x = (x+4)*100;
        double window_y = (y-3)*(-1)*100;

        return std::make_pair(window_x, window_y);
    }

    double toGameCoordsX(double window_x) {
        return (window_x/100)-4;
    }

    double toGameCoordsY(double window_y) {
        return (window_y/(-100))+3;
    }

private:
    Transformation() {}
};


#endif //SPACEINVADERS_TRANSFORMATION_H
