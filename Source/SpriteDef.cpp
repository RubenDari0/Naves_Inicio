#include "SpriteDef.h"
#include "Config.h"

SpriteDef::SpriteDef(){
	modulos[0].id = MODULO_MINAVE_NAVE;
	modulos[0].x = 0;
	modulos[0].y = 0;
	modulos[0].w = 64;
	modulos[0].h = 64;

	modulos[1].id = MODULO_MENUFONDO_FONDO;
	modulos[1].x = 0;
	modulos[1].y = 0;
	modulos[1].w = WIDTH_SCREEN;
	modulos[1].h = HEIGHT_SCREEN;

	modulos[2].id = MODULO_ENEMIGO_NAVE;
	modulos[2].x = 0;
	modulos[2].y = 0;
	modulos[2].w = 54;
	modulos[2].h = 61;

	modulos[3].id = MODULO_MENUTEXTO_TITULO;
	modulos[3].x = 124;
	modulos[3].y = 46;
	modulos[3].w = 417;
	modulos[3].h = 46;

	modulos[4].id = MODULO_MENUTEXTO_NOMBRE;
	modulos[4].x = 186;
	modulos[4].y = 406;
	modulos[4].w = 410;
	modulos[4].h = 36;

	modulos[5].id = MODULO_MENUTEXTO_OPCION1;
	modulos[5].x = 188;
	modulos[5].y = 176;
	modulos[5].w = 140;
	modulos[5].h = 36;

	modulos[6].id = MODULO_MENUTEXTO_OPCION2;
	modulos[6].x = 188;
	modulos[6].y = 232;
	modulos[6].w = 140;
	modulos[6].h = 36;

	modulos[7].id = MODULO_MENUTEXTO_OPCION1SELECCIONADO;
	modulos[7].x = 380;
	modulos[7].y = 176;
	modulos[7].w = 154;
	modulos[7].h = 36;

	modulos[8].id = MODULO_MENUTEXTO_OPCION2SELECCIONADO;
	modulos[8].x = 380;
	modulos[8].y = 232;
	modulos[8].w = 154;
	modulos[8].h = 36;

	modulos[9].id = MODULO_BALAS_BALA;
	modulos[9].x = 0;
	modulos[9].y = 0;
	modulos[9].w = 5;
	modulos[9].h = 5;


}
