#ifndef VIEW_JUGADOR_SPIDERMANBLACK_H_
#define VIEW_JUGADOR_SPIDERMANBLACK_H_
#include <SDL2/SDL.h>
#include "../View/View_Jugador_Spiderman.h"

class View_Jugador_SpidermanBlack: public View_Jugador_Spiderman { // @suppress("Class has a virtual method and non-virtual destructor")
public:
	View_Jugador_SpidermanBlack();
	void initialize(Jugador *model,
		LTexture * texturaJugador);
	//virtual ~ View_Jugador_SpidermanBlack();

};
#endif
