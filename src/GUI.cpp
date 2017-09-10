#include "GUI.h"

GUI::GUI(Display* display, Grid* grid, list<Player*>& players)
{
    this->display = display;
    this->grid = grid;

    modeText = (char *)"Tryb edycji";
    player1Text = (char *)"Gracz 1";
    player2Text = (char *)"Gracz 2";
    //pobranie gracza pierwszego z listy graczy
    Player& player1 = **(players.begin());
    //pobranie  zasad pierwszego gracza
    Rules& rules1 = **player1.currentRules;
    //pobranie opisu zasad pierwszego gracza
    player1RulesText = rules1.description;
    //pobranie gracza drugiego z listy graczy
    Player& player2 = **(++players.begin());
    //pobranie  zasad drugiego gracza
    Rules& rules2 = **player2.currentRules;
    //pobranie opisu zasad drugiego gracza
    player2RulesText = rules2.description;
    xText = (char *)"0";
    yText = (char *)"0";

    //za³adowanie pakietu z czcionkami i konkretnie format ttf
	al_init_font_addon();
	al_init_ttf_addon();

	//path to the folder that contains the executable
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	// change the working directory
    al_change_directory(al_path_cstr(path, '/'));
    al_destroy_path(path);

	font = al_load_ttf_font("DejaVuSans.ttf", 20,0 );
	RefreshTexts();
}

void GUI::RefreshTexts()
{
    //ustawiamy prostok¹t obcinania jako pasek u góry, który ma wysokoœæ grid->offsetY i szerokoœæ ekranu
	al_set_clipping_rectangle(0, 0, display->width, grid->offsetY);
	//czyœcimy ten obszar na bia³o
	al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_text(font,al_map_rgb(0,0,0), 0,0,0, modeText);
    al_draw_text(font,al_map_rgb(0,0,0), 300,0,0, player1Text);
    al_draw_text(font,al_map_rgb(0,0,0), 300,50,0, player2Text);
    al_draw_text(font,al_map_rgb(0,0,0), 400,0,0, player1RulesText);
    al_draw_text(font,al_map_rgb(0,0,0), 400,50,0, player2RulesText);
    al_draw_text(font,al_map_rgb(0,0,0), 150,0,0, xText);
    al_draw_text(font,al_map_rgb(0,0,0), 200,0,0, yText);
    //ustawiamy prostok¹t obcinania na ca³y ekran
	al_set_clipping_rectangle(0, 0, display->width, display->height);
	al_flip_display();
}
