#include "Grid.h"

Grid::Grid(Display& display)
{
    //rozmiar siatki wszerz
	width = 40;
	//rozmiar siatki na wysokoœæ
	height = 25;
	//utworzenie komórki referencyjnej by sprawdziæ jej szerokoœæ i wysokoœæ
    Cell c = Cell();
    int gridX = width * c.width;
	int gridY = height * c.height;
	//ustawienie marginesów miêdzy siatk¹ a granic¹ okna
	offsetX = (display.width - gridX) * 0.5;
	offsetY = (display.height - gridY) * 0.5;
}

Grid::~Grid()
{
    //niszczy wszystkie komórki
	for (int i = 0; i < width; i++)
	{
		delete[] Cells[i];
	}
}

void Grid::Initialize()
{
	Cells = new Cell*[width];
	for (int i = 0; i < width; i++)
	{
        //tworzy tablicê komórek dla ka¿dej kolumny
		Cells[i] = new Cell[height];
		for (int j = 0; j < height; j++)
		{
		    //rysuje konkretn¹ komórkê
			Cells[i][j].Draw(i, j, offsetX, offsetY);
		}
	}
	al_flip_display();
}
