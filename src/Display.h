#pragma once
#include <allegro5/allegro.h>
#include "Dimensional.h"

//klasa reprezentuj� okienko ALLEGRO, ma zdefiniowany rozmiary i obiekt ALLEGRO_DISPLAY
class Display : public Dimensional
{
public:
    //bezparametrowy konstruktor klasy Display
	Display();
	//inicjalizacja klasy Display, w kt�rej tworzony jest obiekt ALLEGRO_DISPLAY
	int Initialize();
	//destruktor
	~Display();
private:
	ALLEGRO_DISPLAY *display;
};

