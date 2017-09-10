#pragma once
#include "Dimensional.h"
#include <allegro5/allegro_primitives.h>

//klasa komórki, która posiada włąsne wymiary
class Cell : public Dimensional
{
public:
	Cell();
	~Cell();
	//Konstruktor kopiujący - tworzy nową komórkę jako kopię komórki przekazanej jako parametr
	Cell (const Cell& cell);
	//Tworzy nową komórkę przekazując offset
	Cell(int shiftX, int shiftY);
	//rysuje prostokąt o szerokości = x, wysokości = y przesunięty o offsety odpowiednio, czyli rysuje tylko siatkę
	void Draw(int x, int y, int offsetX, int offsetY);
    //rysuje prostokąt wypełniający kolorem
	void DrawFilled(ALLEGRO_COLOR color);
	//rysuje komórkę na planszy i przupisuje ją do właściciela
	void AssignToPlayer(ALLEGRO_COLOR playerColor, int playerId);
	//zamalowuje komórkę na neutralny kolor i usuwa informację o właścicielu
	void UnassignFromPlayer();
	//opisuje współrzędne komórki na siatce grid
	int x, y;
	//opisują przesunięcię względem komórki referncyjnej. Używane do repreentacji kształtów
	int shiftX, shiftY;
	//opisuje przesunięcie lewego górnego rogu grida względem górnego lewego rogu okna.
    int offsetX, offsetY;
    //id gracza do którego komórka należy
    int id;
    //kolor na który komórka zostanie pokolorowana
    ALLEGRO_COLOR color;
private:
    ALLEGRO_COLOR black;
    ALLEGRO_COLOR white;
    //rysuje szkielet/obramowanie komórki
    void DrawWires();
};

