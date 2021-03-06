#include "ViewModel.h"
#include <SDL2/SDL.h>

ViewModel::ViewModel(Model* model, SDL_Renderer* gRenderer, SDL_Rect* camara, LTexture texturasEquipo1[2], LTexture texturasEquipo2[2]) {
	//this->viewPantalla.initialize(gRenderer, texturaPantalla);
	this->model = model;
	this->viewEquipo[0] = new ViewEquipo(model->equipos[0]);
	this->viewEquipo[1] = new ViewEquipo(model->equipos[1]);
	this->camara = camara;
	this->gRenderer = gRenderer;

	this->viewEquipo[0]->initialize(model->getEquipoNro(0),texturasEquipo1);
	this->viewEquipo[1]->initialize(model->getEquipoNro(1),texturasEquipo2);

}

ViewModel::~ViewModel() {
	delete[] this->viewEquipo;
}

void ViewModel::render() {
	//this->viewPantalla.render(this->camara, this->gRenderer);

	for (int i = 0; i < 2; ++i) {
		this->viewEquipo[i]->render(this->camara->x,model->alto_Pantalla -model->alto_Pantalla*0.4 + model->getEquipoNro(i)->getJugadorActivo()->get_alto(), this->gRenderer);
	}
}

void ViewModel::render(int equipo, int zIndex) {

	this->viewEquipo[equipo]->render(this->camara->x,model->alto_Pantalla -model->alto_Pantalla*0.4 + model->getEquipoNro(equipo)->getJugadorActivo()->get_alto(), this->gRenderer, zIndex);
}

