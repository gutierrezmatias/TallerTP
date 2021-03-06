#include "Activo.h"
#include "../View/View.h"
#include "GeneralPantalla.h"

Activo::Activo() {
	//ctor
}


Activo::~Activo() {
	//dtor
}

void Activo::move() {
	quieto=false;

		this->mPosX += this->mVelX * aceleracion;
		if ((mPosX < 0) || (mPosX + ANCHO_JUGADOR >= ANCHO_NIVEL)) {
			mPosX -= mVelX * aceleracion;
		}
		mVelY -= aceleracion;
		mPosY -= mVelY;
		if ((mPosY < 0) || (mPosY + ALTO_JUGADOR >= ALTO_NIVEL)) {
			mPosY += mVelY;
			mVelY = 0;
		}
		quieto=true;
}

void Activo::moveVertical() {
	quieto=false;

		mVelY -= aceleracion;
		mPosY -= mVelY;
		if ((mPosY < 0) || (mPosY + ALTO_JUGADOR >= ALTO_NIVEL)) {
			mPosY += mVelY;
			mVelY = 0;
		}
		quieto=true;
}

bool Activo::estaQuieto(){

	return quieto;
}

bool Activo::isFueraDePantalla(){
	return (mPosX > ANCHO_NIVEL)||(mPosX < 0);
}

bool Activo::estaActivo() {
	return true;
}
bool Activo::estaAgachado() {
	return false;
}
bool Activo::estaCambiandoPersonaje(){
	return false;
}

