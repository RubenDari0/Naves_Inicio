#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>


CGame::CGame(){
	tiempoFrameInicial = 0;
	estado=ESTADO_INICIANDO;
	//Iniciando();
	//atexit(SDL_Quit);
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
	delete nave;
	//delete(keys);
	delete * enemigoArreglo;
	SDL_FreeSurface(screen);
	SDL_Quit();
}

void CGame::Iniciando(){
	if (SDL_Init( SDL_INIT_VIDEO )){
		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	screen = SDL_SetVideoMode( WIDTH_SCREEN, HEIGHT_SCREEN, 24, SDL_HWSURFACE);
	if (screen == NULL){
		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption( "Mi Primer Juego", NULL );
	atexit(SDL_Quit);

	nave = new Nave(screen,"../Data/minave.bmp",(WIDTH_SCREEN/2),(HEIGHT_SCREEN-80),MODULO_MINAVE_NAVE);
	menu = new Objeto(screen,"../Data/naves.bmp",0,0,MODULO_MENUFONDO_FONDO);
	textos = new Objeto(screen,"../Data/menu.bmp",0,0,MODULO_MENUTEXTO_TITULO);
	fondo = new Objeto(screen,"../Data/navesita.bmp",0,0,MODULO_MENUFONDO_FONDO);
	for(int i=0;i<10;i++){
		enemigoArreglo[i] = new Nave(screen,"../Data/enemigo.bmp",i*60,0,MODULO_ENEMIGO_NAVE);
		enemigoArreglo[i]->GetNaveObjeto()->SetAutoMovimiento(false);
		enemigoArreglo[i]->GetNaveObjeto()->SetPasoLimite(4);
	}
	tick=0;
	opcionSeleccionada = MODULO_MENUTEXTO_OPCION1;
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;

	while (salirJuego == false){  
		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO:
			Iniciando();
			InicializandoStage();
			estado = ESTADO_MENU;
			break;
		case Estado::ESTADO_MENU:
			menu->Pintar();
			textos->Pintar(MODULO_MENUTEXTO_TITULO,151,48);
			textos->Pintar(MODULO_MENUTEXTO_NOMBRE,327,440);
			Menu();
			//estado = ESTADO_JUGANDO;
			break;
		case ESTADO_PRE_JUGANDO:
			nivelActual=0;
			vida = 1;
			enemigosEliminados = 0;
			estado = ESTADO_JUGANDO;
			break;
		case Estado::ESTADO_JUGANDO:
			for(int i=0;i<nivel[nivelActual].NumeroEnemigosVisibles;i++){
				enemigoArreglo[i]->GetNaveObjeto()->Actualizar();
			}
			MoverEnemigo();
			fondo->Pintar();
			keys = SDL_GetKeyState(NULL);
			if(keys[SDLK_RIGHT]){
				if(!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_DERECHO))
					nave->MoverDerecha(nivel[nivelActual].VelocidadNavePropia);
			}
			if(keys[SDLK_LEFT]){
				if(!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_IZQUIERDO))
				nave->MoverIzquierda(nivel[nivelActual].VelocidadNavePropia);
			}
			if(keys[SDLK_DOWN]){
				if(!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_INFERIOR))
					nave->MoverAbajo(nivel[nivelActual].VelocidadNavePropia);
			}
			if(keys[SDLK_UP]){
				if(!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_SUPERIOR))
				nave->MoverArriba(nivel[nivelActual].VelocidadNavePropia);
			}
			if(keys[SDLK_SPACE]){
				nave->Disparar(NAVE_PROPIA, nivel[nivelActual].balasMaximas);
			}
			///// Simulacion Colisiones /////
			if (keys[SDLK_x]){//Bala enemigo / Nuestra nave
				nave->simularColision(true);
			}
			if (keys[SDLK_c]){//Nuestra bala / Nave enemigo
				int enemigoAEliminar = rand() % nivel[nivelActual].NumeroEnemigosVisibles;
				enemigoArreglo[enemigoAEliminar]->simularColision(true);
			}
			if (keys[SDLK_v]){//Nuestra nave / Nave enemigo
			}
			/////////////////////////////////
			///// Control de colisiones /////
			for(int i=0; i<nivel[nivelActual].NumeroEnemigosVisibles; i++){
				if(enemigoArreglo[i]->estaColisionandoConBala(nave))
					vida--;
				if(nave->estaColisionandoConBala(enemigoArreglo[i])){
					enemigoArreglo[i]->setVisible(false);
					enemigosEliminados++;
					nave->simularColision(false);
					if(enemigosEliminados < nivel[nivelActual].NumeroEnemigosAEliminar){
						enemigoArreglo[i]->CrearNuevo();
					}
				}
			}
			///////////////////////////////// 
			if(vida<=0)
				estado=ESTADO_TERMINANDO;
			if(enemigosEliminados >= nivel[nivelActual].NumeroEnemigosAEliminar){
				nivelActual++;
				// Cargar otro fondo;
			}
			nave->Pintar(NAVE_PROPIA);
			for(int i=0;i<nivel[nivelActual].NumeroEnemigosVisibles;i++){
				enemigoArreglo[i]->Pintar(NAVE_ENEMIGO);
				enemigoArreglo[i]->AutoDisparar(nivel[nivelActual].balasMaximas);
			}
			break;
		case Estado::ESTADO_TERMINANDO:
			break;
		case Estado::ESTADO_FINALIZANDO:
			salirJuego = true;
			break;
		}
		while(SDL_PollEvent(&event)) //Aqui SDL creara una lista de eventos ocurridos
		{
			if(event.type == SDL_QUIT) {salirJuego = true;} //Si se detecta una salida de SDL o...
			if(event.type == SDL_KEYDOWN) {  }
		}

		//Este codigo estara provicionalmente aqui.
		SDL_Flip(screen);

		//Calculando FPS
		tiempoFrameFinal = SDL_GetTicks();
		while(tiempoFrameFinal < (tiempoFrameInicial + FPS_DELAY)){
			tiempoFrameFinal=SDL_GetTicks();
			SDL_Delay(1);
		}
		printf("Frames:%d Tiempo:%d Tiempo Promedio:%f Tiempo por Frame:%d FPS:%f\n",tick,SDL_GetTicks(), (float)SDL_GetTicks()/(float)tick, tiempoFrameFinal - tiempoFrameInicial, 1000.0f / (float)(tiempoFrameFinal - tiempoFrameInicial));
		tiempoFrameInicial = tiempoFrameFinal; //Marcamos el inicio nuevamente.
		tick++;
	}
	return true;
}
bool CGame::EsLimitePantalla(Objeto * objeto, int bandera){
	if(bandera & BORDE_IZQUIERDO)
		if(objeto->ObtenerX() <= 0)
			return true;
	if(bandera & BORDE_SUPERIOR)
		if(objeto->ObtenerY() <= 0)
			return true;
	if(bandera & BORDE_DERECHO)
		if(objeto->ObtenerX() >= WIDTH_SCREEN - objeto->ObtenerW())
			return true;
	if(bandera & BORDE_INFERIOR)
		if(objeto->ObtenerY() >= HEIGHT_SCREEN - objeto->ObtenerH())
			return true;
	return false;
}

void CGame::MoverEnemigo()
{

	for (int i = 0; i < nivel[nivelActual].NumeroEnemigosVisibles; i++)

		{

			if(enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual()==0)

				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_DERECHO))

				{

				enemigoArreglo[i]->GetNaveObjeto()->MoverX(nivel[nivelActual].VelocidadNaveEnemigo);//Derecha

				}

				else

				{

					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();


				}

			if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 1)

				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_INFERIOR))


				{

				enemigoArreglo[i]->GetNaveObjeto()->MoverY(nivel[nivelActual].VelocidadNaveEnemigo);

				}

				else

				{

					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();

				}

			if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 2)

				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_IZQUIERDO))

				{
	
				enemigoArreglo[i]->GetNaveObjeto()->MoverX(-nivel[nivelActual].VelocidadNaveEnemigo);

				}

				else

				{

					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();

				}
			
                         if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 3)

				if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_SUPERIOR))

				{

				enemigoArreglo[i]->GetNaveObjeto()->MoverY(-nivel[nivelActual].VelocidadNaveEnemigo);

				}

				else

				{

					enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();

				}

	   }

}



void CGame::Menu(){
	for (int i = MODULO_MENUTEXTO_OPCION1, j = 0; i <= MODULO_MENUTEXTO_OPCION2; i++, j++){
		keys = SDL_GetKeyState(NULL);
		if(keys[SDLK_UP]){
			opcionSeleccionada = MODULO_MENUTEXTO_OPCION1;
		}
		if(keys[SDLK_DOWN]){
			opcionSeleccionada = MODULO_MENUTEXTO_OPCION2;
		}
		if(i == opcionSeleccionada)
			textos->Pintar(i+2,260,162+(j*40));
		else
			textos->Pintar(i,260,162+(j*40));
		if(keys[SDLK_RETURN]){
			if(opcionSeleccionada == MODULO_MENUTEXTO_OPCION1){
				estado = Estado::ESTADO_PRE_JUGANDO;
			}
			if(opcionSeleccionada == MODULO_MENUTEXTO_OPCION2){
				estado = Estado::ESTADO_FINALIZANDO;
			}
		}
	}
}
