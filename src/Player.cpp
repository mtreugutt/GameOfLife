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
            //przypisujmey komórce w³aœciciela
            (**it).id = id;
            //dorzucamy komórkê do listy ¿ywych komórek gracza
            livingCells.push_back(*it);
        }
}

void Player::GetNextRule()
{
    //ustalamy kierunek przegl¹dania listy
    if(lookForNextRules)
        currentRules++;
    else
        currentRules--;
    //tworzymy iterator wskazuj¹cy na now¹ regu³ê
    list<Rules*> :: iterator nextRules = currentRules;
    //je¿eli obecna regu³a jest z pocz¹tku lub z koñca listy to odwracamy kierunek przegl¹dania listy
    if (*currentRules == *rules->begin() || *(++nextRules) == *rules->end())
        lookForNextRules = !lookForNextRules;
}

