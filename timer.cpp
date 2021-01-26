//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "timer.h"
#include <iostream>

Timer::Timer()
    : seconds(0),
    takingTime(true),
    startPoint(std::chrono::high_resolution_clock::now()) {}

/**
 * @brief Timer::start
 * Start the timer.
 */
void Timer::start() {
    if(!takingTime)
        startPoint = std::chrono::high_resolution_clock::now();
}

/**
 * @brief Timer::stop
 * Stop timer.
 */
void Timer::stop() {

    //Stop time and add to total amount of seconds.
    if(takingTime) {
        auto stopPoint = std::chrono::high_resolution_clock::now();
        seconds += std::chrono::duration_cast<std::chrono::seconds>(stopPoint - startPoint).count();
    }
}


/**
 * @brief Timer::getTime
 * @return Time in seconds.
 */
int Timer::getTime() {

    if(takingTime)
        stop();

    return seconds;
}
