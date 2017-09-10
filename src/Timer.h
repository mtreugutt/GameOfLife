#pragma once
#include <allegro5/allegro.h>
//klasa opakowuj¹ca Timer z biblioteki ALLEGRO
class Timer
{
    public:
		//bezparametrowy konstruktor, przypisuje liczbê FPS
        Timer();
		//bezparametrowy desktruktor
        ~Timer();
		//metoda inicjalizuj¹ca, która tworzy obiekt ALLEGRO_TIMER
        int Initialize();
		//startuje dzia³anie timer'a
        void Start();
        ALLEGRO_TIMER *timer;
    private:
		//okreœla prêdkoœæ odœwie¿ania w klatkach na sekundê
        float FPS;
};
