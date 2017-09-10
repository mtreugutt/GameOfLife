#include "Timer.h"

Timer::Timer()
{
    FPS = 5;
}

Timer::~Timer()
{
    al_destroy_timer(timer);
}

int Timer::Initialize()
{
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void Timer::Start()
{
    al_start_timer(timer);
}
