#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Display.h"
#include "Grid.h"
#include "Player.h"

//klasa przetrzymująca elementy widoku okna
class GUI
{
    public:
        //konstruktor przyjmujący wskaźnik na Display, wskaźnik na Grida oraz referencję na listę graczy
        GUI(Display* display, Grid* grid, list<Player*>& players);
        //odświeża wszystkie teksty
        void RefreshTexts();
        char* modeText;
        char* player1Text;
        char* player2Text;
        char* player1RulesText;
        char* player2RulesText;
        char* xText;
        char* yText;
    private:
	ALLEGRO_FONT* font;
	Display* display;
	Grid* grid;
};
