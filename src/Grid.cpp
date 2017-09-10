#include "Grid.h"

Grid::Grid(Display& display)
{
    //rozmiar siatki wszerz
	width = 40;
	//rozmiar siatki na wysoko��
	height = 25;
	//utworzenie kom�rki referencyjnej by sprawdzi� jej szeroko�� i wysoko��
    Cell c = Cell();
    int gridX = width * c.width;
	int gridY = height * c.height;
	//ustawienie margines�w mi�dzy siatk� a granic� okna
	offsetX = (display.width - gridX) * 0.5;
	offsetY = (display.height - gridY) * 0.5;
}

Grid::~Grid()
{
    //niszczy wszystkie kom�rki
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
        //tworzy tablic� kom�rek dla ka�dej kolumny
		Cells[i] = new Cell[height];
		for (int j = 0; j < height; j++)
		{
		    //rysuje konkretn� kom�rk�
			Cells[i][j].Draw(i, j, offsetX, offsetY);
		}
	}
	al_flip_display();
}
