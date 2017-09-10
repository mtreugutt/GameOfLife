#pragma once
#include <allegro5/allegro.h>
#include "EventHandler.h"
#include "GUI.h"

//klasa nasłuchuje na różne eventy. Propaguje ich obsługę do klasy "EventHandler"
class EventListener
{
    public:
        //konstrutktor przyjmujący referencję do listy z graczami, referencję do listy z kształtami oraz wskaźnik do GUI
        EventListener(list<Player*>& players,list<list<Cell>* >&shapes, GUI* gui, EventHandler* EventHandler);
        ~EventListener();
        //podczas inicjalizacji przekazujemy wskaźnik do EventHandler oraz wskaźnik do ALLEGRO_TIMER
        int Initialize(ALLEGRO_TIMER* timer);
        //rozpoczyna nasłuchiwanie na eventy
        void ListenForEvents();
    private:
        //kolejka na eventy ALLEGRO
        ALLEGRO_EVENT_QUEUE *event_queue;
        //wskaźnik na naszą obsługę eventów
        EventHandler* eventHandler;
        //lista graczy
        list<Player*> players;
        //lista na dostępne kształty - jeden kształt to lista komórek
        list<list<Cell>* > shapes;
        //wskaźnik na GUI
        GUI* gui;
        //flaga do sprawdzenia czy jesteœmy w trybie symulacji
        bool isInSimulation;
        //iterator na obecnie wybranego gracza
        list<Player*>::iterator currentPlayer;
        //iterator na obecnie wybrany kształt
        list<list<Cell>* >::iterator currentShape;
        //flagi, które mówią w którą stronę przeglądamy listy graczy i kształtów
        bool lookForNext, lookForNextShape;
        //metoda wybierająca nowego gracza
        void getNextPlayer();
        //metoda wybierająca nowy kształt
        void getNextShape();
};
