#include "Cell.h"

Cell::Cell()
{
	width = 15;
	height = 15;
	black = al_map_rgb(0, 0, 0);
    white = al_map_rgb(255, 255, 255);
}

Cell::~Cell()
{
}

Cell::Cell (const Cell& cell)
{
    this->x = cell.x;
    this->y = cell.y;
    this->offsetX = cell.offsetX;
    this->offsetY = cell.offsetY;
    this->shiftX = cell.shiftX;
    this->shiftY = cell.shiftY;
    this->id = cell.id;
    this->color = cell.color;
}

Cell::Cell(int shiftX, int shiftY)
{
    this->shiftX = shiftX;
    this->shiftY = shiftY;
}

void Cell::Draw(int x, int y, int offsetX, int offsetY)
{
    this->x = x;
    this->y = y;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    DrawWires();
}

void Cell::DrawWires()
{
    //rysuje szkielet/obramowanie komórki
    //pierwsze 2 parametry to x i y które wskazuj¹ na lewy górny róg, potem x i y które wskazuj¹ na prawy dolny róg
    //potem kolor i gruboœæ = 2
    al_draw_rectangle(x * width + offsetX, y * height + offsetY, (x + 1)* width + offsetX, (y + 1) * height + offsetY,
	black, 2);
}

void Cell::DrawFilled(ALLEGRO_COLOR color)
{
	al_draw_filled_rectangle(x * width + offsetX, y * height + offsetY, (x + 1)* width + offsetX, (y + 1) * height + offsetY,
		color);
    this->color = color;
}

void Cell::AssignToPlayer(ALLEGRO_COLOR playerColor, int playerId)
{
    DrawFilled(playerColor);
    DrawWires();
    id = playerId;
}

void Cell::UnassignFromPlayer()
{
    DrawFilled(white);
    DrawWires();
    id = 0;
}
