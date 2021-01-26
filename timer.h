//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <chrono>

/**
 * @brief The Timer class
 * A class for taking the time.
 * All time will be tracked in seconds.
 */
class Timer {

public:
    Timer();

    void start();

    void stop();

    int getTime();

private:
    int seconds;
    bool takingTime;
    std::chrono::steady_clock::time_point startPoint;
};

#endif // TIMER_H
