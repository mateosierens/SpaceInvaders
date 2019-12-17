//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_SUBJECT_H
#define SPACEINVADERS_SUBJECT_H

#include "Observer.h"
#include <memory>
#include <iostream>
#include <vector>

namespace ObserverPattern {
    class Subject {
    private:
        std::vector<std::shared_ptr<Observer>> observers;

    public:
        void addObserver(std::shared_ptr<Observer> observer);

        void removeObserver(std::shared_ptr<Observer> observer);

    protected:
        void notify(const Entity& entity, std::string event);
    };
}




#endif //SPACEINVADERS_SUBJECT_H
