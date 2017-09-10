#include "Player.h"

int Player::idToAssign = 1;

Player::Player(ALLEGRO_COLOR color, list<Rules*>* rules)
{
    this->color = color;
    this->id = idToAssign++;
    this->rules = rules;
    lookForNextRules = true;
    currentRules = rules->begin();
}

void Player::AssignCells(list<Cell*>& cells)
{
        for (list<Cell*> :: iterator it = cells.begin(); it != cells.end(); ++it)
        {
            //przypisujmey kom�rce w�a�ciciela
            (**it).id = id;
            //dorzucamy kom�rk� do listy �ywych kom�rek gracza
            livingCells.push_back(*it);
        }
}

void Player::GetNextRule()
{
    //ustalamy kierunek przegl�dania listy
    if(lookForNextRules)
        currentRules++;
    else
        currentRules--;
    //tworzymy iterator wskazuj�cy na now� regu��
    list<Rules*> :: iterator nextRules = currentRules;
    //je�eli obecna regu�a jest z pocz�tku lub z ko�ca listy to odwracamy kierunek przegl�dania listy
    if (*currentRules == *rules->begin() || *(++nextRules) == *rules->end())
        lookForNextRules = !lookForNextRules;
}

