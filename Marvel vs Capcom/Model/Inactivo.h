#ifndef INACTIVO_H
#define INACTIVO_H
#include "Estado.h"
class Inactivo: public Estado {
public:
	Inactivo();
	virtual ~Inactivo();
	void move();
	bool estaActivo();
	void acelerar();
	bool isFueraDePantalla();
protected:
private:
};
#endif // INACTIVO_H
