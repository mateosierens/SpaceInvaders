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

    std::chrono::system_clock::time_point previous;
    std::chrono::system_clock::time_point current;
    double elapsed = 0; // 0 by default


private:
    Stopwatch() = default;
};

#endif //SPACEINVADERS_STOPWATCH_H
