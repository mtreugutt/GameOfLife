#include <allegro5/allegro.h>
#include "Display.h"
#include "Grid.h"
#include "Timer.h"
#include "EventListener.h"
#include "Player.h"
#include "GUI.h"

int main()
{
    //inicjalizujemy komponenty ALLEGRO
	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	al_set_app_name("Game of Life - Weronika Rybicka, Maria Treugutt");


	Display display = Display();
	if (display.Initialize() == EXIT_FAILURE)
		return EXIT_FAILURE;

	al_clear_to_color(al_map_rgb(255, 255, 255));


	Grid grid = Grid(display);
	grid.Initialize();


	//tworzymy regu造
    list<Rules*> rules;

    Rules rules1 = Rules((char*)"Conway");
    rules1.toLive.push_back(2);
    rules1.toLive.push_back(3);
    rules1.toBeBorn.push_back(3);
    rules1.Initialize();
    rules.push_back(&rules1);

    Rules rules2 = Rules((char*)"Labirynt");
    rules2.toLive.push_back(1);
    rules2.toLive.push_back(2);
    rules2.toLive.push_back(3);
    rules2.toLive.push_back(4);
    rules2.toLive.push_back(5);
    rules2.toBeBorn.push_back(3);
    rules2.Initialize();
    rules.push_back(&rules2);

    Rules rules3 = Rules((char*)"2x2");
    rules3.toLive.push_back(1);
    rules3.toLive.push_back(2);
    rules3.toLive.push_back(5);
    rules3.toBeBorn.push_back(3);
    rules3.toBeBorn.push_back(6);
    rules3.Initialize();
    rules.push_back(&rules3);

    Rules rules4 = Rules((char*)"Ameba");
    rules4.toLive.push_back(1);
    rules4.toLive.push_back(3);
    rules4.toLive.push_back(5);
    rules4.toLive.push_back(8);
    rules4.toBeBorn.push_back(3);
    rules4.toBeBorn.push_back(5);
    rules4.toBeBorn.push_back(7);
    rules4.Initialize();
    rules.push_back(&rules4);

    Rules rules5 = Rules((char*)"Serwety");
    rules5.toBeBorn.push_back(2);
    rules5.toBeBorn.push_back(3);
    rules5.toBeBorn.push_back(4);
    rules5.Initialize();
    rules.push_back(&rules5);


    //tworzymy graczy
	list<Player*> players;

	Player player1 = Player(al_map_rgb(255, 0, 0), &rules);
	players.push_back(&player1);

	Player player2 = Player(al_map_rgb(0, 255, 0), &rules);
	players.push_back(&player2);

    GUI gui = GUI(&display, &grid, players);

	//tworzymy kszta速y

	//liste wskaznikow na liste komorek danego ksztaltu
	list<list<Cell>* > shapes;

    //definicja kszta速u
    list<Cell> shape0;
    shape0.push_back(Cell(0,0));
    //dodajemy go do listy kszta速闚
    shapes.push_back(&shape0);

    list<Cell> shape1;
    shape1.push_back(Cell(0,0));
    shape1.push_back(Cell(1,1));
    shape1.push_back(Cell(1,2));
    shape1.push_back(Cell(2,0));
    shape1.push_back(Cell(2,1));
    shapes.push_back(&shape1);

    list<Cell> shape2;
    shape2.push_back(Cell(0,-1));
    shape2.push_back(Cell(1,-1));
    shape2.push_back(Cell(1,0));
    shape2.push_back(Cell(2,0));
    shape2.push_back(Cell(1,1));
    shape2.push_back(Cell(0,1));
    shape2.push_back(Cell(0,2));
    shape2.push_back(Cell(-1,2));
    shape2.push_back(Cell(-1,1));
    shape2.push_back(Cell(-1,0));
    shape2.push_back(Cell(-2,0));
    shape2.push_back(Cell(-2,1));
    shapes.push_back(&shape2);

    list<Cell> shape3;
    shape3.push_back(Cell(0,0));
    shape3.push_back(Cell(1,0));
    shape3.push_back(Cell(2,0));
    shape3.push_back(Cell(0,1));
    shape3.push_back(Cell(1,1));
    shape3.push_back(Cell(-1,1));
    shapes.push_back(&shape3);

    list<Cell> shape4;
        int xoffset = -6;
        int yoffset = -6;
            shape4.push_back(Cell(2+ xoffset,0+ yoffset));
            shape4.push_back(Cell(3+ xoffset,0+ yoffset));
            shape4.push_back(Cell(4+ xoffset,0+ yoffset));
            shape4.push_back(Cell(5+ xoffset,2+ yoffset));
            shape4.push_back(Cell(5+ xoffset,3+ yoffset));
            shape4.push_back(Cell(5+ xoffset,4+ yoffset));
            shape4.push_back(Cell(2+ xoffset,5+ yoffset));
            shape4.push_back(Cell(3+ xoffset,5+ yoffset));
            shape4.push_back(Cell(4+ xoffset,5+ yoffset));
            shape4.push_back(Cell(0+ xoffset,2+ yoffset));
            shape4.push_back(Cell(0+ xoffset,3+ yoffset));
            shape4.push_back(Cell(0+ xoffset,4+ yoffset));

        xoffset = -6;
        yoffset = 1;
            shape4.push_back(Cell(2+ xoffset,0+ yoffset));
            shape4.push_back(Cell(3+ xoffset,0+ yoffset));
            shape4.push_back(Cell(4+ xoffset,0+ yoffset));
            shape4.push_back(Cell(5+ xoffset,1+ yoffset));
            shape4.push_back(Cell(5+ xoffset,2+ yoffset));
            shape4.push_back(Cell(5+ xoffset,3+ yoffset));
            shape4.push_back(Cell(2+ xoffset,5+ yoffset));
            shape4.push_back(Cell(3+ xoffset,5+ yoffset));
            shape4.push_back(Cell(4+ xoffset,5+ yoffset));
            shape4.push_back(Cell(0+ xoffset,1+ yoffset));
            shape4.push_back(Cell(0+ xoffset,2+ yoffset));
            shape4.push_back(Cell(0+ xoffset,3+ yoffset));

        xoffset = 1;
        yoffset = -6;
            shape4.push_back(Cell(1+ xoffset,0+ yoffset));
            shape4.push_back(Cell(2+ xoffset,0+ yoffset));
            shape4.push_back(Cell(3+ xoffset,0+ yoffset));
            shape4.push_back(Cell(5+ xoffset,2+ yoffset));
            shape4.push_back(Cell(5+ xoffset,3+ yoffset));
            shape4.push_back(Cell(5+ xoffset,4+ yoffset));
            shape4.push_back(Cell(1+ xoffset,5+ yoffset));
            shape4.push_back(Cell(2+ xoffset,5+ yoffset));
            shape4.push_back(Cell(3+ xoffset,5+ yoffset));
            shape4.push_back(Cell(0+ xoffset,2+ yoffset));
            shape4.push_back(Cell(0+ xoffset,3+ yoffset));
            shape4.push_back(Cell(0+ xoffset,4+ yoffset));

        xoffset = 1;
        yoffset = 1;
            shape4.push_back(Cell(1+ xoffset,0+ yoffset));
            shape4.push_back(Cell(2+ xoffset,0+ yoffset));
            shape4.push_back(Cell(3+ xoffset,0+ yoffset));
            shape4.push_back(Cell(5+ xoffset,1+ yoffset));
            shape4.push_back(Cell(5+ xoffset,2+ yoffset));
            shape4.push_back(Cell(5+ xoffset,3+ yoffset));
            shape4.push_back(Cell(1+ xoffset,5+ yoffset));
            shape4.push_back(Cell(2+ xoffset,5+ yoffset));
            shape4.push_back(Cell(3+ xoffset,5+ yoffset));
            shape4.push_back(Cell(0+ xoffset,1+ yoffset));
            shape4.push_back(Cell(0+ xoffset,2+ yoffset));
            shape4.push_back(Cell(0+ xoffset,3+ yoffset));
    shapes.push_back(&shape4);

    EventHandler eventHandler = EventHandler(&grid);

    Timer timer = Timer();
	if (timer.Initialize() == EXIT_FAILURE)
		return EXIT_FAILURE;

    EventListener eventListener = EventListener(players, shapes, &gui, &eventHandler);
	if (eventListener.Initialize(timer.timer) == EXIT_FAILURE)
		return EXIT_FAILURE;
    timer.Start();
    eventListener.ListenForEvents();

	return EXIT_SUCCESS;
}

