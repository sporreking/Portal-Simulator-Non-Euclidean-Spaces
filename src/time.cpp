#include "time.h"

void Time::init() {
    _startTime = sinceEpochNS();
    _currentTime = _startTime;
}

void Time::update() {
    double newTime = sinceStart();
    _deltaTime = newTime - _currentTime;
    _currentTime = newTime;
}

double Time::delta() {
    return _deltaTime;
}

double Time::current() {
    return _currentTime;
}

double Time::sinceStart() {
    return (sinceEpochNS() - _startTime) / 1000000000.0;
}

uint64_t Time::sinceEpochNS() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::high_resolution_clock::now().time_since_epoch())
        .count();
}

uint64_t Time::_startTime = 0;
double Time::_currentTime = 0;
double Time::_deltaTime = 0;