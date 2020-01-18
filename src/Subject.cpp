//
// Created by mateo on 09.12.19.
//

#include "Subject.h"

void ObserverPattern::Subject::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void ObserverPattern::Subject::removeObserver(std::shared_ptr<Observer> observer) {
    // search for observer to be removed
    for (auto obs = observers.begin(); obs != observers.end(); obs++) {
        if (observer == (*obs)) {
            // remove observer from observers and let obs point to next observer in vector
            obs = observers.erase(obs);
        }
    }
}

void ObserverPattern::Subject::notify(const Entities::Entity &entity, std::string event) {
    for (std::shared_ptr<Observer> obs: observers) {
        obs->onNotify(entity, event);
    }
}
