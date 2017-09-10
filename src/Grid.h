#pragma once
#include <allegro5/allegro_primitives.h>
#include "Dimensional.h"
#include "Cell.h"
#include "Display.h"

//klasa siatki komórek, przechowuje liczbê komórek wzd³u¿ i wszerz
class Grid : public Dimensional
{
public:
    //konstruktor klasy Grid przyjmuj¹cy referencjê na Display
	Grid(Display& display);
	//destruktor
	~Grid();
	//Inicjalizuje Grid. Tworzy komórki siatki i je rysuje na ekranie.
	void Initialize();
	//2 wymiarowa tablica komórek
    Cell** Cells;
    //marginesy siatki od granic okna
    int offsetX, offsetY;
};

