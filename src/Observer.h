//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_OBSERVER_H
#define SPACEINVADERS_OBSERVER_H


#include <string>

class Entity;

namespace ObserverPattern {
    class Observer {
    public:
        virtual ~Observer();
        virtual void onNotify(const Entity& entity, std::string event) = 0;
    };
}



#endif //SPACEINVADERS_OBSERVER_H
