#ifndef __NAVE_H__
#define __NAVE_H__
#include "objeto.h"
#include "Config.h"

class Nave{
	Objeto * nave;
	Objeto * bala[MAXIMO_DE_BALAS];
	int balasVisibles;
public:
	Nave(SDL_Surface * screen, char * rutaImagen, int x, int y, int module);
	void Pintar(int tipoNave);
	void Disparar(int tipoNave);
	void AutoDisparar();
	void MoverDerecha();
	void MoverIzquierda();
	void MoverArriba();
	void MoverAbajo();
	Objeto * GetNaveObjeto();
};

#endif