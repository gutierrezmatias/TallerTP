#ifndef VIEW_JUGADOR_H_
#define VIEW_JUGADOR_H_
#include <SDL2/SDL.h>
#include "../Model/LTexture.h"
#include "../Model/Model_Jugador.h"
#include "../Logger/Logger.h"
#include "../EfectoSonido.h"
class View_Jugador { // @suppress("Class has a virtual method and non-virtual destructor")
public:

	View_Jugador(Jugador *model);
	View_Jugador();
	virtual void initialize(Jugador *model, LTexture * texturaJugador);
	void grisar_imagen();
	void desgrisar_imagen();
	void render(int camX, int camY, SDL_Renderer * gRenderer);
	void getSpriteByGolpe(SDL_Rect* currentClip, int &frame, TIPO_GOLPE tipoGolpe);
	Jugador *jugador;
	int getZIndex();



	SDL_Rect * gSpriteCaminar;
	SDL_Rect * gSpriteCambiarPersonaje;
	SDL_Rect  *gSpriteSaltar;
	SDL_Rect  *gSpriteAgachar;
	SDL_Rect  *gSpriteGolpear;
	SDL_Rect  *gSpriteAnimacion;
	//patadas
	SDL_Rect  *gSpritePatadon;
	SDL_Rect  *gSpritePatada;
	SDL_Rect  *gSpritePatadaSaltando;
	SDL_Rect  *gSpritePatadonSaltando;
	SDL_Rect  *gSpritePatadaAgachado;
	SDL_Rect  *gSpritePatadonAgachado;
	//piñas
	SDL_Rect  *gSpritePinia;
	SDL_Rect  *gSpritePinion;
	SDL_Rect  *gSpritePiniaSaltando;
	SDL_Rect  *gSpritePinionSaltando;
	SDL_Rect  *gSpritePiniaAgachado;
	SDL_Rect  *gSpritePinionAgachado;
	SDL_Rect  *gSpriteDefensa;
	SDL_Rect  *gSpriteDefensaAgachado;
	SDL_Rect  *gSpriteDefensaSaltando;
	//defensa
	SDL_Rect  *gSpriteLanzarJugador;
	SDL_Rect  *gSpriteJugadorLanzado;
	SDL_Rect  *gSpriteLanzarPoder;
	SDL_Rect  *gSpritePoder;
	SDL_Rect * gSpriteTomado;
	//poder especial
	SDL_Rect  *gSpritePoderEspecial;
	//danio
	SDL_Rect  *gSpriteRecibirDanio;
	SDL_Rect * gSprite;
	int contador = 0;

	int CANTSPRITECLIP;
	int CANTSPRITECLIPCAMINA;
	int MINFRAMECAMINA;
	int MAXFRAMECAMINA;
	int FACTORCAMINA;
	int CANTSPRITECLIPSALTA;
	int MINFRAMESALTA;
	int MAXFRAMESALTA;
	int FACTORSALTA;
	int CANTSPRITEANIMACION;
	int MINFRAMEANIMACION;
	int MAXFRAMEANIMACION;
	int FACTORANIMACION;
	int CANTSPRITECLIPDEFENSA;
	int MINFRAMEDEFENSA;
	int MAXFRAMEDEFENSA;
	int FACTORDEFENSA;

	//patadas
	int CANTSPRITECLIPPATADON;
	int MINFRAMEPATADON;
	int MAXFRAMEPATADON;
	int FACTORPATADON;
	int CANTSPRITECLIPPATADA;
	int MINFRAMEPATADA;
	int MAXFRAMEPATADA;
	int FACTORPATADA;
	int CANTSPRITECLIPPATADASALTANDO;
	int MAXFRAMEPATADASALTANDO;
	int MINFRAMEPATADASALTANDO;
	int FACTORPATADASALTANDO;
	int CANTSPRITECLIPPATADONSALTANDO;
	int MINFRAMEPATADONSALTANDO;
	int MAXFRAMEPATADONSALTANDO;
	int FACTORPATADONSALTANDO;
	int CANTSPRITECLIPPATADAAGACHADO;
	int MINFRAMEPATADAAGACHADO;
	int MAXFRAMEPATADAAGACHADO;
	int FACTORPATADAAGACHADO;
	int CANTSPRITECLIPPATADONAGACHADO;
	int MINFRAMEPATADONAGACHADO;
	int MAXFRAMEPATADONAGACHADO;
	int FACTORPATADONAGACHADO;
	//piñas
	int CANTSPRITECLIPPINIA;
	int MINFRAMEPINIA;
	int MAXFRAMEPINIA;
	int FACTORPINIA;
	int CANTSPRITECLIPPINION;
	int MINFRAMEPINION;
	int MAXFRAMEPINION;
	int FACTORPINION;

	int CANTSPRITECLIPPINIASALTANDO;
	int MINFRAMEPINIASALTANDO;
	int MAXFRAMEPINIASALTANDO;
	int FACTORPINIASALTANDO;

	int CANTSPRITECLIPPINIONSALTANDO;
	int MINFRAMEPINIONSALTANDO;
	int MAXFRAMEPINIONSALTANDO;
	int FACTORPINIONSALTANDO;
	int CANTSPRITECLIPPINIONAGACHADO;
	int MINFRAMEPINIONAGACHADO;
	int MAXFRAMEPINIONAGACHADO;
	int FACTORPINIONAGACHADO;
	int CANTSPRITECLIPPINIAAGACHADO;
	int MINFRAMEPINIAAGACHADO;
	int MAXFRAMEPINIAAGACHADO;
	int FACTORPINIAAGACHADO;

//	int CANTSPRITECLIPPINIAAGACHADO;
//	int MINFRAMEPINIAAGACHADO;
//	int MAXFRAMEPINIAAGACHADO;
//	int FACTORPINIAAGACHADO;
//
//	int CANTSPRITECLIPPINIONAGACHADO;
//	int MINFRAMEPINIONAGACHADO;
//	int MAXFRAMEPINIONAGACHADO;
//	int FACTORPINIONAGACHADO;
//
//	int CANTSPRITECLIPDEFENSA;
//	int MINFRAMEDEFENSA;
//	int MAXFRAMEDEFENSA;
//	int FACTORDEFENSA;

	int CANTSPRITECLIPDEFENSAAGACHADO;
	int MINFRAMEDEFENSAAGACHADO;
	int MAXFRAMEDEFENSAAGACHADO;
	int FACTORDEFENSAAGACHADO;

	int CANTSPRITECLIPDEFENSASALTANDO;
	int MINFRAMEDEFENSASALTANDO;
	int MAXFRAMEDEFENSASALTANDO;
	int FACTORDEFENSASALTANDO;

	int CANTSPRITECLIPRECIBIRGOLPE;
	int MINFRAMERECIBIRGOLPE;
	int MAXFRAMERECIBIRGOLPE;
	int FACTORRECIBIRGOLPE;

	//Especiales
	int CANTSPRITECLIPLANZARJUGADOR;
	int MINFRAMELANZARJUGADOR;
	int MAXFRAMELANZARJUGADOR;
	int FACTORLANZARJUGADOR;

	int CANTSPRITECLIPJUGADORLANZADO;
	int MINFRAMEJUGADORLANZADO;
	int MAXFRAMEJUGADORLANZADO;
	int FACTORJUGADORLANZADO;

	int CANTSPRITECLIPLANZARPODER;
	int MINFRAMELANZARPODER;
	int MAXFRAMELANZARPODER;
	int FACTORLANZARPODER;

	int CANTSPRITECLIPPODER_especial;
	int MINFRAMEPODER_especial;
	int MAXFRAMEPODER_especial;
	int FACTORPODER_especial;

	int CANTSPRITECLIPPODER;
	int MINFRAMEPODER;
	int MAXFRAMEPODER;
	int FACTORPODER;


	int CANTSPRITECLIPTOMADO;
	int MINFRAMETOMADO;
	int MAXFRAMETOMADO;
	int FACTORTOMADO;

	bool silencio=false;
	bool sonido_defensa_reproducido=false;
	int maxFrame;
	int factor;

	bool sonido_KO_reproducido=false;
	EfectoSonido *sonido_KO;
	void reproducir_sonido_KO();
	virtual void reproducir_sonido_salto(){};
	virtual void reproducir_sonido_cambio(){};
	virtual void reproducir_sonido_ataque_pu(){};
	virtual void reproducir_sonido_defensa(){};
	virtual void reproducir_sonido_ataque_patada(){};
	virtual void reproducir_sonido_recibir_danio(){};
	virtual void reproducir_sonido_poder(){};
	virtual void reproducir_sonido_agarre(){};
	void silenciar_efectos();


	void reproducir_efecto_sonido(int tipo_golpe);



protected:

	LTexture * texturaJugador;
	int frame = 0;
	int framePoder = 0;
	SDL_RendererFlip direccion;
	void getSpritesCaminar();
	int zIndex;
};

#endif
