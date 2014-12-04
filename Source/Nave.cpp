#include "Nave.h"
#include "Config.h"

Nave::Nave(SDL_Surface * screen, char * rutaImagen, int x, int y, int module){
	nave = new Objeto(screen, rutaImagen, x, y, module);
	for(int i = 0;i<MAXIMO_DE_BALAS;i++){

	bala[i] = new Objeto(screen, "../Data/balas.bmp", 0, 0, MODULO_BALAS_BALA);
	bala[i]->SetVisible(false);
	}
	balasVisibles=0;
}

void Nave::Pintar(int tipoNave){
	nave->Pintar();
	for(int i = 0;i<MAXIMO_DE_BALAS;i++){
	bala[i]->Pintar();
	switch(tipoNave){
	case NAVE_PROPIA:
		bala[i]->MoverY(-10); //codigo para mover para arriba
		break;
	case NAVE_ENEMIGO:
		bala[i]->MoverY(10); //codigo para mover para arriba
	
	break;
	}
	}
}


void Nave::Disparar(int tipoNave){
	
	bala[balasVisibles]->SetVisible(true);
	
	switch(tipoNave){
	case NAVE_PROPIA:
			bala[balasVisibles]->PonerEn(nave->ObtenerX()+nave->ObtenerW()/2,nave->ObtenerY());
			break;
	case NAVE_ENEMIGO:
		bala[balasVisibles]->PonerEn(nave->ObtenerX()+nave->ObtenerW()/2,nave->ObtenerY()+nave->ObtenerH());
		break;
	}

	bala[balasVisibles]->PonerEn(nave->ObtenerX()+nave->ObtenerW()/2, nave->ObtenerY());
	balasVisibles++;
	if(balasVisibles >= MAXIMO_DE_BALAS)
		balasVisibles=0;
	
}

void Nave::MoverAbajo(){
nave->MoverY(10);
}
void Nave::MoverArriba(){
nave->MoverY(-10);
}
void Nave::MoverDerecha(){
nave->MoverX(10);
}
void Nave::MoverIzquierda(){
nave->MoverX(-10);
}

Objeto* Nave::GetNaveObjeto(){
	return nave;
}

void Nave::AutoDisparar(){
	if((rand() % 100)<10)
	Disparar(NAVE_ENEMIGO);

}
