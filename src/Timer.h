#pragma once
#include <allegro5/allegro.h>
//klasa opakowuj�ca Timer z biblioteki ALLEGRO
class Timer
{
    public:
		//bezparametrowy konstruktor, przypisuje liczb� FPS
        Timer();
		//bezparametrowy desktruktor
        ~Timer();
		//metoda inicjalizuj�ca, kt�ra tworzy obiekt ALLEGRO_TIMER
        int Initialize();
		//startuje dzia�anie timer'a
        void Start();
        ALLEGRO_TIMER *timer;
    private:
		//okre�la pr�dko�� od�wie�ania w klatkach na sekund�
        float FPS;
};
