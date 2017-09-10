#include "Rules.h"

Rules::Rules(char* rulesName)
{
    this->rulesName = rulesName;
}

void Rules::Initialize()
{
    //bufor pomocniczy do którego będziemy wczytywać liczby
    char buf[3];
    char* dest = new char[30];
    //zaalokowaliśmy pamięć, czyścimy ją na wypadek śmieci
    memset(dest, '\0', sizeof(char)*30 );
    //do bufora "dest" konktatenujemy/łączymy "rulesName"
    strcat(dest, rulesName);
    //teraz do wynikowego bufora dodajemy dwukropek
    strcat(dest, ": ");
    for (list<int> ::iterator prefix = toLive.begin(); prefix != toLive.end(); prefix++)
    {
        //wyciągnięcie inta do bufora znaków - int to ASCII, int w systemie 10-tnym
        itoa(*prefix, buf, 10);
        //konkatenacja dwóch buforów
        strcat(dest, buf);
        strcat(dest, " ");
    }
    strcat(dest, "/ ");
    for (list<int> ::iterator suffix = toBeBorn.begin(); suffix != toBeBorn.end(); suffix++)
    {
         itoa(*suffix, buf, 10);
        //konkatenacja dwóch buforów
        strcat(dest, buf);
        strcat(dest, " ");
    }
    this->description = dest;
}

Rules::~Rules()
{
    delete[] description;
}
