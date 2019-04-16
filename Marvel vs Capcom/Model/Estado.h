#ifndef ESTADO_H
#define ESTADO_H

#define VELOCIDAD_NORMAL 3
#define VELOCIDAD_ACELERACION 2

class Estado {
public:
	Estado();
	virtual ~Estado();
	int getPosX();
	int getPosY();
	int getVelX();
	int getVelY();
	void setPosX(int PosX);
	void setPosY(int PosY);
	void setPosInitX(int posX);
	void setPosInitY(int posY);
	void copiarEstado(Estado* estado);
	void disminuirVelocidadX();
	void disminuirVelocidadY();
	void Agachar();
	void aumentarVelocidadX();
	void aumentarVelocidadY();
	void Saltar();
	void detenerVelocidad();
	virtual void move() = 0;
	virtual bool estaActivo() = 0;
	int getAceleracion();
	void desacelerar();
	bool getAcelero();
	void setVelocidadX(int velx);
	void setVelocidadY(int vely);
	void setAceleracion(int ac);
	void aumentarVelocidadX(int vel);
	bool isCambiandoJugador();
	void setCambiandoPersonaje(bool cambiandoPersonaje);
	virtual bool isFueraDePantalla();

protected:
	int mPosX, mPosY;
	int posInitX, posInitY;
	int mVelX, mVelY;
	int aceleracion;
	bool acelero;
	bool cambiandoPersonaje;

private:
};

#endif // ESTADO_H
