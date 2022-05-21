/*
 * Menu.cpp
 *
 *  Created on: 3 may. 2022
 *      Author: Iker L�pez
 */

#include "Menu.h"
#include "../Logger/Logger.h"
#include "../Classes/Ciudad.h"
#include "../Properties/Properties.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <winsock2.h>

#define MAX_LINE 40

using namespace std;

SOCKET comm_s;
char sendBuff[512], recvBuff[2048];
char *SERVER_IP;
int SERVER_PORT;

int Menu::prepareSocket() {
	this->s = &comm_s;
	SERVER_IP = this->prop->propValue[0];
	char *SERVER_PORT_AUX = this->prop->propValue[1];
	SERVER_PORT = atoi(SERVER_PORT_AUX);

	WSADATA wsaData;
	struct sockaddr_in server;

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((*s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(*s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(*s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	mainMenu(false);

	return 1;
}

// NIVEL DE MEN�: 5 (administrador)
void Menu::manageProdMenu(bool b) {
	char *sql;
	char str[MAX_LINE];
	char strAux[2];
	char id_prod[MAX_LINE];
	char nom_prod[MAX_LINE];
	char precio_prod[MAX_LINE];
	char desc_prod[MAX_LINE];
	int opt;

	printf("\n-------------------\n");
	printf("GESTIONAR PRODUCTOS\n");
	printf("-------------------\n\n");
	printf("1. A�adir producto\n");
	printf("2. Eliminar producto\n");
	printf("3. Actualizar informaci�n de un producto\n");
	printf("4. Volver\n");
	printf("Introduzca una opci�n: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logger->logFile(INFO,
				"Opci�n 1 de manageProdMenu seleccionada (addProduct)");

		printf("\n---------------\n");
		printf("A�ADIR PRODUCTO\n");
		printf("---------------\n\n");

		printf("CODIGOS DE PRODUCTO ACTUALES\n");

		// EQUIVALENTE A showProductPK() --------------------------------------------------

		// SENDING command SHOWPRODSPK
		strcpy(sendBuff, "SHOWPRODSPK");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

		// RECEIVING response to command SHOWPRODSPK from the server
		recv(*s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s\n", recvBuff);
			recv(*s, recvBuff, sizeof(recvBuff), 0);
		}
		//cout << recvBuff << "/n" << endl;

		// ----------------------------------------------------------------------------------------------------

		logger->logFile(INFO, "C�digos de productos mostrados");

		printf("\nIntroduzca el c�digo: ");
		fflush(stdout);
		fgets(id_prod, 512, stdin);
		fflush(stdin);
		sscanf(id_prod, "%s", id_prod);

		printf("\nIntroduzca el nombre (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(nom_prod, 512, stdin);
		fflush(stdin);
		sscanf(nom_prod, "%s", nom_prod);

		printf("\nIntroduzca el precio: ");
		fflush(stdout);
		fgets(precio_prod, 512, stdin);
		fflush(stdin);
		sscanf(precio_prod, "%s", precio_prod);

		printf("\nIntroduzca la descripci�n (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(desc_prod, 512, stdin);
		fflush(stdin);
		sscanf(desc_prod, "%s", desc_prod);

		// EQUIVALENTE A addProductDB(sql, p) --------------------------------------------------

		// SENDING command ADDPRODDB
		strcpy(sendBuff, "ADDPRODDB");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar id_prod
		strcpy(sendBuff, id_prod);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar nom_prod
		strcpy(sendBuff, nom_prod);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar precio_prod
		strcpy(sendBuff, precio_prod);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar desc_prod
		strcpy(sendBuff, desc_prod);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff); // Comp.

// ----------------------------------------------------------------------------------------------------

		printf("\n�Producto a�adido con �xito! Pulse ENTER para continuar: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logger->logFile(INFO, "manageProdMenu<<");
		manageProdMenu(false);
		break;

	case 2:
		logger->logFile(INFO,
				"Opci�n 2 de manageProdMenu seleccionada (deleteProduct)");

		printf("\n-----------------\n");
		printf("ELIMINAR PRODUCTO\n");
		printf("-----------------\n\n");

		if (b) {
			printf("\n---------------------------\n");
			printf("LISTA COMPLETA DE PRODUCTOS\n");
			printf("---------------------------\n\n");
		}

		printf("CODIGO || NOMBRE || PRECIO || DESCRIPCION\n\n");

		// EQUIVALENTE A showProducts(false) --------------------------------------------------

		// SENDING command SHOWPRODS
		strcpy(sendBuff, "SHOWPRODS");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

		// RECEIVING response to command SHOWPRODS from the server
		recv(*s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "/n" << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
		}

		// ----------------------------------------------------------------------------------------------------

		logger->logFile(INFO, "Lista completa de productos mostrada");

		if (b) {
			printf(
					"\n�Lista completa de productos mostrada! Pulse ENTER para volver al men� principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		printf("\nIntroduzca el c�digo del producto a eliminar: ");
		fflush(stdout);
		fgets(id_prod, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(id_prod, "%s", id_prod);

		printf("\n�Est� seguro? Si continua se eliminar� el producto [s/n]: ");
		fflush(stdout);
		fgets(str, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(str, "%c", &opt);

		// Asumimos que el usuario solo introducir� una 's' o una 'n'
		if (opt == 's') {

			// EQUIVALENTE A deleteProductDB(sql, id_prod) --------------------------------------------------

			// SENDING command DELPRODDB
			strcpy(sendBuff, "DELPRODDB");
			send(*s, sendBuff, sizeof(sendBuff), 0);
			printf("%s ", sendBuff);

			// Enviar id_prod
			strcpy(sendBuff, id_prod);
			send(*s, sendBuff, sizeof(sendBuff), 0);
			printf("%s\n", sendBuff);

// ----------------------------------------------------------------------------------------------------

			printf(
					"\n�Producto eliminado correctamente! Pulse ENTER para continuar: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		} else if (opt == 'n') {
			manageProdMenu(false);
		}

		logger->logFile(INFO, "manageProdMenu<<");
		manageProdMenu(false);
		break;

	case 3:
		logger->logFile(INFO,
				"Opci�n 3 de manageProdMenu seleccionada (updateProduct)");

		printf("\n-------------------\n");
		printf("ACTUALIZAR PRODUCTO\n");
		printf("-------------------\n\n");

		if (b) {
			printf("\n---------------------------\n");
			printf("LISTA COMPLETA DE PRODUCTOS\n");
			printf("---------------------------\n\n");
		}

		printf("CODIGO || NOMBRE || PRECIO || DESCRIPCION\n\n");

		// EQUIVALENTE A showProducts(false) --------------------------------------------------

		// SENDING command SHOWPRODS
		strcpy(sendBuff, "SHOWPRODS");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

		// RECEIVING response to command SHOWPRODS from the server
		recv(*s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "/n" << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
		}

		// --------------------------------------------------------------------------------

		logger->logFile(INFO, "Lista completa de productos mostrada");

		if (b) {
			printf(
					"\n�Lista completa de productos mostrada! Pulse ENTER para volver al men� principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		printf("\nIntroduzca el c�digo del producto a actualizar: ");
		fflush(stdout);
		fgets(id_prod, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(id_prod, "%s", id_prod);

		printf(
				"\nIntroduzca el (posible nuevo) nombre (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(nom_prod, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(nom_prod, "%s", nom_prod);

		printf("\nIntroduzca el (posible nuevo) precio: ");
		fflush(stdout);
		fgets(precio_prod, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(precio_prod, "%s", precio_prod);

		printf(
				"\nIntroduzca la (posible nueva) descripci�n (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(desc_prod, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(desc_prod, "%s", desc_prod);

		// EQUIVALENTE A updateProductDB(sql, p) --------------------------------------------------

		// SENDING command UDPRODDB
		strcpy(sendBuff, "UDPRODDB");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar id_prod
		strcpy(sendBuff, id_prod);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar nom_prod
		strcpy(sendBuff, nom_prod);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar precio_prod
		strcpy(sendBuff, precio_prod);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar desc_prod
		strcpy(sendBuff, desc_prod);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

// ----------------------------------------------------------------------------------------------------

		printf(
				"\n�Supermercado actualizado correctamente! Pulse ENTER para continuar: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logger->logFile(INFO, "manageProdMenu<<");
		manageProdMenu(false);
		break;

	case 4:
		logger->logFile(INFO,
				"Opci�n 4 de manageProdMenu seleccionada (updateBDMenu<<)");
		updateBDMenu();
		logger->logFile(INFO, "manageProdMenu<<");
		manageProdMenu(false);
		break;
	}
}

// NIVEL DE MEN�: 5 (administrador)
void Menu::manageSuperMenu(bool b) {
	char *sql;
	char str[MAX_LINE];
	char strAux[2];
	char cod_s[MAX_LINE];
	char nom_s[MAX_LINE];
	char dir_s[MAX_LINE];
	char tlf_s[MAX_LINE];
	char metros_cuad_s[MAX_LINE];
	char cod_ciu[MAX_LINE];
	int opt;

	printf("\n-----------------------\n");
	printf("GESTIONAR SUPERMERCADOS\n");
	printf("-----------------------\n\n");
	printf("1. A�adir supermercado\n");
	printf("2. Eliminar supermercado\n");
	printf("3. Actualizar informaci�n de un supermercado\n");
	printf("4. Volver\n");
	printf("Introduzca una opci�n: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logger->logFile(INFO,
				"Opci�n 1 de manageSuperMenu seleccionada (addSupermarket)");

		printf("\n-------------------\n");
		printf("A�ADIR SUPERMERCADO\n");
		printf("-------------------\n\n");

		printf("CODIGOS DE SUPERMERCADO ACTUALES\n");

		//EQUIVALENTE A showSupermarketPK() --------------------------------------------------

		// SENDING command SHOWSMKTSPK
		strcpy(sendBuff, "SHOWSMKTSPK");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

		// RECEIVING response to command SHOWSMKTSPK from the server
		recv(*s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END") != 0) {
			printf("%s\n", recvBuff);
			recv(*s, recvBuff, sizeof(recvBuff), 0);
			//cout << recvBuff << "/n" << endl;
		}

		// ----------------------------------------------------------------------------------------------------

		logger->logFile(INFO, "C�digos de supermercados mostrados");

		printf("\nIntroduzca el c�digo: ");
		fflush(stdout);
		fgets(cod_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(cod_s, "%s", cod_s);

		printf("\nIntroduzca el nombre (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(nom_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(nom_s, "%s", nom_s);

		printf("\nIntroduzca la direcci�n (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(dir_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(dir_s, "%s", dir_s);

		printf("\nIntroduzca el tel�fono: ");
		fflush(stdout);
		fgets(tlf_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(tlf_s, "%s", tlf_s);

		printf("\nIntroduzca los metros cuadrados: ");
		fflush(stdout);
		fgets(metros_cuad_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(metros_cuad_s, "%s", metros_cuad_s);

		printf("\nIntroduzca el c�digo de la ciudad: ");
		fflush(stdout);
		fgets(cod_ciu, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(cod_ciu, "%s", cod_ciu);

		// EQUIVALENTE A addSupermarketDB(sql, s) --------------------------------------------------

		// SENDING command ADDSMKTDB
		strcpy(sendBuff, "ADDSMKTDB");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar cod_s
		strcpy(sendBuff, cod_s);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar nom_s
		strcpy(sendBuff, nom_s);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar dir_s
		strcpy(sendBuff, dir_s);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar tlf_s
		strcpy(sendBuff, tlf_s);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar metros_cuad_s
		strcpy(sendBuff, metros_cuad_s);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar cod_ciu
		strcpy(sendBuff, cod_ciu);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff); // Comp.

// ----------------------------------------------------------------------------------------------------

		printf(
				"\n�Supermercado a�adido con �xito! Pulse ENTER para continuar: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logger->logFile(INFO, "manageSuperMenu<<");
		manageSuperMenu(false);
		break;

	case 2:
		logger->logFile(INFO,
				"Opci�n 2 de manageSuperMenu seleccionada (deleteSupermarket)");

		printf("\n---------------------\n");
		printf("ELIMINAR SUPERMERCADO\n");
		printf("---------------------\n\n");

		if (b) {
			printf("\n-------------------------------\n");
			printf("LISTA COMPLETA DE SUPERMERCADOS\n");
			printf("-------------------------------\n\n");
		}

		printf(
				"CODIGO || NOMBRE || DIRECCION || TELEFONO || METROS_CUADRADOS || CODIGO_CIUDAD\n\n");

		// EQUIVALENTE A showSupermarkets(false) --------------------------------------------------

		// SENDING command SHOWSMKTS
		strcpy(sendBuff, "SHOWSMKTS");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

		// RECEIVING response to command SHOWSMKTS from the server
		recv(*s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "\n" << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
		}

		// ----------------------------------------------------------------------------------------------------

		logger->logFile(INFO, "Lista completa de supermercados mostrada");

		if (b) {
			printf(
					"\n�Lista completa de supermercados mostrada! Pulse ENTER para volver al men� principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		printf("\nIntroduzca el c�digo del supermercado a eliminar: ");
		fflush(stdout);
		fgets(cod_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(cod_s, "%s", cod_s);

		printf(
				"\n�Est� seguro? Si continua se eliminar� el supermercado [s/n]: ");
		fflush(stdout);
		fgets(str, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(str, "%c", &opt);

		// Asumimos que el usuario solo introducir� una 's' o una 'n'
		if (opt == 's') {

			// EQUIVALENTE A deleteSupermarketDB(sql, cod_s) --------------------------------------------------

			// SENDING command DELSMKTDB
			strcpy(sendBuff, "DELSMKTDB");
			send(*s, sendBuff, sizeof(sendBuff), 0);
			printf("%s ", sendBuff); // Comp.

			// Enviar cod_s
			strcpy(sendBuff, cod_s);
			send(*s, sendBuff, sizeof(sendBuff), 0);
			printf("%s\n", sendBuff); // Comp.

// ----------------------------------------------------------------------------------------------------

			printf(
					"\n�Supermercado eliminado correctamente! Pulse ENTER para continuar: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		} else if (opt == 'n') {
			manageSuperMenu(false);
		}

		logger->logFile(INFO, "manageSuperMenu<<");
		manageSuperMenu(false);
		break;

	case 3:
		logger->logFile(INFO,
				"Opci�n 3 de manageSuperMenu seleccionada (updateSupermarket())");

		printf("\n-----------------------\n");
		printf("ACTUALIZAR SUPERMERCADO\n");
		printf("-----------------------\n\n");

		if (b) {
			printf("\n-------------------------------\n");
			printf("LISTA COMPLETA DE SUPERMERCADOS\n");
			printf("-------------------------------\n\n");
		}

		printf(
				"CODIGO || NOMBRE || DIRECCION || TELEFONO || METROS_CUADRADOS || CODIGO_CIUDAD\n\n");

		// EQUIVALENTE A showSupermarkets(false) --------------------------------------------------

		// SENDING command SHOWSMKTS
		strcpy(sendBuff, "SHOWSMKTS");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

		// RECEIVING response to command SHOWSMKTS from the server
		recv(*s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "\n" << endl;
			recv(*s, recvBuff, sizeof(recvBuff), 0);
		}

		// ----------------------------------------------------------------------------------------------------

		logger->logFile(INFO, "Lista completa de supermercados mostrada");

		if (b) {
			printf(
					"\n�Lista completa de supermercados mostrada! Pulse ENTER para volver al men� principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		printf("\nIntroduzca el c�digo del supermercado a actualizar: ");
		fflush(stdout);
		fgets(cod_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(cod_s, "%s", cod_s);

		printf(
				"\nIntroduzca el (posible nuevo) nombre (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(nom_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(nom_s, "%s", nom_s);

		printf(
				"\nIntroduzca la (posible nueva) direcci�n (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(dir_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(dir_s, "%s", dir_s);

		printf("\nIntroduzca el (posible nuevo) tel�fono: ");
		fflush(stdout);
		fgets(tlf_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(tlf_s, "%s", tlf_s);

		printf("\nIntroduzca los (posibles nuevos) metros cuadrados: ");
		fflush(stdout);
		fgets(metros_cuad_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(metros_cuad_s, "%s", metros_cuad_s);

		printf("\nIntroduzca el (posible nuevo) c�digo de la ciudad: ");
		fflush(stdout);
		fgets(cod_ciu, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(cod_ciu, "%s", cod_ciu);

		// EQUIVALENTE A updateSupermarketDB(sql, s) --------------------------------------------------

		// SENDING command UDSMKTDB
		strcpy(sendBuff, "UDSMKTDB");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar cod_s
		strcpy(sendBuff, cod_s);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar nom_s
		strcpy(sendBuff, nom_s);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar dir_s
		strcpy(sendBuff, dir_s);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar tlf_s
		strcpy(sendBuff, tlf_s);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar metros_cuad_s
		strcpy(sendBuff, metros_cuad_s);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar cod_ciu
		strcpy(sendBuff, cod_ciu);
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

// ----------------------------------------------------------------------------------------------------

		printf(
				"\n�Supermercado actualizado correctamente! Pulse ENTER para continuar: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logger->logFile(INFO, "manageSuperMenu<<");
		manageSuperMenu(false);
		break;

	case 4:
		logger->logFile(INFO,
				"Opci�n 4 de manageSuperMenu seleccionada (updateBDMenu<<)");
		updateBDMenu();
		break;
	}
}

// NIVEL DE MEN�: 4
void Menu::updateBDMenu() {
	int opt;
	char str[10];

	printf("\n-------------\n");
	printf("ACTUALIZAR BD\n");
	printf("-------------\n\n");
	printf("1. Gestionar supermercados\n");
	printf("2. Gestionar productos\n");
	printf("3. Volver\n");
	printf("Introduzca una opci�n: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logger->logFile(INFO,
				"Opci�n 1 de updateBDMenu seleccionada (>>manageSuperMenu)");
		manageSuperMenu(false);
		break;

	case 2:
		logger->logFile(INFO,
				"Opci�n 2 de updateBDMenu seleccionada (>>manageProdMenu)");
		manageProdMenu(false);
		break;

	case 3:
		logger->logFile(INFO,
				"Opci�n 3 de updateBDMenu seleccionada (adminMenu<<)");
		adminMenu();
		break;
	}
}

// NIVEL DE MEN�: 3 (usuario) y 4 (administrador)
void Menu::queryBDMenu(bool b) {
	char strAux[2];
	int opt;
	char str[10];

	printf("\n-----------------\n");
	printf("CONSULTAS A LA BD\n");
	printf("-----------------\n\n");
	printf("1. Visualizar supermercados\n");
	printf("2. Visualizar productos\n");
	printf("3. Visualizar provincias\n");
	printf("4. Visualizar ciudades\n");
	printf("5. Volver a men� principal\n");
	printf("Introduzca una opci�n: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logger->logFile(INFO,
				"Opci�n 1 de queryBDMenu seleccionada (showSupermarkets)");

		if (b) {
			printf("\n-------------------------------\n");
			printf("LISTA COMPLETA DE SUPERMERCADOS\n");
			printf("-------------------------------\n\n");
		}

		printf(
				"CODIGO || NOMBRE || DIRECCION || TELEFONO || METROS_CUADRADOS || CODIGO_CIUDAD\n\n");

		// EQUIVALENTE A showSupermarkets(true) --------------------------------------------------

		// SENDING command SHOWSMKTS
		strcpy(sendBuff, "SHOWSMKTS");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

		// RECEIVING response to command SHOWSMKTS from the server
		recv(*s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "\n" << endl;
			recv(*s, recvBuff, sizeof(recvBuff), 0);
		}

		// --------------------------------------------------------------------------------

		logger->logFile(INFO, "Lista completa de supermercados mostrada");

		if (b) {
			printf(
					"\n�Lista completa de supermercados mostrada! Pulse ENTER para volver al men� principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		logger->logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 2:
		logger->logFile(INFO,
				"Opci�n 2 de queryBDMenu seleccionada (showProducts)");

		if (b) {
			printf("\n---------------------------\n");
			printf("LISTA COMPLETA DE PRODUCTOS\n");
			printf("---------------------------\n\n");
		}

		printf("CODIGO || NOMBRE || PRECIO || DESCRIPCION\n\n");

		// EQUIVALENTE A showProducts(true) --------------------------------------------------

		// SENDING command SHOWPRODS
		strcpy(sendBuff, "SHOWPRODS");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

		// RECEIVING response to command SHOWPRODS from the server
		recv(*s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "/n" << endl;

			recv(*s, recvBuff, sizeof(recvBuff), 0);
		}

		// --------------------------------------------------------------------------------

		logger->logFile(INFO, "Lista completa de productos mostrada");

		if (b) {
			printf(
					"\n�Lista completa de productos mostrada! Pulse ENTER para volver al men� principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		logger->logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 3:
		logger->logFile(INFO,
				"Opci�n 3 de queryBDMenu seleccionada (showProvinces)");

		if (b) {
			printf("\n----------------------------\n");
			printf("LISTA COMPLETA DE PROVINCIAS\n");
			printf("----------------------------\n\n");
		}

		printf("CODIGO || NOMBRE\n\n");

		if (data.num_provincias != 0) {
			for (int i = 0; i < data.num_provincias; ++i) {
				printf("%i || ", data.provincias[i].cod_prov);
				printf("%s\n", data.provincias[i].nom_prov);
			}

		} else {
			// EQUIVALENTE A showProvinces(true) --------------------------------------------------

			// SENDING command SHOWPROVS
			strcpy(sendBuff, "SHOWPROVS");
			send(*s, sendBuff, sizeof(sendBuff), 0);
			printf("%s\n", sendBuff);

			// RECEIVING response to command SHOWPROVS from the server
			recv(*s, recvBuff, sizeof(recvBuff), 0);

			while (strcmp(recvBuff, "END")) {
				printf("%s || ", recvBuff);
				int cod_prov = 0;
				sscanf(recvBuff, "%i", &cod_prov);
				//cout << recvBuff << " || " << endl;

				recv(*s, recvBuff, sizeof(recvBuff), 0);
				printf("%s\n", recvBuff);
				char *nom_prov = new char[MAX_LINE];
				sscanf(recvBuff, "%s", nom_prov);
				//cout << recvBuff << " || " << endl;

				recv(*s, recvBuff, sizeof(recvBuff), 0);

				Provincia p(cod_prov, nom_prov);
				data.addProvincia(p);
			}

			// --------------------------------------------------------------------------------
		}

		logger->logFile(INFO, "Lista completa de provincias mostrada");

		if (b) {
			printf(
					"\n�Lista completa de provincias mostrada! Pulse ENTER para volver al men� principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		logger->logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 4:
		logger->logFile(INFO,
				"Opci�n 4 de queryBDMenu seleccionada (showCities)");

		if (b) {
			printf("\n--------------------------\n");
			printf("LISTA COMPLETA DE CIUDADES\n");
			printf("--------------------------\n\n");
		}

		printf("CODIGO || NOMBRE || CODIGO_PROV\n\n");

		if (data.num_ciudades != 0) {
			for (int i = 0; i < data.num_ciudades; ++i) {
				printf("%i || ", data.ciudades[i].cod_ciu);
				printf("%s || ", data.ciudades[i].nom_ciu);
				printf("%i\n", data.ciudades[i].cod_prov);
			}

		} else {
			// EQUIVALENTE A showCities(true) --------------------------------------------------

			// SENDING command SHOWCITIES
			strcpy(sendBuff, "SHOWCITIES");
			send(*s, sendBuff, sizeof(sendBuff), 0);
			printf("%s\n", sendBuff);

			// RECEIVING response to command SHOWCITIES from the server
			recv(*s, recvBuff, sizeof(recvBuff), 0);

			while (strcmp(recvBuff, "END")) {
				printf("%s || ", recvBuff);
				int cod_ciu = atoi(recvBuff);
				//sscanf(recvBuff, "%i", &cod_ciu);
				//cout << recvBuff << " || " << endl;

				recv(*s, recvBuff, sizeof(recvBuff), 0);
				printf("%s || ", recvBuff);
				char *nom_ciu = new char[MAX_LINE];
				sscanf(recvBuff, "%s", nom_ciu);
				//cout << recvBuff << " || " << endl;

				recv(*s, recvBuff, sizeof(recvBuff), 0);
				printf("%s\n", recvBuff);
				int cod_prov_c = atoi(recvBuff);
				//sscanf(recvBuff, "%i", &cod_prov_c);
				//cout << recvBuff << "/n" << endl;

				recv(*s, recvBuff, sizeof(recvBuff), 0);

				Ciudad c(cod_ciu, nom_ciu, cod_prov_c);
				data.addCiudad(c);
			}

			// --------------------------------------------------------------------------------
		}

		logger->logFile(INFO, "Lista completa de ciudades mostrada");

		if (b) {
			printf(
					"\n�Lista completa de ciudades mostrada! Pulse ENTER para volver al men� principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		logger->logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 5:
		logger->logFile(INFO,
				"Opci�n 5 de queryBDMenu seleccionada (mainMenu<<)");
		mainMenu(true);
		break;
	}
}

// NIVEL DE MEN�: 3
void Menu::adminMenu() {
	char strAux[2];
	int opt;
	char str[10];

	printf("\n------------------\n");
	printf("MEN� ADMINISTRADOR\n");
	printf("------------------\n\n");
	printf("1. Actualizar BD\n");
	printf("2. Consultas a la BD\n");
	printf("3. Estad�sticas\n");
	printf("4. Volver al men� principal\n");
	printf("Introduzca una opci�n: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logger->logFile(INFO,
				"Opci�n 1 de adminMenu seleccionada (>>updateBDMenu)");
		updateBDMenu();
		break;

	case 2:
		logger->logFile(INFO,
				"Opci�n 2 de adminMenu seleccionada (>>queryBDMenu)");
		queryBDMenu(true);
		break;

	case 3:
		logger->logFile(INFO,
				"Opci�n 3 de adminMenu seleccionada (showStatistics)");

		printf("\n------------\n");
		printf("ESTAD�STICAS\n");
		printf("------------\n\n");

		// SENDING command SHOWSTATS
		strcpy(sendBuff, "SHOWSTATS");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

		// RECEIVING response to command SHOWSTATS from the server
		recv(*s, recvBuff, sizeof(recvBuff), 0);
		printf("Media de los precios de los productos: %s\n", recvBuff);
//		cout << "Media de los precios de los productos: " << recvBuff << endl;

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		printf("Media de los metros cuadrados de los supermercados: %s\n",
				recvBuff);
//		cout << "Media de los metros cuadrados de los supermercados: " << recvBuff << endl;

		logger->logFile(INFO, "Estad�sticas mostradas");

		printf(
				"\n�Estad�sticas mostradas! Pulse ENTER para volver al men� principal: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logger->logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 4:
		logger->logFile(INFO,
				"Opci�n 4 de adminMenu seleccionada (mainMenu<<)");
		mainMenu(true);
		break;
	}
}

// NIVEL DE MEN�: 2
void Menu::userMenu() {
	char strAux[2];
	int opt;
	char str[10];

	printf("\n------------\n");
	printf("MEN� USUARIO\n");
	printf("------------\n\n");
	printf("1. Consultas a la BD\n");
	printf("2. Estad�sticas\n");
	printf("3. Volver al men� principal\n");
	printf("Introduzca una opci�n: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logger->logFile(INFO,
				"Opci�n 1 de userMenu seleccionada (>>queryBDMenu)");
		queryBDMenu(true);
		break;

	case 2:
		logger->logFile(INFO,
				"Opci�n 2 de userMenu seleccionada (showStatistics)");

		printf("\n------------\n");
		printf("ESTAD�STICAS\n");
		printf("------------\n\n");

		//fflush(stdout);

		// SENDING command SHOWSTATS
		strcpy(sendBuff, "SHOWSTATS");
		send(*s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

		// RECEIVING response to command SHOWSTATS from the server
		recv(*s, recvBuff, sizeof(recvBuff), 0);
		printf("Media de los precios de los productos: %s\n", recvBuff);
//		cout << "Media de los precios de los productos: " << recvBuff << endl;

		recv(*s, recvBuff, sizeof(recvBuff), 0);
		printf("Media de los metros cuadrados de los supermercados: %s\n",
				recvBuff);
//		cout << "Media de los metros cuadrados de los supermercados: " << recvBuff << endl;

		logger->logFile(INFO, "Estad�sticas mostradas");

		printf(
				"\n�Estad�sticas mostradas! Pulse ENTER para volver al men� principal: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logger->logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 3:
		logger->logFile(INFO, "Opci�n 3 de userMenu seleccionada (mainMenu<<)");
		mainMenu(true);
		break;
	}
}

// NIVEL DE MEN�: 2
void Menu::adminAccessMenu() {
	int pass;
	char str[10];

	printf("\n--------------------\n");
	printf("ACCESO ADMINISTRADOR\n");
	printf("--------------------\n\n");
	printf(
			"Introduzca la clave (si quiere volver al men� principal pulse 'q' y para continuar pulse ENTER): ");
	fflush(stdout);
	fgets(str, 6, stdin);
	fflush(stdin);
	sscanf(str, "%i", &pass);

	int propPass;
	sscanf(this->prop->propValue[2], "%i", &propPass);

	if (pass == propPass) {
		logger->logFile(INFO,
				"Contrase�a de administrador correcta (>>adminMenu)");
		adminMenu();
	} else if (str[0] == 'q') {
		logger->logFile(INFO, "mainMenu<<");
		mainMenu(true);
	} else {
		logger->logFile(INFO, "adminAccessMenu<<");
		adminAccessMenu();
	}

}

// NIVEL DE MEN�: 1
void Menu::mainMenu(bool b) {
	int opt;
	char str[10];

	prop->loadProperties(prop, "config.prop");

	if (b) {
		printf("\n------------\n");
		printf("DEUSTOMARKET\n");
		printf("------------\n\n");
	} else {
		printf("------------\n");
		printf("DEUSTOMARKET\n");
		printf("------------\n\n");
	}

	printf("1. Entrar como usuario\n");
	printf("2. Entrar como administrador\n");
	printf("3. Salir\n");
	printf("Introduzca una opci�n: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logger->logFile(INFO, "Opci�n 1 de mainMenu seleccionada (>>userMenu)");
		userMenu();
		break;

	case 2:
		logger->logFile(INFO,
				"Opci�n 2 de mainMenu seleccionada (>>adminMenu)");
		adminAccessMenu();
		break;

	case 3:
		logger->logFile(END,
				"Opci�n 3 de mainMenu seleccionada (ejecuci�n finalizada)");
		exit(0);
	}

}

void Menu::setProperties(Properties *prop) {
	this->prop = prop;
}

void Menu::setLogger(Logger *logger) {
	this->logger = logger;
}

void Menu::setData(Data d) {
	this->data = d;
}
