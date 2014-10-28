#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <SDL.h>
#include "SpriteDef.h"

class Sprite{
	SDL_Surface * imagen;//Imagen
	SDL_Surface * screen;//Pantalla
	SpriteDef spriteDef;
public:
	Sprite(SDL_Surface * screen);//Constructor
	~Sprite();//Destructor
	void CargarImagen(char * nombre);
	void PintarModulo(int nombre, int x, int y);
	int WidthModule(int module);
	int HeightModule(int module);
};
#endif 
