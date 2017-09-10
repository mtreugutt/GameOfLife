#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
using namespace std;
class Rules
{
    public:
        //konstruktor przyjmujący wskaźnik na nazwę reguły
        Rules(char* name);
        //destruktor
        ~Rules();
        char* rulesName;
        //lista liczb które definiują ile sąsiadów jest potrzebnych by komórka przeżyła
        list<int> toLive;
        //lista liczb które definiują ile s¹siadów jest potrzebnych by komórka się narodziła
        list<int> toBeBorn;
        //wskaźnik do całego opisu
        char* description;
        //metoda która inicjalizuje regułę
        void Initialize();
};
