#ifndef __NAVE_H__
#define __NAVE_H__
#include "Sprite.h"

class Nave{
	Sprite * sprite;
	int x;
	int y;
	int w;
	int h;
	bool autoMovimiento;
public:
	void Mover(int posicion);
	Nave(SDL_Surface * screen, char * rutaImagen, int x, int y);//Constructor
	void SetAutoMovimiento(bool autoMovimiento);
	void Pintar();
	void Actualizar();
	int ObtenerX();
	int ObtenerY();
	int ObtenerW();
	int ObtenerH();
};

#endif
