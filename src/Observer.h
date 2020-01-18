//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_OBSERVER_H
#define SPACEINVADERS_OBSERVER_H


#include <string>
#include <memory>

namespace Entities {
    class Entity;
}

namespace ObserverPattern {
    class Observer : public std::enable_shared_from_this<Observer> {
    public:
        virtual ~Observer();

        virtual void onNotify(const Entities::Entity &entity, std::string event) = 0;
    };
}


#endif //SPACEINVADERS_OBSERVER_H
