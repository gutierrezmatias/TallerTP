#ifndef COMMAND_H
#define COMMAND_H
#define DECVELX 0x00
#define DECVELY 0x01
#define INCVELX 0x02
#define INCVELY 0x03
#define AGACHAR 0x04
#define SALTAR  0x05
#define CAMBIAR_PERSONAJE  0x06
#define PARAR  0x07
#define PINIA  0x08
#define PINION  0x09
#define PATADA  0x10
#define PATADON  0x11
#define DEFENSA 0x12
#define CANTCOMMANDS 13

class Command {
public:
	Command();
	virtual ~Command();
	virtual void execute(int i) = 0;
protected:
private:
};
#endif // COMMAND_H
