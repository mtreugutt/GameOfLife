#pragma once
#include <allegro5/allegro_primitives.h>
#include "Dimensional.h"
#include "Cell.h"
#include "Display.h"

//klasa siatki kom�rek, przechowuje liczb� kom�rek wzd�u� i wszerz
class Grid : public Dimensional
{
public:
    //konstruktor klasy Grid przyjmuj�cy referencj� na Display
	Grid(Display& display);
	//destruktor
	~Grid();
	//Inicjalizuje Grid. Tworzy kom�rki siatki i je rysuje na ekranie.
	void Initialize();
	//2 wymiarowa tablica kom�rek
    Cell** Cells;
    //marginesy siatki od granic okna
    int offsetX, offsetY;
};

