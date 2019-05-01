/*
 * Comunicacion.cpp
 *
 *  Created on: Apr 29, 2019
 *      Author: jorge
 */

#include "Comunicacion.h"
#include <iostream>

Comunicacion::Comunicacion() {
	// TODO Auto-generated constructor stub

}

int Comunicacion::preparar_socket_servidor(const char* puerto_numero,
		int num_clientes_espera) {
	int s = 0;

	struct addrinfo hints;
	struct addrinfo *ptr;

	int skt = 0;
	int val;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; /* IPv4 (or AF_INET6 for IPv6)     */
	hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
	hints.ai_flags = AI_PASSIVE; /* AI_PASSIVE for server           */

	s = getaddrinfo(NULL, puerto_numero, &hints, &ptr);

	if (s != 0) {
		printf("Error in getaddrinfo: %s\n", gai_strerror(s));
		std::cout << "[Comunicacion-preparar_socket_servidor] error en getaddrinfo"<< std::endl;
		return 1;
	}

	skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (skt == -1) {
		printf("Error: %s\n", strerror(errno));
		std::cout << "[Comunicacion-preparar_socket_servidor] error generando socket"<< std::endl;
		freeaddrinfo(ptr);
		return ERROR;
	}

	this->socket_servidor = skt;

	// Activamos la opcion de Reusar la Direccion en caso de que esta
	// no este disponible por un TIME_WAIT
	val = 1;
	s = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	if (s == -1) {
		printf("Error: %s\n", strerror(errno));
		std::cout << "[Comunicacion-preparar_socket_servidor] error en setsockopt"<< std::endl;
		close(skt);
		freeaddrinfo(ptr);
		return ERROR;
	}

	// Decimos en que direccion local queremos escuchar, en especial el puerto
	// De otra manera el sistema operativo elegiria un puerto random
	// y el cliente no sabria como conectarse
	s = bind(skt, ptr->ai_addr, ptr->ai_addrlen);
	if (s == -1) {
		printf("Error: %s\n", strerror(errno));
		std::cout << "[Comunicacion-preparar_socket_servidor] error en bind"<< std::endl;
		close(skt);
		freeaddrinfo(ptr);
		return ERROR;
	}

	freeaddrinfo(ptr);

	// Cuanto clientes podemos mantener en espera antes de poder acceptarlos?
	s = listen(skt, num_clientes_espera);
	if (s == -1) {
		printf("Error: %s\n", strerror(errno));
		std::cout << "[Comunicacion-preparar_socket_servidor] Error en listen"<< std::endl;
		close(skt);
		return ERROR;
	}

	return OK;

}
int Comunicacion::aceptar_cliente() {
	int peerskt;
	peerskt = accept(this->socket_servidor, NULL, NULL); // aceptamos un cliente
	if (peerskt == -1) {
		printf("Error: %s\n", strerror(errno));
		return ERROR;
	}
	this->socket_cliente = peerskt;
	return OK;
}
int Comunicacion::preparar_socket_cliente(char *nom_servidor,
		const char* puerto_num) {
//	std::cout << "[Comunicacion-preparar_socket_cliente] nom_servidor: "<< nom_servidor << "; puerto_num: " << puerto_num << std::endl;
	int socket_cliente;
	struct sockaddr_in servidor_addr;
	struct hostent *servidor;

	socket_cliente = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_cliente < 0) {
		std::cout << "[Comunicacion-preparar_socket_cliente] Error en creando socket()"<< std::endl;
		return ERROR;
	}
	servidor = gethostbyname(nom_servidor);
	if (servidor == NULL) {
		printf("ERROR, no existe ese host\n");
		std::cout << "[Comunicacion-preparar_socket_cliente] Error en gethostbyname()"<< std::endl;
		return ERROR;
	}
	memset(&servidor_addr, 0, sizeof(servidor_addr));

	servidor_addr.sin_family = AF_INET;
	servidor_addr.sin_addr.s_addr = INADDR_ANY;
	servidor_addr.sin_port = htons(atoi(puerto_num));

	if (connect(socket_cliente, (struct sockaddr *) &servidor_addr,
			sizeof(servidor_addr)) < 0) {
		std::cout << "[Comunicacion-preparar_socket_cliente] Error en el connect()"<< std::endl;
		close(socket_cliente);
		return ERROR;
	}
	this->socket_cliente = socket_cliente;

	return OK;

}
int Comunicacion::enviar_mensaje(int socket, char* mensaje, int tam_mensaje) {

	int sent = 0;
	int s = 0;
	bool is_the_socket_valid = true;
//	std::cout << "[Comunicacion-enviarMensaje] Se va a iniciar el en enviado del mensaje: "<< mensaje << ";" << std::endl;

	while (sent < tam_mensaje && is_the_socket_valid) {
		s = send(socket, &mensaje[sent], tam_mensaje - sent, MSG_NOSIGNAL);

		if (s == 0) {
			is_the_socket_valid = false;
		} else if (s < 0) {
			is_the_socket_valid = false;
		} else {
			sent += s;
		}
	}
//	std::cout << "[Comunicacion-enviarMensaje] Se completó el envío del mensaje: " << mensaje << ";" << std::endl;

	if (is_the_socket_valid) {
		return sent;
	} else {
		return -1;
	}
}

int Comunicacion::recibir_mensaje(int socket, char* mensaje, int tam_mensaje) {
	int received = 0;
	int s = 0;
	bool is_the_socket_valid = true;
//	std::cout << "[Comunicacion-recibir_mensaje] Se va a recibir un msj de tamaño: " << tam_mensaje << std::endl;
	while (received < tam_mensaje && is_the_socket_valid) {

		s = recv(socket, &mensaje[received], tam_mensaje - received, MSG_NOSIGNAL);

		if (s == 0) { // nos cerraron el socket :(
			is_the_socket_valid = false;
			std::cout << "[Comunicacion-recibir_mensaje] Socket cerrado" << std::endl;
		} else if (s < 0) { // hubo un error >(
			is_the_socket_valid = false;
			std::cout << "[Comunicacion-recibir_mensaje] Error recibiendo msj" << std::endl;
		} else {
			received += s;
//			std::cout << "[Comunicacion-recibir_mensaje] tamaño actual: " << s << std::endl;
		}
	}
//	std::cout << "[Comunicacion-recibir_mensaje] Tamaño recibido: " << received << std::endl;
//	std::cout << "[Comunicacion-recibir_mensaje] Mensaje recibido: " << mensaje << std::endl;

	if (is_the_socket_valid) {
		return received;
	} else {
		return -1;
	}
}

int Comunicacion::get_socket_cliente(){

	return this->socket_cliente;
}
int Comunicacion::get_socket_servidor(){
	return this->socket_servidor;

}
void Comunicacion::close_socket(int socket){
	 shutdown(socket, SHUT_RDWR);
	 close(socket);

}


Comunicacion::~Comunicacion() {
	// TODO Auto-generated destructor stub
}

