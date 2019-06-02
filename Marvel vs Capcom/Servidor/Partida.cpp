#include "Partida.h"
#include <iostream>
void Partida::IniciarPartida() {
	//listaJugadores = listaEspera;
	//listaEspera.clear();
	modelo->inicializar();
	ActualizarModelo();
	modelo->getEquipoNro(0)->getJugadorActivo()->setPosX(120-80);
	modelo->getEquipoNro(0)->getJugadorActivo()->setPosY(931);
	modelo->getEquipoNro(1)->getJugadorActivo()->setPosX(780-80);
	modelo->getEquipoNro(1)->getJugadorActivo()->setPosY(931);
	int CAMARAPOSICIONINICIALX =ANCHO_NIVEL/2-modelo->ancho_Pantalla/2;
	int CAMARAPOSICIONINICIALY =ALTO_NIVEL/2-modelo->alto_Pantalla/2;
	camaraStatic = {CAMARAPOSICIONINICIALX,CAMARAPOSICIONINICIALY, modelo->ancho_Pantalla, modelo->alto_Pantalla};
	camara = &(camaraStatic);
	modelo->setCamara(this->camara);
	//	modelo->inicializarPosicionesEquipos();
	AjustarCamara();
	partidaIniciada = true;

}
void Partida::AjustarCamara(){
	// Este codigo se puede mejorar.
	int posXJugador1 = modelo->getEquipoNro(0)->getJugadorActivo()->getPosX();
	int posYJugador1 = modelo->getEquipoNro(0)->getJugadorActivo()->getPosY();
	int posXJugador2 = modelo->getEquipoNro(1)->getJugadorActivo()->getPosX();
	int posYJugador2 = modelo->getEquipoNro(1)->getJugadorActivo()->getPosY();
	//
	int anchoJugador1 = modelo->getEquipoNro(0)->getJugadorActivo()->get_ancho();

	int anchoJugador2 = modelo->getEquipoNro(1)->getJugadorActivo()->get_ancho();

	//Chequeo que los jugadores no se salgan del escenario
	if (posXJugador1 + anchoJugador1 > ANCHO_NIVEL)
		modelo->getEquipoNro(0)->getJugadorActivo()->setPosX(ANCHO_NIVEL - anchoJugador1);

	if (posXJugador2 + anchoJugador2 > ANCHO_NIVEL)
		modelo->getEquipoNro(1)->getJugadorActivo()->setPosX(ANCHO_NIVEL - anchoJugador2);

	if (posXJugador1 < 0) {
		modelo->getEquipoNro(0)->getJugadorActivo()->setPosX(0);
		posXJugador1 = 0;
	}
	if (posXJugador2 < 0) {
		modelo->getEquipoNro(1)->getJugadorActivo()->setPosX(0);
		posXJugador2 = 0;
	}

	//Muevo la cámara si algún jugador se está saliendo de ella
	if (posXJugador1 + anchoJugador1 > this->camara->x + this->camara->w)
		this->camara->x += modelo->getEquipoNro(0)->getJugadorActivo()->estado->getVelX();
	else if (posXJugador1 < this->camara->x)
		this->camara->x = posXJugador1;

	if (posXJugador2 + anchoJugador2 > this->camara->x + this->camara->w)
		this->camara->x += modelo->getEquipoNro(1)->getJugadorActivo()->estado->getVelX();
	else if (posXJugador2 < this->camara->x)
		this->camara->x = posXJugador2;

	//Keep the this->camara->in bounds
	if (this->camara->x < 0) {
		this->camara->x = 0;
	}
	if (this->camara->y < 0) {
		this->camara->y = 0;
	}
	if (this->camara->x > ANCHO_NIVEL - this->camara->w) {
		this->camara->x = ANCHO_NIVEL - this->camara->w;
	}
	if (this->camara->y > ALTO_NIVEL - this->camara->h) {
		this->camara->y = ALTO_NIVEL - this->camara->h;
	}
}

ModeloEstado  Partida::GetModeloEstado(){
	ModeloEstado unModelo;
	unModelo = modelo->GetModelEstado();
	//	unModelo.activoEquipo1 = GetTitularJugando(0).numeroJugador;
	//	unModelo.activoEquipo2 = GetTitularJugando(1).numeroJugador;
	unModelo.activoEquipo1 = modelo->equipos[0]->nroJugadorActivo;
	unModelo.activoEquipo2 = modelo->equipos[1]->nroJugadorActivo;
	return unModelo;
}
ModeloPersonajes Partida::GetModeloPersonajes(){
	ModeloPersonajes unModelo;
	list<int> idsPersonajes = this->modelo->GetIdsPersonajes();

	unModelo.cantidadPersonajes = idsPersonajes.size();

	list<int>::iterator itInt = idsPersonajes.begin();
	for (unsigned i = 0; i < idsPersonajes.size(); i++){
		advance(itInt, i);
		unModelo.idsPersonajes[i] = *itInt;
	}
	return unModelo;
}
ModeloSeleccion  Partida::GetModeloSeleccion(){
	ModeloSeleccion unModelo;
	unModelo.seleccionFinalizada = FinalizadaSeleccionPersonajes();
	unModelo.cantidadData = listaJugadores.size();
	list<ClienteConectado>::iterator it;
	for (int i = 0; i < listaJugadores.size(); i++) {

		ModeloSeleccionPersonaje unModeloSeleccionPersonaje;
		unModeloSeleccionPersonaje.personajeId = it->personajeId;
		unModeloSeleccionPersonaje.jugadorId = it->numeroJugador;
		unModeloSeleccionPersonaje.confirmado =  it->personajeConfirmado;

		switch(i){
			case 0:
				unModelo.jugadorA = unModeloSeleccionPersonaje;
				break;
			case 1:
				unModelo.jugadorB = unModeloSeleccionPersonaje;
				break;
			case 2:
				unModelo.jugadorC = unModeloSeleccionPersonaje;
				break;
			case 3:
				unModelo.jugadorD = unModeloSeleccionPersonaje;
				break;
		}
	}

	return unModelo;
}
void  Partida::SetJugadoresPersonajeInicial(){

	list<ClienteConectado>::iterator it;
	list<int> idsPersonajes = this->modelo->GetIdsPersonajes();
	int contador = 1;
	int cantidadPersonajes = idsPersonajes.size();

	for (it = listaJugadores.begin(); it != listaJugadores.end(); it++) {
		ModeloSeleccionPersonaje unModeloSeleccionPersonaje;

		list<int>::iterator itInt = idsPersonajes.begin();
		if(contador <= cantidadPersonajes){
			advance(itInt, contador  -1);
			it->personajeId = *itInt;
		}
		else{
			advance(itInt, cantidadPersonajes  -1);
			it->personajeId = *itInt;
		}
		contador = contador + 1;
	}
}
void Partida::ActualizarModelo() {
	list<ClienteConectado>::iterator it;
	for (it = listaJugadores.begin(); it != listaJugadores.end(); it++) {
		if (it->titular == true) {
			modelo->getEquipoNro(it->equipo)->setJugadorActivo(it->numeroJugador);
		}
	}

}
void Partida::SetComando(int equipo, int comando){
	if(comando != 99)
		controlador->SetComando(equipo, comando);
	modelo->update();
	AjustarCamara();

	cout << "Equipo 0 JugadorActivo: " << modelo->getEquipoNro(0)->nroJugadorActivo << endl;
	cout << "Equipo 1 JugadorActivo: " << modelo->getEquipoNro(1)->nroJugadorActivo << endl;
	cout << "Camara X: " << camara->x<< endl;
	cout << "Camara Y: " << camara->y<< endl;
	cout << "Equipo 0 - Pos x: " << modelo->getEquipoNro(0)->getJugadorActivo()->getPosX()<< endl;
	cout << "Equipo 0 - Pos y: " << modelo->getEquipoNro(0)->getJugadorActivo()->getPosY()<< endl;
	cout << "Equipo 1 - Pos x: " << modelo->getEquipoNro(1)->getJugadorActivo()->getPosX()<< endl;
	cout << "Equipo 1 - Pos y: " << modelo->getEquipoNro(1)->getJugadorActivo()->getPosY()<< endl;
	cout << "*****************************************************" << endl;



}
void Partida::SetModelo(Model* model) {
	modelo = model;
	controlador =  new Controller();
	controlador->SetModel(modelo);


}
Model * Partida::GetModelo(){
	return modelo;
}
Controller * Partida::GetControlador(){
	return controlador;
}
bool Partida::EquipoCompleto() {
	if (listaEspera.size() == maximoJugadores) {
		return true;
	}
	return false;
}
list<ClienteConectado> Partida::GetListaJugadores() {
	return listaJugadores;
}
list<ClienteConectado> Partida::GetListaEspera() {
	return listaEspera;
}
list<ClienteConectado> Partida::GetListaJugadores(int equipo) {
	ClienteConectado unCliente;
	list<ClienteConectado>::iterator it;
	list<ClienteConectado> listaTmp;
	for (it = listaJugadores.begin(); it != listaJugadores.end(); it++) {
		if (it->equipo == equipo) {
			listaTmp.push_back(*it);
		}
	}
	return listaTmp;
}
void Partida::FinalizarPartida() {
	partidaFinalizada = true;
}
bool Partida::Iniciada() {
	return partidaIniciada;
}
bool Partida::Finalizada() {
	return partidaFinalizada;
}
void Partida::SetMaximoJugadores(int max) {
	maximoJugadores = max;
}
void Partida::EliminarJugador(string nombre) {
	list<ClienteConectado>::iterator it;
	it = listaJugadores.begin();
	bool encontrado = false;
	while ((it != listaJugadores.end()) && !encontrado) {
		if (it->nombre == nombre) {
			listaJugadores.erase(it);
			encontrado = true;
		}
		it++;
	}
}
void Partida::EliminarDesconectado(string nombre) {
	list<ClienteConectado>::iterator it;
	it = listaDesconectados.begin();
	bool encontrado = false;
	while ((it != listaDesconectados.end()) && !encontrado) {
		if (it->nombre == nombre) {
			listaDesconectados.erase(it);
			encontrado = true;
		}
		it++;
	}
}
void Partida::JugadorDesconectado(string nombre) {
	ClienteConectado unCliente;
	unCliente = GetClienteJugando(nombre);
	if (unCliente.titular) {
		if (TieneSuplente(unCliente.equipo)) {
			//Suplente ocupa el lugar del titular
			JuegaSuplente(unCliente.equipo);
		} else {
			partidaFinalizada = true;
		}
	}
	//Borra de lista de jugadores
	EliminarJugador(nombre);
	// Agrego a la lista de desconectados
	listaDesconectados.push_back(unCliente);

}
void Partida::JuegaTitular(int equipo, ClienteConectado reconectado) {
	list<ClienteConectado>::iterator it;
	it = listaJugadores.begin();
	bool encontrado = false;
	while ((it != listaJugadores.end()) && !encontrado) {
		if ((it->equipo == equipo) && it->titular) {
			encontrado = true;
			it->titular = false;
		}
		it++;
	}
	ActualizarModelo();
}
bool Partida::TieneSuplente(int equipo) {
	list<ClienteConectado>::iterator it;
	for (it = listaJugadores.begin(); it != listaJugadores.end(); it++) {
		if ((it->equipo == equipo) && (!it->titular)) {
			return true;
		}
	}
	return false;
}
// Cuando se eliminar un juegador juega el suplente.
void Partida::JuegaSuplente(int equipo) {
	list<ClienteConectado>::iterator it;
	it = listaJugadores.begin();
	bool encontrado = false;
	while ((it != listaJugadores.end()) && !encontrado) {
		if ((it->equipo == equipo) && !it->titular) {
			encontrado = true;
			it->titular = true;
		}
		it++;
	}
	ActualizarModelo();
}
void Partida::AgregarCliente(ClienteConectado * cliente) {
	if (!seleccionPersonajesIniciada && !EsClienteDesconectado(cliente->nombre)) {//if (!partidaIniciada) {
		int cantidad = listaEspera.size();
		if (cantidad < 2) {
			cliente->titular = true;
		} else {
			cliente->titular = false;
		}
		// Seleccion de equipos
		cantidad++;
		if (cantidad % 2 == 0) {
			cliente->numeroJugador = cantEquipo0;
			cliente->equipo = 0;
			cantEquipo0++;
		} else {
			cliente->numeroJugador = cantEquipo1;
			cliente->equipo = 1;
			cantEquipo1++;
		}
		cliente->numeroJugadorJuego = cantEquipo0 + cantEquipo1;

		cout << "PARTIDA - AgregarCliente: por agregar el cliente "<< cliente->nombre << " | "  << TimeHelper::getStringLocalTimeNow() << endl;
		listaEspera.push_back(*cliente);
		cout << "PARTIDA - AgregarCliente: la lista de espera tiene "<< listaEspera.size() << " | "  << TimeHelper::getStringLocalTimeNow() << endl;

	} else {
		cout << "PARTIDA - AgregarCliente: entro al else"<< cliente->nombre << " | "  << TimeHelper::getStringLocalTimeNow() << endl;

		// Equipo 0 se usa para verificar que no es un Cliente reconectado.
		if (EsClienteDesconectado(cliente->nombre)) {

			cout << "PARTIDA - AgregarCliente: entro al else de EsClienteDesconectado"<< cliente->nombre << " | "  << TimeHelper::getStringLocalTimeNow() << endl;

			//Recupero el equipo para el cliente reconectado.
			ClienteConectado unClienteDesconectado;
			unClienteDesconectado = GetClienteDesconectado(cliente->nombre);
			cliente->equipo = unClienteDesconectado.equipo;
			cliente->personajeId = unClienteDesconectado.personajeId;
			cliente->personajeConfirmado = unClienteDesconectado.personajeConfirmado;
			cliente->numeroJugadorJuego = unClienteDesconectado.numeroJugadorJuego;
			cliente->dataPersonajesEnviada = unClienteDesconectado.dataPersonajesEnviada;
			//Es cliente reconectado?
			if (unClienteDesconectado.titular) {
				// El cliente reconectado era titular
				JuegaTitular(unClienteDesconectado.equipo, *cliente);
				cliente->titular = true;
				//Agrego a la lista de jugadores
				listaJugadores.push_back(*cliente);
			} else {
				//El cliente era suplente.
				cliente->titular = false;
				listaJugadores.push_back(*cliente);
			}
			//Elimino de la lista de desconectados
			EliminarDesconectado(cliente->nombre);
		}
	}
}
ClienteConectado Partida::GetClienteJugando(string nombre) {
	ClienteConectado unCliente;
	list<ClienteConectado>::iterator it;
	for (it = listaJugadores.begin(); it != listaJugadores.end(); it++) {
		if (it->nombre == nombre) {
			unCliente = *it;
		}
	}
	return unCliente;
}
ClienteConectado Partida::GetTitularJugando(int equipo) {
	ClienteConectado unCliente;
	list<ClienteConectado>::iterator it;
	for (it = listaJugadores.begin(); it != listaJugadores.end(); it++) {
		if ((it->titular) && (it->equipo == equipo)) {
			unCliente = *it;
		}
	}
	return unCliente;
}
ClienteConectado Partida::GetClienteEspera(string nombre) {
	ClienteConectado unCliente;
	list<ClienteConectado>::iterator it;
	for (it = listaEspera.begin(); it != listaEspera.end(); it++) {
		if (it->nombre == nombre) {
			unCliente = *it;
		}
	}
	return unCliente;
}

ClienteConectado Partida::GetClienteDesconectado(string nombre) {
	ClienteConectado unCliente;
	list<ClienteConectado>::iterator it;
	for (it = listaDesconectados.begin(); it != listaDesconectados.end();
			it++) {
		if (it->nombre == nombre) {
			unCliente = *it;
		}
	}
	return unCliente;
}
bool Partida::EsClienteDesconectado(string nombre) {
	ClienteConectado unCliente;
	list<ClienteConectado>::iterator it;
	for (it = listaDesconectados.begin(); it != listaDesconectados.end();
			it++) {
		if (it->nombre == nombre) {
			return true;
		}
	}
	return false;
}
int Partida::GetCantidadJugando() {
	return listaJugadores.size();
}
int Partida::GetCantidadJugando(int equipo) {
	int contador = 0;
	list<ClienteConectado>::iterator it;
	for (it = listaJugadores.begin(); it != listaJugadores.end(); it++) {
		// Seleccion de titularidad
		if (it->equipo == equipo) {
			contador++;
		}
	}
	return contador;
}
int Partida::GetCantidadDesconectados() {
	return listaDesconectados.size();
}
int Partida::GetCantidadEspera() {
	return listaEspera.size();
}

void Partida::IniciarSeleccionPersonajes(){
	listaJugadores = listaEspera;
	listaEspera.clear();
	this->SetJugadoresPersonajeInicial();
	this->seleccionPersonajesIniciada = true;
}

void Partida::FinalizarSeleccionPersonajes(){
	this->seleccionPersonajesFinalizada = true;
}

bool Partida::IniciadaSeleccionPersonajes(){
	return this->seleccionPersonajesIniciada;
}

bool Partida::FinalizadaSeleccionPersonajes(){
	return this->seleccionPersonajesFinalizada;
}

void Partida::HandleEventSeleccionPersonajes(string nombreJugador, DataSeleccionAlServidor *data){
	list<ClienteConectado>::iterator it;

	for (it = listaJugadores.begin(); it != listaJugadores.end(); it++) {

		if(it->nombre == nombreJugador){
			it->personajeId = data->personajeId;
			it->personajeConfirmado = data->confirmado;
		}
	}
}

bool Partida::PersonajesSeleccionCompleta(){
	list<ClienteConectado>::iterator it;
	int personajeIdNoValido = static_cast<int>(PERSONAJE::P_NA);
	int cantidadSeleccionada = 0;

	for (it = listaJugadores.begin(); it != listaJugadores.end(); it++) {

		if(it->personajeId != personajeIdNoValido && it->personajeConfirmado){
			cantidadSeleccionada++;		}
	}
	if(listaJugadores.size() == cantidadSeleccionada){
		return true;
	}
	else{
		return false;
	}
}

void Partida::SetPersonajes(){
	list<ClienteConectado>::iterator it;
	for (it = listaJugadores.begin(); it != listaJugadores.end(); it++) {
		this->modelo->set_equipos_with_jugador(it->equipo, it->numeroJugador, it->personajeId);
	}
}

bool Partida::EstaHabilitadoEnvioPersonajes(){
	return this->habilitadoEnvioPersonajes;
}

void Partida::HabilitarEnvioPersonajes(){
	this->habilitadoEnvioPersonajes = true;
}


bool Partida::EstaEnviadaDataPersonajes(){
	list<ClienteConectado>::iterator it;
	int contadorEnviado = 0;

	for (it = listaEspera.begin(); it != listaEspera.end(); it++) {
		if(it->dataPersonajesEnviada){
			contadorEnviado++;
		}
	}
	if(contadorEnviado == listaEspera.size()){
		return true;
	}
	else{
		return false;
	}
}

void Partida::SetDataPersonajesEnviada(string nombre){
	list<ClienteConectado>::iterator it;
	for (it = listaEspera.begin(); it != listaEspera.end(); it++) {
		if(it->nombre == nombre){
			it->dataPersonajesEnviada = true;
		}
	}
}

