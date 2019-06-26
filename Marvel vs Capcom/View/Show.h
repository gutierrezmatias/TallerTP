#pragma once
#include "../Model/LTexture.h"
#include "../Model/LTexture.h"
#include "../Comunicacion/EstructuraDatos.h"
#include <sstream>
#include <stdio.h>
#include <string>
#include <iostream>
#include "../Model/Equipo.h"
class Show{
private:
	LTexture gReady;
	LTexture gWin;
	LTexture gLose;

	LTexture gAmerica;
	LTexture gChunlee;
	LTexture gSpider;
	LTexture gVenom;

	LTexture gTexto;

	LTexture gBorde;

	TTF_Font *gFont = NULL;

	std::stringstream texto;

	SDL_Renderer * gRenderer;

	SDL_Color textColor = { 255,255, 255, 255 };

public:
	Show(SDL_Renderer * gRen);
	void CargarTexto(std::string txt);
	void render(TIPOLEYENDA tipo, std::string mensaje, Equipo * equipos[2]);
	void RenderPersonaje(int x, int y, std::string nombre);
	~Show();
};