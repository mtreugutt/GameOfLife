#include "EventListener.h"

EventListener::EventListener(list<Player*>& players,list<list<Cell>* >&shapes, GUI* gui, EventHandler* eventHandler)
{
    this->players = players;
    this->shapes = shapes;
    this->gui = gui;
    this->eventHandler = eventHandler;
    isInSimulation = false;
    //wybieramy gracza jako pierwszego z listy
    currentPlayer = players.begin();
    lookForNext = lookForNextShape = true;
    //wybieramy kszta³t jako pierwszy z listy
    currentShape = shapes.begin();
    this->eventHandler->shape = *currentShape;
}

EventListener::~EventListener()
{
    //destruktorze niszczymy kolejkê eventów ALLEGRO
    al_destroy_event_queue(event_queue);
}

int EventListener::Initialize(ALLEGRO_TIMER* timer)
{
    //tworzymy kolejkê eventów ALLEGRO
   event_queue = al_create_event_queue();
    if(!event_queue) {
       return EXIT_FAILURE;
    }
    //rejestrujemy siê na eventy zwi¹zane z timererm, klawiatur¹ i myszk¹
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    return EXIT_SUCCESS;
}

void EventListener::getNextPlayer()
{
    //ustalamy kierunek przegl¹dania listy
    if(lookForNext)
        currentPlayer++;
    else
        currentPlayer--;
    //tworzymy iterator wskazuj¹cy na nowego gracza
    list<Player*> :: iterator nextPlayer = currentPlayer;
    //je¿eli obecny gracz jest z pocz¹tku lub z koñca listy to odwracamy kierunek przegl¹dania listy
    if (*currentPlayer == *players.begin() || *(++nextPlayer) == *players.end())
        lookForNext = !lookForNext;
}

void EventListener::getNextShape()
{
    //ustalamy kierunek przegl¹dania listy
    if(lookForNextShape)
        currentShape++;
    else
        currentShape--;
    //tworzymy iterator wskazuj¹cy na nowy kszta³t
    list<list<Cell>* > :: iterator nextShape = currentShape;
    //je¿eli obecny kszta³t jest z pocz¹tku lub z koñca listy to odwracamy kierunek przegl¹dania listy
    if (*currentShape == *shapes.begin() || *(++nextShape) == *shapes.end())
        lookForNextShape = !lookForNextShape;

}

void EventListener::ListenForEvents()
{
    //klasa zbiblioteki allegro, przchowująca stan myszki
    ALLEGRO_MOUSE_STATE msestate;
    //trzymamy wskaŸniki na obu graczy
    Player* player1 = *players.begin();
    Player* player2 = *(++players.begin());
    while(true)
    {
        ALLEGRO_EVENT ev;
        //ta metoda czeka na przyjœcie eventa na który siê zarejestrowaliœmy w metodzie Initialize
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            //co tykniêcie zegara odœwie¿amy rozgrywkê
            if (isInSimulation)
                eventHandler->UpdatePlayers(players);
            //o ile nie jesteœmy w trybie symulacji to mrygamy komórkami
            else
                eventHandler->BlinkHighlighted();
        }
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            //na przycisk ESCAPE zamykamy okno rozgrywki
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                return;
            }

            switch (ev.keyboard.keycode)
            {
            //na wciœniêcie spacji wchodzimy w tryb symulacji lub edycji
            case ALLEGRO_KEY_SPACE:
                isInSimulation = !isInSimulation;
                if (isInSimulation)
                {
                    gui->modeText = (char*) "Tryb symulacji";
                    //usuwamy podœwietlone/mrugaj¹ce komórki
                    eventHandler->RemoveHighlighted();
                }
                else
                {
                    gui->modeText = (char*) "Tryb edycji";
                }
                gui->RefreshTexts();
                break;
            //na wciœniêcie enter zmieniamy gracza
            case ALLEGRO_KEY_ENTER:
                if (!isInSimulation)
                {
                    getNextPlayer();
                    eventHandler->RemoveHighlighted();
                    eventHandler->UpdateCursor(msestate, **currentPlayer, gui);
                }
                break;
            //na wciœniêcie TAB zmieniamy kszta³t - dzia³a tylko w trybie edycji
            case ALLEGRO_KEY_TAB:
                if (!isInSimulation)
                {
                    getNextShape();
                    eventHandler->shape = *currentShape;
                    eventHandler->RemoveHighlighted();
                    eventHandler->UpdateCursor(msestate, **currentPlayer, gui);
                }
                break;
            //na wciœniêcie A zmieniamy regu³y komórek dla pierwszego gracza
            case ALLEGRO_KEY_A:
                player1->GetNextRule();
                gui->player1RulesText = (*(player1->currentRules))->description;
                gui->RefreshTexts();
                break;
                //na wciœniêcie B zmieniamy regu³y komórek dla drugiego gracza
           case ALLEGRO_KEY_B:
                player2->GetNextRule();
                gui->player2RulesText = (*(player2->currentRules))->description;
                gui->RefreshTexts();
                break;
            }
        }
        if (!isInSimulation)
        {
            //przy ka¿dym ruchu myszki odœwie¿amy zaznaczenie komórek
            if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                al_get_mouse_state(&msestate);
                eventHandler->UpdateCursor(msestate, **currentPlayer, gui);
            }
            //przy klikniêciu przyciskiem myszy ustawiamy komórki gracza
            if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                eventHandler->SetNewCells(**currentPlayer);
            }
        }
    }
}

