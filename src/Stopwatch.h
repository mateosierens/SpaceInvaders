//
// Created by mateo on 23.12.19.
//

#ifndef SPACEINVADERS_STOPWATCH_H
#define SPACEINVADERS_STOPWATCH_H

#include <iostream>
#include <chrono>
#include <thread>

class Stopwatch {
public:
    static Stopwatch& instance() {
        static Stopwatch instance_;
        return instance_;
    }

    void sleep(int milliseconds) {
        std::chrono::milliseconds timespan(milliseconds);
        std::this_thread::sleep_for(timespan);
    }

private:
    Stopwatch() {};
};

#endif //SPACEINVADERS_STOPWATCH_H
