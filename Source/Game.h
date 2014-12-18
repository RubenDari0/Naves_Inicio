#pragma once;
#include "Nave.h"
#include "objeto.h"
#include "Stage.h"

class CGame
{
public:
	bool Start();
	static CGame instanceGame;

	enum Estado{
		ESTADO_INICIANDO,
		ESTADO_MENU,
		ESTADO_PRE_JUGANDO,
		ESTADO_JUGANDO,
		ESTADO_TERMINANDO,
		ESTADO_FINALIZANDO
	};
	CGame();
	void Finalize();

private:
	void Iniciando();
	void Menu();
	void MoverEnemigo();
	bool EsLimitePantalla(Objeto * objeto, int bandera);

	int opcionSeleccionada;
	Uint8 * keys; //Esta variable nos servira para ver si determinadas teclas estan o no pulsadas.
	SDL_Event event; //La variable event de tipo evento de SDL nos servira para monitorizar el teclado.

	SDL_Surface * screen;
	SDL_Surface * imagen;

	Nave * nave;
	Nave * enemigoArreglo [10];
	Stage nivel[4];
	void InicializandoStage();
	int nivelActual;

	Objeto * menu;//Fondo del Menu
	Objeto * textos;//Textos del Menu
	Objeto * fondo;//Fondo del Juego

	int tick;
	int tiempoFrameInicial;
	int tiempoFrameFinal;

	Estado estado;
	int vida;
	int enemigosEliminados;
};