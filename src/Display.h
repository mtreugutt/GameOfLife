#pragma once
#include <allegro5/allegro.h>
#include "Dimensional.h"

//klasa reprezentujê okienko ALLEGRO, ma zdefiniowany rozmiary i obiekt ALLEGRO_DISPLAY
class Display : public Dimensional
{
public:
    //bezparametrowy konstruktor klasy Display
	Display();
	//inicjalizacja klasy Display, w której tworzony jest obiekt ALLEGRO_DISPLAY
	int Initialize();
	//destruktor
	~Display();
private:
	ALLEGRO_DISPLAY *display;
};

