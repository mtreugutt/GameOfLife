#include "Display.h"

Display::Display()
{
	width = 800;
	height = 600;
}

int Display::Initialize()
{
	display = al_create_display(width, height);
	if (display == NULL)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


Display::~Display()
{
	al_destroy_display(display);
}
