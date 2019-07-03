#include "Model_Jugador.h"
# include "../Logger/Logger.h"
#define MARGENDESELECCION 20
/*
 Jugador::Jugador() {

<<<<<<< Upstream, based on origin/develop-parte-3-mergeado
 }*/

Jugador::Jugador(int &ancho, int &alto, int &zind,std::string &nom,std::string &path, bool &inmortal) {
//	this->estado->setPosInitY(0);

	int reduccion=0;
	if (ancho==430){
		reduccion=20;
	}
	extension_colider_golpe=(ancho -400)*1.2+40-reduccion/2;

	this->estado = &(this->inactivo);
	this->mCollider.x = this->estado->getPosX();
	this->mCollider.y = this->estado->getPosY();

	this->direccion = SDL_FLIP_NONE;
	this->personaje = 0;


	this->width=ancho;
	this->height=alto;
	this->zindex= zind;
	this->nombre=nom;
	this->pathImagen=path;
	this->mCollider.w =110 +(ancho -400) -reduccion;

	this->mCollider.h = 100 ;

	mColliderOffsetX = (ancho - mCollider.w)/2;
	mColliderOffsetY = alto - mCollider.h;

	this->vidaJugador = 100;
	this->inmortal = inmortal;

}
void Jugador::SetVida(int vida) {
	this->vidaJugador = vida;
}
int Jugador::GetVida() {
	return this->vidaJugador;
}
int Jugador::getPosXPoder() {
	return mipoder.getPosX();
}
int Jugador::getPosYPoder() {
	return mipoder.getPosY();
}
int Jugador::getSentidoPoder() {
	return mipoder.getSentido();
}
void Jugador::setPosYPoder(int y) {
	mipoder.setPosY(y);
}
void Jugador::setPosXPoder(int x) {
	mipoder.setPosX(x);
}
void Jugador::setSentidoPoder(int z) {
	mipoder.setSentido(z);
}
bool Jugador::poderActivo() {
	return mipoder.estaActivo();
}
void Jugador::setEstadoPoder(bool estado) {
	mipoder.setInactivo();
	if (estado)
		mipoder.setActivo();

}
int Jugador::get_alto() {

	return height;
}
int Jugador::get_ancho() {
	return width;

}
int Jugador::get_zindex() {
	return zindex;
}

int Jugador::getCollideX() {
	return this->mCollider.x;
}
int Jugador::getCollideY() {
	return this->mCollider.y;
}
int Jugador::getCollideW() {
	return this->mCollider.w;
}
int Jugador::getCollideH() {
	return this->mCollider.h;
}

int Jugador::setCollideX(int collPosX) {
	 this->mCollider.x = collPosX;
}
int Jugador::setCollideY(int collPosY) {
	 this->mCollider.y = collPosY;
}
int Jugador::setCollideW(int collPosW) {
	 this->mCollider.w = collPosW;
}
int Jugador::setCollideH(int collPosH) {
	 this->mCollider.h = collPosH;
}
bool Jugador::collideConPoder(Poder * poder) {
	return poder->colision(this->getCollideX(), this->getCollideY(),
			this->getCollideW()+this->getCollideX(), this->getCollideH() +this->getCollideY());
}
std::string Jugador::getNombre() {

	return nombre;
}
std::string Jugador::getPathImagen() {
	return pathImagen;

}

void Jugador::setPosInitX(int posX) {
	this->estado->setPosInitX(posX);

}

void Jugador::setPosInitY(int posY) {
	this->estado->setPosInitY(posY);
}

void Jugador::setDireccion(SDL_RendererFlip direccion) {
	Logger::Log(DEBUG, "Jugador:: setea la direccion ", "");
	this->direccion = direccion;
}

void Jugador::move(Jugador* jugadorRival, SDL_Rect* camara) {

	int nuevaposX;
	int nuevaposY;

	jugadorVolando();
//	if ((this->murio()) && (!jugadorRival->murio())){
//
//		this->cambiarPersonaje();
//	}

//	if (this->estaActivo()){
//	cout<<"=========================================" <<endl;
//	cout<<"colider x: "<<this->mCollider.x <<endl;
//	cout<<"colider y: "<<this->mCollider.y <<endl;
//	cout<<"colider h: "<<this->mCollider.h <<endl;
//	cout<<"colider w: "<<this->mCollider.w <<endl;
//	cout<<"pos x: "<<this->estado->getPosX()<<endl;
//	cout<<"pos y: "<<this->estado->getPosY()<<endl;
//	cout<<"colliderOfsetX: "<< mColliderOffsetX <<endl;
//	cout<<"colliderOfsetY: "<< mColliderOffsetY <<endl;
//	cout<<"camara X IZQ: "<< camara->x << endl;
//	cout<<"camara X DER: "<< camara->x + camara->w << endl;
//	cout<<"========================================="<<endl;
//	}

	int distancia_jugadores= abs(this->estado->getPosX()-jugadorRival->estado->getPosX());
	if (this->estado->estaCambiandoPersonaje()&& !jugadorRival->murio()) {
		this->estado->move();

	}
//	else if(this->estado->getPosX()>jugadorRival->estado->getPosX() && this->estado->getVelX()>0 && distancia_jugadores>600 )
//	{
//
//
//		cout<<" No te vayas!!!!!!"<<endl;
//		nuevaposX=this->estado->getPosX()-this->estado->getVelX();
//		//nuevaposX=this->estado->getPosX();
//		this->estado->setPosX(nuevaposX);
//		this->estado->move();
//
//
//	}else if(this->estado->getPosX()<jugadorRival->estado->getPosX() && this->estado->getVelX()<0 && distancia_jugadores>600 ){
//
//
//		cout<<" No te vayas!!!!!!"<<endl;
//		nuevaposX=this->estado->getPosX()-this->estado->getVelX();
//		//nuevaposX=this->estado->getPosX();
//		this->estado->setPosX(nuevaposX);
//		this->estado->move();
//	}
	else if(collideConJugador(&(jugadorRival->mCollider))){

		cout<<"Hay coliisiooooonnn!!!!$%$%#%#$%#$%$#$%$#$" << endl;
//Move back
		if(this->mCollider.x <= jugadorRival->mCollider.x){
//			if((this->estado->getVelY()!=0) && (!collideDerecha(camara)) && (!collideIzquierda(camara)))
			if((this->getVelY() < 0) && collideVertical(&this->mCollider, &jugadorRival->mCollider)){
				if (hayLugarAIzquierda(this, jugadorRival, camara))
					nuevaposX= jugadorRival->mCollider.x - this->mCollider.w - mColliderOffsetX - 10;
				else
					nuevaposX= jugadorRival->mCollider.x + jugadorRival->mCollider.w - mColliderOffsetX +10;
			}
//			else if((this->estado->getVelY() < 0) && (collideDerecha(camara)) && (!collideIzquierda(camara)))
//							nuevaposX= this->estado->getPosX() -100;
//			else if((this->estado->getVelY()!=0) && (collideIzquierda(camara)))
//									nuevaposX= this->estado->getPosX() +100;
			else if(this->estado->getVelX() >= 0)
				nuevaposX= this->estado->getPosX() -this->estado->getVelX();
			else
				nuevaposX= this->estado->getPosX() +this->estado->getVelX() ;

		}else{
			if ((this->getVelY() < 0)  && collideVertical(&this->mCollider, &jugadorRival->mCollider)) {
				if (hayLugarADerecha(this, jugadorRival, camara))
					nuevaposX = jugadorRival->mCollider.x + jugadorRival->mCollider.w - mColliderOffsetX + 10;
				else
					nuevaposX = jugadorRival->mCollider.x - this->mCollider.w - mColliderOffsetX - 10;
			}
//			else if((this->estado->getVelY()!=0) && (collideIzquierda(camara)))
//				nuevaposX= this->estado->getPosX() +100;
			else if(this->estado->getVelX() >= 0)
				nuevaposX= this->estado->getPosX() +this->estado->getVelX();
			else
				nuevaposX= this->estado->getPosX() -this->estado->getVelX();

		}


		nuevaposY= this->estado->getPosY();
		this->estado->setPosX( nuevaposX);
		this->estado->setPosY( nuevaposY);
		this->estado->move();


	} else if (movimientoDerecha()) {


		if (!collideDerecha(camara)) {
			cout << "Mov derecha: " << endl;
			this->estado->move();
		} else {
			if (!jugadorRival->collideIzquierda(camara)) {
				this->estado->move();
			} else {
				this->estado->moveVertical();
			}
		}
	} else if (movimientoIzquierda()) {
		if (!collideIzquierda(camara)) {
			this->estado->move();
		} else {
			if (!jugadorRival->collideDerecha(camara)) {
				this->estado->move();
			} else {
				this->estado->moveVertical();
			}
		}
	} else {
		this->estado->move();
	}
	updateDirection(*jugadorRival);
	this->mCollider.x = this->estado->getPosX() + mColliderOffsetX;
	this->mCollider.y = this->estado->getPosY() + mColliderOffsetY;




	//aca iria el contador
//	if (this->getTipoGolpe() == TIPO_GOLPE::GOLPE_ARROJAR)
//				this->setTipoGolpe(TIPO_GOLPE::NADA);
//	if (this->getTipoGolpe() == TIPO_GOLPE::GOLPE_PODER)
//				this->setTipoGolpe(TIPO_GOLPE::NADA);
	if (jugadorRival->collideConPoder(&mipoder)){
				jugadorRival->recibeDanio(10);
	}
}

bool Jugador::hayLugarADerecha(Jugador* jugador, Jugador* jugadorRival, SDL_Rect* camara){
	// el "1040" es el ANCHO_NIVEL
	int bordeDerCamara = 1040;
//	int bordeDerechoRival = jugadorRival->mCollider.x + jugadorRival->mCollider.w;
	int bordeDerechoRival = jugadorRival->mCollider.x + jugadorRival->mCollider.w;

	return (bordeDerCamara - bordeDerechoRival) > jugador->mCollider.w;
}

bool Jugador::hayLugarAIzquierda(Jugador* jugador, Jugador* jugadorRival, SDL_Rect* camara){
	// el "0" es el mínima posicion del escenario
	int bordeIzqCamara = 0;
	int bordeIzqRival = jugadorRival->mCollider.x;

	return (bordeIzqRival - bordeIzqCamara) > jugador->mCollider.w;
}

bool Jugador::collideVertical(SDL_Rect* camJugador, SDL_Rect* camJugadorRival){
	int pisoJugador = camJugador->y + camJugador->h;
	int techoRival = camJugadorRival->y;

	std::cout << "pisoJugador: " << pisoJugador << std::endl;
	std::cout << "techoRival: " << techoRival << std::endl;
// sumo 30 porque el salto va a actializando los valores de Y del personaje en +/- 20 pixeles
	if (pisoJugador > techoRival - 30){
		std::cout << "Collide verticaaaaaaalllll CARAJOOOOOOOO ################!!!!" << std::endl;
		if (camJugador->x < camJugadorRival->x){
			if (camJugador->x + camJugador->w > camJugadorRival->x)
				std::cout << "Collide verticaaaaaaalllll por IZQUIERDAA!!!!" << std::endl;
				return true;
		}
		else if (camJugador->x > camJugadorRival->x){
			if (camJugadorRival->x + camJugadorRival->w > camJugador->x)
				std::cout << "Collide verticaaaaaaalllll por DERECHAAAAA!!!!" << std::endl;
				return true;
		}
		else{
			std::cout << "Collide verticaaaaaaalllll por CENTROOO!!!!" << std::endl;
			return true;
		}
	}
	return false;
}

int Jugador::getPosX() {
	return this->estado->getPosX();
}

int Jugador::getPosY() {
	return this->estado->getPosY();
}

void Jugador::setPosX(int PosX) {
	this->estado->setPosX(PosX);
}

void Jugador::setPosY(int PosY) {
	this->estado->setPosY(PosY);
}

void Jugador::disminuirVelocidadX() {
	this->estado->disminuirVelocidadX();
}
void Jugador::disminuirVelocidadY() {
	this->estado->disminuirVelocidadY();
}

void Jugador::cambiarPersonaje() {
	if (this->estado->getVelY() == 0) {
		this->estado->aumentarVelocidadY(20);
		this->cambiandoPersonaje.copiarEstadoCambiarPersonaje(this->estado);
		this->estado = &(this->cambiandoPersonaje);
		mipoder.setInactivo();
	}
}

void Jugador::Agachar() {
	if (this->estado->getVelY() == 0) {
		this->agachado.copiarEstadoAgachar(this->estado);
		this->estado = &(this->agachado);
		this->tipoGolpe = TIPO_GOLPE::NADA;
	}
}
void Jugador::Parar() {
	if (this->estado->estaAgachado()) {
		this->activo.copiarEstadoAgachar(this->estado);
		this->estado = &(this->activo);
		this->tipoGolpe = TIPO_GOLPE::NADA;
	}
}

void Jugador::aumentarVelocidadX() {
	this->estado->aumentarVelocidadX();
}

void Jugador::aumentarVelocidadX(int vel) {
	this->estado->aumentarVelocidadX(vel);
}

void Jugador::aumentarVelocidadY() {
	this->estado->aumentarVelocidadY();
}

void Jugador::aumentarVelocidadY(int vel) {
	this->estado->aumentarVelocidadY(vel);
}


void Jugador::Pinia(Jugador * rival) {
	if ((this->getTipoGolpe() == TIPO_GOLPE::NADA)
			&& (this->estado->getVelY() > -10)) {
		std::cout << "Agregar PINIA!!!!!: " << std::endl;
		this->setTipoGolpe(TIPO_GOLPE::GOLPE_PINIA);
	}

		if (this->collideConGolpe(&(rival->mCollider),1.2))
		rival->recibeDanio(this->estado->getDanioPinia());
}

void Jugador::Pinion(Jugador * rival) {
//	this->estado->Pinion();
	if (this->getTipoGolpe() == TIPO_GOLPE::NADA) {

		this->setTipoGolpe(TIPO_GOLPE::GOLPE_PINION);
	}

		if (collideConGolpe(&(rival->mCollider),1.1))
		rival->recibeDanio(this->estado->getDanioPinion());

}

void Jugador::Patada(Jugador * rival) {
	if ((this->getTipoGolpe() == TIPO_GOLPE::NADA)
			&& (this->estado->getVelY() > -10)) {
		std::cout << "Agregar PATADA!!!!!: " << std::endl;
		this->setTipoGolpe(TIPO_GOLPE::GOLPE_PATADA);
	}

		if (collideConGolpe(&(rival->mCollider),1.4))
		rival->recibeDanio(this->estado->getDanioPatada());
}
void Jugador::Arrojar(Jugador * rival) {
	if (this->getTipoGolpe() == TIPO_GOLPE::NADA) {
		this->estado->Arrojar();
		std::cout << "ARROJJAAAAAAARRRRRR!!!!!: " << std::endl;
		this->setTipoGolpe(TIPO_GOLPE::GOLPE_ARROJAR);

		int i = -1;
		if (this->getDireccion() == SDL_FLIP_NONE)
			i = 1;

		if ((rival->collideConJugador(&mCollider))
				&& (rival->getTipoGolpe() == TIPO_GOLPE::NADA)) {
			std::cout << "VOLANDOOOOOOOOOO!!!!!: " << std::endl;
			rival->estado->setVelocidadX(20 * i);
			rival->estado->setVelocidadY(20);
			rival->setTipoGolpe(TIPO_GOLPE::GOLPE_VOLAR);
			rival->recibeDanio(this->estado->getDanioArrojar());
		}
	}
}

void Jugador::Patadon(Jugador * rival) {
	if ((this->getTipoGolpe() == TIPO_GOLPE::NADA)
			&& (this->estado->getVelY() > -10)) {
		std::cout << "Agregar PATADON!!!!!: " << std::endl;
		this->setTipoGolpe(TIPO_GOLPE::GOLPE_PATADON);
	}
	//if (rival->collideConJugador(&mCollider))
		if (collideConGolpe(&(rival->mCollider),1.3))
		rival->recibeDanio(this->estado->getDanioPatadon());
}

void Jugador::ActivarDefensa() {
	std::cout << "Agregar DEFENSAAAAAAAAAAAA!!!!!: " << std::endl;
//	if(!this->estado->estaSaltando())
	this->setTipoGolpe(TIPO_GOLPE::ACTIVAR_DEFENSA);
}

void Jugador::DesactivarDefensa() {
	std::cout << "Terminar DEFENSAAAAAAAAAAAA!!!!!: " << std::endl;
	this->setTipoGolpe(TIPO_GOLPE::DESACTIVAR_DEFENSA);
}


void Jugador::TirarPoder(Jugador * rival) {
	if(!this->mipoder.estaActivo()){
		this->estado->TirarPoder();
	if (this->getTipoGolpe() == TIPO_GOLPE::NADA) {

		this->setTipoGolpe(TIPO_GOLPE::GOLPE_PODER);
	}
	if (this->getDireccion() == SDL_FLIP_NONE) {
		mipoder.activarPoder(this->getPosX(), this->getPosY() , 1);
	} else {
		mipoder.activarPoder(this->getPosX(), this->getPosY(), -1);
	}
	std::cout << "HADOOOOUUUUKENNNNNN" << std::endl;
	std::cout << "HADOOOOUUUUKENNNNNN" << std::endl;
	std::cout << "HADOOOOUUUUKENNNNNN" << std::endl;
	}

}

void Jugador::recibeDanio(int danio) {
	if (this->getTipoGolpe() == TIPO_GOLPE::ACTIVAR_DEFENSA){
		danio=danio*0.2; // si esta activada la defensa el danio es el 20 %
	}

	if (this->vidaJugador - danio > 0) {
		this->vidaJugador = this->vidaJugador - danio;
	}else{
		this->vidaJugador =0;
	}

		if ((this->getTipoGolpe()) == !(TIPO_GOLPE::GOLPE_VOLAR)) {
			this->setTipoGolpe(TIPO_GOLPE::RECIBIR_DANIO);
			std::cout << "me pegaron!!!" << endl;
		}

	//std::cout << "me pego y mi vida es : " + std::to_string(this->vidaJugador) << std::endl;
}

void Jugador::Saltar() {
//	this->estado->Saltar();

	if(!this->estado->estaSaltando()){
		this->estado->setVelocidadY(25);

		this->saltando.copiarEstado(this->estado);
		this->estado = &(this->saltando);
		this->tipoGolpe = TIPO_GOLPE::NADA;
	}

}

int Jugador::getVelX() {
	return this->estado->getVelX();
}

int Jugador::getVelY() {
	return this->estado->getVelY();
}
void Jugador::set_desconectado() {
	this->desconectado = true;

}
void Jugador::set_conectado() {
	this->desconectado = false;

}
bool Jugador::get_estado_desconexion() {

	return desconectado;
}
void Jugador::detenerVelocidad() {
	this->estado->detenerVelocidad();
}
bool Jugador::estaActivo() {
	return this->estado->estaActivo();
}
bool Jugador::estaAgachado() {
	return this->estado->estaAgachado();
}
bool Jugador::estaCambiandoPersonaje() {
	return this->estado->estaCambiandoPersonaje();
}
bool Jugador::estaSaltando() {
	return this->estado->estaSaltando();
}
void Jugador::activar() {
	this->activo.copiarEstado(this->estado);
	this->estado = &(this->activo);
	this->detenerVelocidad();
	this->tipoGolpe = TIPO_GOLPE::NADA;
}
void Jugador::desactivar() {
	this->inactivo.copiarEstado(this->estado);
	this->estado = &(this->inactivo);
	this->detenerVelocidad();
	this->tipoGolpe = TIPO_GOLPE::NADA;
}
void Jugador::terminarSalto() {
	this->activo.copiarEstado(this->estado);
	this->estado = &(this->activo);
	this->tipoGolpe = TIPO_GOLPE::NADA;
}
bool Jugador::collide(SDL_Rect * camara) {

	int leftCam, leftJugador;
	int rightCam, rightJugador;
	int topCam, topJugador;
	int bottomCam, bottomJugador;

	leftCam = camara->x + MARGENDESELECCION;

	rightCam = camara->x + camara->w - MARGENDESELECCION;

	topCam = camara->y + MARGENDESELECCION;

	bottomCam = camara->y + camara->h - MARGENDESELECCION;

	leftJugador = this->mCollider.x;
	rightJugador = this->mCollider.x + this->mCollider.w;
	topJugador = this->mCollider.y;
	bottomJugador = this->mCollider.y + this->mCollider.h;

//	if (bottomJugador <= topCam) {
//		return false;
//	}
//
//	if (topJugador >= bottomCam) {
//		return false;
//	}

	if (leftJugador >= leftCam) {
		return false;
	}

	if (rightJugador <= rightCam) {
		return false;
	}

	return true;
}

bool Jugador::collideConJugador(SDL_Rect * rival) {

	int leftRival, leftJugador;
	int rightRival, rightJugador;
	int topRival, topJugador;
	int bottomRival, bottomJugador;

	leftRival = rival->x;

	rightRival = rival->x + rival->w;

	topRival = rival->y;

	bottomRival = rival->y + rival->h;
	cout<<"================================" <<endl;
	cout<<"colider x: "<<this->mCollider.x <<endl;
	cout<<"colider y: "<<this->mCollider.y <<endl;
	cout<<"colider h: "<<this->mCollider.h <<endl;
	cout<<"colider w: "<<this->mCollider.w <<endl;
	cout<<"================================" <<endl;
	cout<<"rival x: "<<rival->x <<endl;
	cout<<"rival y: "<<rival->y <<endl;
	cout<<"rival h: "<<rival->h <<endl;
	cout<<"rival w: "<<rival->w <<endl;
	cout<<"================================" <<endl;
	leftJugador = this->mCollider.x;
	rightJugador = this->mCollider.x + this->mCollider.w;
	topJugador = this->mCollider.y;
	bottomJugador = this->mCollider.y + this->mCollider.h;

	if (bottomJugador < topRival) {
		return false;
	}
	if (bottomJugador == topRival) {
		return collideVertical(&this->mCollider, rival);
	}

//	if (topJugador >= bottomRival) {
//		return false;
//	}

	if (leftJugador > rightRival) {
		return false;
	}

	if (rightJugador < leftRival) {
		return false;
	}
	cout<<"Hay coliision por descarte" << endl;
	return true;
}
bool Jugador::collideConGolpe(SDL_Rect * jugador, int factor_golpe) {

	int leftRival, leftJugador;
	int rightRival, rightJugador;
	int topRival, topJugador;
	int bottomRival, bottomJugador;

	leftRival = jugador->x;

	rightRival = jugador->x + jugador->w ;

	topRival = jugador->y;

	bottomRival = jugador->y + jugador->h;

	leftJugador = this->mCollider.x- extension_colider_golpe*factor_golpe;
	rightJugador = this->mCollider.x + this->mCollider.w + extension_colider_golpe*factor_golpe;
	topJugador = this->mCollider.y;
	bottomJugador = this->mCollider.y + this->mCollider.h;

	if (bottomJugador <= topRival) {
		return false;
	}

	if (topJugador >= bottomRival) {
		return false;
	}

	if (leftJugador >= rightRival) {
		return false;
	}

	if (rightJugador <= leftRival) {
		return false;
	}

	return true;
}

bool Jugador::collideDerecha(SDL_Rect * camara) {

	int leftCam, leftJugador;
	int rightCam, rightJugador;
	int topCam, topJugador;
	int bottomCam, bottomJugador;

	leftCam = camara->x + MARGENDESELECCION;
	rightCam = camara->x + camara->w - MARGENDESELECCION;
	topCam = camara->y + MARGENDESELECCION;
	bottomCam = camara->y + camara->h - MARGENDESELECCION;

	leftJugador = this->mCollider.x;
	rightJugador = this->mCollider.x + this->mCollider.w+10;
	topJugador = this->mCollider.y;
	bottomJugador = this->mCollider.y + this->mCollider.h;

	if (rightJugador >= rightCam) {
		return true;
	}

	return false;
}

bool Jugador::collideIzquierda(SDL_Rect * camara) {

	int leftCam, leftJugador;
	int rightCam, rightJugador;
	int topCam, topJugador;
	int bottomCam, bottomJugador;

	leftCam = camara->x + MARGENDESELECCION;

	rightCam = camara->x + camara->w - MARGENDESELECCION ;

	topCam = camara->y + MARGENDESELECCION;

	bottomCam = camara->y + camara->h - MARGENDESELECCION;

	leftJugador = this->mCollider.x;
	rightJugador = this->mCollider.x + this->mCollider.w;
	topJugador = this->mCollider.y;
	bottomJugador = this->mCollider.y + this->mCollider.h;

	if (leftJugador <= leftCam) {

		return true;
	}

	return false;
}

SDL_RendererFlip Jugador::getDireccion() {
	return this->direccion;
}

void Jugador::updateDirection(Jugador &oponente) {

	if (this->estado->getVelX() > 0) {
		direccion = SDL_FLIP_NONE;
	} else if (this->estado->getVelX() < 0) {
		direccion = SDL_FLIP_HORIZONTAL;
	} else if (this->getPosX() > oponente.getPosX()) {
		direccion = SDL_FLIP_HORIZONTAL;
	} else {
		direccion = SDL_FLIP_NONE;
	}

}
int Jugador::Personaje() {
	return this->personaje;
}
void Jugador::setPersonaje(int p) {
	this->personaje = p;
}

bool Jugador::isFueraDePantalla() {
	return this->estado->isFueraDePantalla();
}

bool Jugador::movimientoDerecha() {
	return (this->estado->getVelX() > 0);
}

bool Jugador::movimientoIzquierda() {
	return (this->estado->getVelX() < 0);
}

void Jugador::setColor(int red, int green, int blue) {
	this->r = red;
	this->g = green;
	this->b = blue;
}

int Jugador::getR() {
	return r;
}
int Jugador::getG() {
	return g;
}
int Jugador::getB() {
	return b;
}
bool Jugador::isDebeTerminarSalto() {
	return debeTerminarSalto;
}

void Jugador::setDebeTerminarSalto(bool debeTerminarSalto) {
	this->debeTerminarSalto = debeTerminarSalto;
}
bool Jugador::isIniciarGolpe() {
	return this->iniciarGolpe;
}
void Jugador::setIniciarGolpe(bool iniciarGolpe) {
	this->iniciarGolpe = iniciarGolpe;
}
TIPO_GOLPE Jugador::getTipoGolpe() {
	return this->tipoGolpe;
}
void Jugador::setTipoGolpe(TIPO_GOLPE tipoGolpe) {
	this->tipoGolpe = tipoGolpe;
}
void Jugador::setTipoGolpeCliente(TIPO_GOLPE tipoGolpe) {
	if (tipoGolpe == TIPO_GOLPE::DESACTIVAR_DEFENSA) {
		std::cout << "Defensa terminadaa##############" << std::endl;
		this->tipoGolpe = TIPO_GOLPE::NADA;
	} else
		this->tipoGolpe = tipoGolpe;
}
bool Jugador::murio() {
	if (this->esInmortal()) {
		return false;
	} else {
		return this->vidaJugador == 0;
	}
}
bool Jugador::estaVivo() {
	return !this->murio();
}

void Jugador::inicializarVida() {
	this->vidaJugador = 100;
}
bool Jugador::esInmortal() {
	return this->inmortal;
}

void Jugador::setEsInmortal(bool valor) {
	this->inmortal = valor;
}

void Jugador::jugadorVolando() {
	if ((this->getTipoGolpe() == TIPO_GOLPE::GOLPE_VOLAR)) {
		if (this->estado->getVelX() != 0) {
			if (this->estado->getVelX() > 0)
				this->estado->setVelocidadX(this->estado->getVelX() - 1);
			if (this->estado->getVelX() < 0)
				this->estado->setVelocidadX(this->estado->getVelX() + 1);
		}
		if (this->estado->getVelX() == 0) {
			this->setTipoGolpe(TIPO_GOLPE::NADA);
		}

	}
}
