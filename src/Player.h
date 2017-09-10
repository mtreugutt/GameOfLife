#pragma once
#include <allegro5/allegro_primitives.h>
#include "Cell.h"
#include "Rules.h"
#include <list>

using namespace std;

class Player
{
    public:
        //tworzy gracza przypisując mu jego kolor i wskaźnik na zasady
        Player(ALLEGRO_COLOR color, list<Rules*>* rules);
        //kolor gracza
        ALLEGRO_COLOR color;
        //id unikalne dla gracza
        int id;
        //lista przetrzymująca wskaźniki na komórki, które należą do gracza
        list<Cell*> livingCells;
        //przyjmuje referencję na listę komórek, które zostaną przypisane jako żywe komórki gracza, przypisuje do "livingCells"
        void AssignCells(list<Cell*>& cells);
        //zmienia obecne reguły według których rodzą siê nowe i przeżywają istniejące komórki
        void GetNextRule();
        //wskaźnik do listy wszystkich dostępnych reguł
        list<Rules*>* rules;
        //iterator - wskazuje na obecnie wybraną regułę
        list<Rules*>::iterator currentRules;
    private:
        //wspólny dla wszystkich instancji klasy id
        static int idToAssign;
        //kierunek przegl¹dania listy reguł, odpowiednio true = następny element z listy, false = poprzedni element z listy
        bool lookForNextRules;
};
