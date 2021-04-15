#pragma once

#include <chrono>

class Time {
   public:
    // Initializes the time class
    static void init();

    // Should be run every frame to update delta times etc.
    static void update();

    // Retrieves the time passed between the previous two Time::update() calls (in seconds)
    static double delta();

    // Retrieves when the last call to Time::update() was made, relative to the start of the application (in seconds)
    // The returned value should be constant per frame, but will be less precise than Time::sinceStart()
    static double current();

    // Calculates the time passed since the start of the application (in seconds)
    // The returned value may vary throughout a frame, but will be more precise than Time::current()
    static double sinceStart();

    // Returns the time passed since epoch (in nanoseconds)
    static inline uint64_t sinceEpochNS();

   private:
    static uint64_t _startTime;
    static double _currentTime;
    static double _deltaTime;
};