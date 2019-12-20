//
// Created by mateo on 09.12.19.
//

#ifndef SPACEINVADERS_VIEW_H
#define SPACEINVADERS_VIEW_H

#include <memory>
#include "Observer.h"

class View : public ObserverPattern::Observer {
private:
    std::shared_ptr<Entity> entity;
public:
    View(std::shared_ptr<Entity> &entity);

    virtual ~View() {};

    virtual void onNotify(const Entity &entity, std::string event) = 0;
};


#endif //SPACEINVADERS_VIEW_H
