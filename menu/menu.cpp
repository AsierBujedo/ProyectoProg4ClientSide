/*
 * menu.cpp
 *
 *  Created on: 3 may. 2022
 *      Author: Iker López
 */

extern "C" {
#include "menu.h"
#include "../logger/logger.h"
#include "../properties/properties.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
}

#include <iostream>

#define MAX_LINE 40

using namespace std;

Properties properties;
SOCKET s;
char sendBuff[512], recvBuff[2048];
#define SERVER_IP "127.0.0.1" // Fichero de configuración
#define SERVER_PORT 6000 // Fichero de configuración

int prepareSocket() {
	WSADATA wsaData;
	struct sockaddr_in server;

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	mainMenu(false);

	return 1;
}

// NIVEL DE MENÚ: 5 (administrador)
void manageProdMenu(bool b) {
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
	printf("1. Añadir producto\n");
	printf("2. Eliminar producto\n");
	printf("3. Actualizar información de un producto\n");
	printf("4. Volver\n");
	printf("Introduzca una opción: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logFile(INFO, "Opción 1 de manageProdMenu seleccionada (addProduct)");

		printf("\n---------------\n");
		printf("AÑADIR PRODUCTO\n");
		printf("---------------\n\n");

		printf("CODIGOS DE PRODUCTO ACTUALES\n");

		// EQUIVALENTE A showProductPK() --------------------------------------------------

		// SENDING command SHOWPRODSPK
		strcpy(sendBuff, "SHOWPRODSPK");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWPRODSPK from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s\n", recvBuff);
			recv(s, recvBuff, sizeof(recvBuff), 0);
		}
		//cout << recvBuff << "/n" << endl;

		// ----------------------------------------------------------------------------------------------------

		logFile(INFO, "Códigos de productos mostrados");

		printf("\nIntroduzca el código: ");
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

		printf("\nIntroduzca la descripción (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(desc_prod, 512, stdin);
		fflush(stdin);
		sscanf(desc_prod, "%s", desc_prod);

		// EQUIVALENTE A addProductDB(sql, p) --------------------------------------------------

		// SENDING command ADDPRODDB
		strcpy(sendBuff, "ADDPRODDB");
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar id_prod
		strcpy(sendBuff, id_prod);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar nom_prod
		strcpy(sendBuff, nom_prod);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar precio_prod
		strcpy(sendBuff, precio_prod);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar desc_prod
		strcpy(sendBuff, desc_prod);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff); // Comp.

// ----------------------------------------------------------------------------------------------------

		printf("\n¡Producto añadido con éxito! Pulse ENTER para continuar: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logFile(INFO, "manageProdMenu<<");
		manageProdMenu(false);
		break;

	case 2:
		logFile(INFO,
				"Opción 2 de manageProdMenu seleccionada (deleteProduct)");

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
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWPRODS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "/n" << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
		}

		// ----------------------------------------------------------------------------------------------------

		logFile(INFO, "Lista completa de productos mostrada");

		if (b) {
			printf(
					"\n¡Lista completa de productos mostrada! Pulse ENTER para volver al menú principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		printf("\nIntroduzca el código del producto a eliminar: ");
		fflush(stdout);
		fgets(id_prod, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(id_prod, "%s", id_prod);

		printf("\n¿Está seguro? Si continua se eliminará el producto [s/n]: ");
		fflush(stdout);
		fgets(str, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(str, "%c", &opt);

		// Asumimos que el usuario solo introducirá una 's' o una 'n'
		if (opt == 's') {

			// EQUIVALENTE A deleteProductDB(sql, id_prod) --------------------------------------------------

			// SENDING command DELPRODDB
			strcpy(sendBuff, "DELPRODDB");
			send(s, sendBuff, sizeof(sendBuff), 0);
			printf("%s ", sendBuff);

			// Enviar id_prod
			strcpy(sendBuff, id_prod);
			send(s, sendBuff, sizeof(sendBuff), 0);
			printf("%s\n", sendBuff);

// ----------------------------------------------------------------------------------------------------

			printf(
					"\n¡Producto eliminado correctamente! Pulse ENTER para continuar: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		} else if (opt == 'n') {
			manageProdMenu(false);
		}

		logFile(INFO, "manageProdMenu<<");
		manageProdMenu(false);
		break;

	case 3:
		logFile(INFO,
				"Opción 3 de manageProdMenu seleccionada (updateProduct)");

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
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWPRODS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "/n" << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
		}

		// --------------------------------------------------------------------------------

		logFile(INFO, "Lista completa de productos mostrada");

		if (b) {
			printf(
					"\n¡Lista completa de productos mostrada! Pulse ENTER para volver al menú principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		printf("\nIntroduzca el código del producto a actualizar: ");
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
				"\nIntroduzca la (posible nueva) descripción (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(desc_prod, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(desc_prod, "%s", desc_prod);

		// EQUIVALENTE A updateProductDB(sql, p) --------------------------------------------------

		// SENDING command UDPRODDB
		strcpy(sendBuff, "UDPRODDB");
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar id_prod
		strcpy(sendBuff, id_prod);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar nom_prod
		strcpy(sendBuff, nom_prod);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar precio_prod
		strcpy(sendBuff, precio_prod);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar desc_prod
		strcpy(sendBuff, desc_prod);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

// ----------------------------------------------------------------------------------------------------

		printf(
				"\n¡Supermercado actualizado correctamente! Pulse ENTER para continuar: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logFile(INFO, "manageProdMenu<<");
		manageProdMenu(false);
		break;

	case 4:
		logFile(INFO,
				"Opción 4 de manageProdMenu seleccionada (updateBDMenu<<)");
		updateBDMenu();
		logFile(INFO, "manageProdMenu<<");
		manageProdMenu(false);
		break;
	}
}

// NIVEL DE MENÚ: 5 (administrador)
void manageSuperMenu(bool b) {
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
	printf("1. Añadir supermercado\n");
	printf("2. Eliminar supermercado\n");
	printf("3. Actualizar información de un supermercado\n");
	printf("4. Volver\n");
	printf("Introduzca una opción: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logFile(INFO,
				"Opción 1 de manageSuperMenu seleccionada (addSupermarket)");

		printf("\n-------------------\n");
		printf("AÑADIR SUPERMERCADO\n");
		printf("-------------------\n\n");

		printf("CODIGOS DE SUPERMERCADO ACTUALES\n");

		//EQUIVALENTE A showSupermarketPK() --------------------------------------------------

		// SENDING command SHOWSMKTSPK
		strcpy(sendBuff, "SHOWSMKTSPK");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWSMKTSPK from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END") != 0) {
			printf("%s\n", recvBuff);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			//cout << recvBuff << "/n" << endl;
		}

		// ----------------------------------------------------------------------------------------------------

		logFile(INFO, "Códigos de supermercados mostrados");

		printf("\nIntroduzca el código: ");
		fflush(stdout);
		fgets(cod_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(cod_s, "%s", cod_s);

		printf("\nIntroduzca el nombre (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(nom_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(nom_s, "%s", nom_s);

		printf("\nIntroduzca la dirección (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(dir_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(dir_s, "%s", dir_s);

		printf("\nIntroduzca el teléfono: ");
		fflush(stdout);
		fgets(tlf_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(tlf_s, "%s", tlf_s);

		printf("\nIntroduzca los metros cuadrados: ");
		fflush(stdout);
		fgets(metros_cuad_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(metros_cuad_s, "%s", metros_cuad_s);

		printf("\nIntroduzca el código de la ciudad: ");
		fflush(stdout);
		fgets(cod_ciu, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(cod_ciu, "%s", cod_ciu);

		// EQUIVALENTE A addSupermarketDB(sql, s) --------------------------------------------------

		// SENDING command ADDSMKTDB
		strcpy(sendBuff, "ADDSMKTDB");
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar cod_s
		strcpy(sendBuff, cod_s);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar nom_s
		strcpy(sendBuff, nom_s);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar dir_s
		strcpy(sendBuff, dir_s);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar tlf_s
		strcpy(sendBuff, tlf_s);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar metros_cuad_s
		strcpy(sendBuff, metros_cuad_s);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff); // Comp.

		// Enviar cod_ciu
		strcpy(sendBuff, cod_ciu);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff); // Comp.

// ----------------------------------------------------------------------------------------------------

		printf(
				"\n¡Supermercado añadido con éxito! Pulse ENTER para continuar: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logFile(INFO, "manageSuperMenu<<");
		manageSuperMenu(false);
		break;

	case 2:
		logFile(INFO,
				"Opción 2 de manageSuperMenu seleccionada (deleteSupermarket)");

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
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWSMKTS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "\n" << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
		}

		// ----------------------------------------------------------------------------------------------------

		logFile(INFO, "Lista completa de supermercados mostrada");

		if (b) {
			printf(
					"\n¡Lista completa de supermercados mostrada! Pulse ENTER para volver al menú principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		printf("\nIntroduzca el código del supermercado a eliminar: ");
		fflush(stdout);
		fgets(cod_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(cod_s, "%s", cod_s);

		printf(
				"\n¿Está seguro? Si continua se eliminará el supermercado [s/n]: ");
		fflush(stdout);
		fgets(str, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(str, "%c", &opt);

		// Asumimos que el usuario solo introducirá una 's' o una 'n'
		if (opt == 's') {

			// EQUIVALENTE A deleteSupermarketDB(sql, cod_s) --------------------------------------------------

			// SENDING command DELSMKTDB
			strcpy(sendBuff, "DELSMKTDB");
			send(s, sendBuff, sizeof(sendBuff), 0);
			printf("%s ", sendBuff); // Comp.

			// Enviar cod_s
			strcpy(sendBuff, cod_s);
			send(s, sendBuff, sizeof(sendBuff), 0);
			printf("%s\n", sendBuff); // Comp.

// ----------------------------------------------------------------------------------------------------

			printf(
					"\n¡Supermercado eliminado correctamente! Pulse ENTER para continuar: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		} else if (opt == 'n') {
			manageSuperMenu(false);
		}

		logFile(INFO, "manageSuperMenu<<");
		manageSuperMenu(false);
		break;

	case 3:
		logFile(INFO,
				"Opción 3 de manageSuperMenu seleccionada (updateSupermarket())");

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
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWSMKTS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "\n" << endl;
			recv(s, recvBuff, sizeof(recvBuff), 0);
		}

		// ----------------------------------------------------------------------------------------------------

		logFile(INFO, "Lista completa de supermercados mostrada");

		if (b) {
			printf(
					"\n¡Lista completa de supermercados mostrada! Pulse ENTER para volver al menú principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		printf("\nIntroduzca el código del supermercado a actualizar: ");
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
				"\nIntroduzca la (posible nueva) dirección (separe la palabras con '_'): ");
		fflush(stdout);
		fgets(dir_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(dir_s, "%s", dir_s);

		printf("\nIntroduzca el (posible nuevo) teléfono: ");
		fflush(stdout);
		fgets(tlf_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(tlf_s, "%s", tlf_s);

		printf("\nIntroduzca los (posibles nuevos) metros cuadrados: ");
		fflush(stdout);
		fgets(metros_cuad_s, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(metros_cuad_s, "%s", metros_cuad_s);

		printf("\nIntroduzca el (posible nuevo) código de la ciudad: ");
		fflush(stdout);
		fgets(cod_ciu, MAX_LINE, stdin);
		fflush(stdin);
		sscanf(cod_ciu, "%s", cod_ciu);

		// EQUIVALENTE A updateSupermarketDB(sql, s) --------------------------------------------------

		// SENDING command UDSMKTDB
		strcpy(sendBuff, "UDSMKTDB");
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar cod_s
		strcpy(sendBuff, cod_s);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar nom_s
		strcpy(sendBuff, nom_s);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar dir_s
		strcpy(sendBuff, dir_s);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar tlf_s
		strcpy(sendBuff, tlf_s);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar metros_cuad_s
		strcpy(sendBuff, metros_cuad_s);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s ", sendBuff);

		// Enviar cod_ciu
		strcpy(sendBuff, cod_ciu);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("%s\n", sendBuff);

// ----------------------------------------------------------------------------------------------------

		printf(
				"\n¡Supermercado actualizado correctamente! Pulse ENTER para continuar: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logFile(INFO, "manageSuperMenu<<");
		manageSuperMenu(false);
		break;

	case 4:
		logFile(INFO,
				"Opción 4 de manageSuperMenu seleccionada (updateBDMenu<<)");
		updateBDMenu();
		break;
	}
}

// NIVEL DE MENÚ: 4
void updateBDMenu() {
	int opt;
	char str[10];

	printf("\n-------------\n");
	printf("ACTUALIZAR BD\n");
	printf("-------------\n\n");
	printf("1. Gestionar supermercados\n");
	printf("2. Gestionar productos\n");
	printf("3. Volver\n");
	printf("Introduzca una opción: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logFile(INFO,
				"Opción 1 de updateBDMenu seleccionada (>>manageSuperMenu)");
		manageSuperMenu(false);
		break;

	case 2:
		logFile(INFO,
				"Opción 2 de updateBDMenu seleccionada (>>manageProdMenu)");
		manageProdMenu(false);
		break;

	case 3:
		logFile(INFO, "Opción 3 de updateBDMenu seleccionada (adminMenu<<)");
		adminMenu();
		break;
	}
}

// NIVEL DE MENÚ: 3 (usuario) y 4 (administrador)
void queryBDMenu(bool b) {
	char strAux[2];
	int opt;
	char str[10];

	printf("\n-----------------\n");
	printf("CONSULTAS A LA BD\n");
	printf("-----------------\n\n");
	printf("1. Visualizar supermercados\n");
	printf("2. Visualizar productos\n");
	printf("3. Volver a menú principal\n");
	printf("Introduzca una opción: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logFile(INFO,
				"Opción 1 de queryBDMenu seleccionada (showSupermarkets)");

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
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWSMKTS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "\n" << endl;
			recv(s, recvBuff, sizeof(recvBuff), 0);
		}

		// --------------------------------------------------------------------------------

		logFile(INFO, "Lista completa de supermercados mostrada");

		if (b) {
			printf(
					"\n¡Lista completa de supermercados mostrada! Pulse ENTER para volver al menú principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 2:
		logFile(INFO, "Opción 2 de queryBDMenu seleccionada (showProducts)");

		if (b) {
			printf("\n---------------------------\n");
			printf("LISTA COMPLETA DE PRODUCTOS\n");
			printf("---------------------------\n\n");
		}

		printf("CODIGO || NOMBRE || PRECIO || DESCRIPCION\n\n");

		// EQUIVALENTE A showProducts(true) --------------------------------------------------

		// SENDING command SHOWPRODS
		strcpy(sendBuff, "SHOWPRODS");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWPRODS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);

		while (strcmp(recvBuff, "END")) {
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s || ", recvBuff);
			//cout << recvBuff << " || " << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
			printf("%s\n", recvBuff);
			//cout << recvBuff << "/n" << endl;

			recv(s, recvBuff, sizeof(recvBuff), 0);
		}

		// --------------------------------------------------------------------------------

		logFile(INFO, "Lista completa de productos mostrada");

		if (b) {
			printf(
					"\n¡Lista completa de productos mostrada! Pulse ENTER para volver al menú principal: ");
			fflush(stdout);
			fgets(strAux, 2, stdin);
			fflush(stdin);
		}

		logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 3:
		logFile(INFO, "Opción 3 de queryBDMenu seleccionada (mainMenu<<)");
		mainMenu(true);
		break;
	}
}

// NIVEL DE MENÚ: 3
void adminMenu() {
	char strAux[2];
	int opt;
	char str[10];

	printf("\n------------------\n");
	printf("MENÚ ADMINISTRADOR\n");
	printf("------------------\n\n");
	printf("1. Actualizar BD\n");
	printf("2. Consultas a la BD\n");
	printf("3. Estadísticas\n");
	printf("4. Volver al menú principal\n");
	printf("Introduzca una opción: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logFile(INFO, "Opción 1 de adminMenu seleccionada (>>updateBDMenu)");
		updateBDMenu();
		break;

	case 2:
		logFile(INFO, "Opción 2 de adminMenu seleccionada (>>queryBDMenu)");
		queryBDMenu(true);
		break;

	case 3:
		logFile(INFO, "Opción 3 de adminMenu seleccionada (showStatistics)");

		printf("\n------------\n");
		printf("ESTADÍSTICAS\n");
		printf("------------\n\n");

		// SENDING command SHOWSTATS
		strcpy(sendBuff, "SHOWSTATS");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWSTATS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
		printf("Media de los precios de los productos: %s\n", recvBuff);
//		cout << "Media de los precios de los productos: " << recvBuff << endl;

		recv(s, recvBuff, sizeof(recvBuff), 0);
		printf("Media de los metros cuadrados de los supermercados: %s\n",
				recvBuff);
//		cout << "Media de los metros cuadrados de los supermercados: " << recvBuff << endl;

		logFile(INFO, "Estadísticas mostradas");

		printf(
				"\n¡Estadísticas mostradas! Pulse ENTER para volver al menú principal: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 4:
		logFile(INFO, "Opción 4 de adminMenu seleccionada (mainMenu<<)");
		mainMenu(true);
		break;
	}
}

// NIVEL DE MENÚ: 2
void userMenu() {
	char strAux[2];
	int opt;
	char str[10];

	printf("\n------------\n");
	printf("MENÚ USUARIO\n");
	printf("------------\n\n");
	printf("1. Consultas a la BD\n");
	printf("2. Estadísticas\n");
	printf("3. Volver al menú principal\n");
	printf("Introduzca una opción: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logFile(INFO, "Opción 1 de userMenu seleccionada (>>queryBDMenu)");
		queryBDMenu(true);
		break;

	case 2:
		logFile(INFO, "Opción 2 de userMenu seleccionada (showStatistics)");

		printf("\n------------\n");
		printf("ESTADÍSTICAS\n");
		printf("------------\n\n");

		//fflush(stdout);

		// SENDING command SHOWSTATS
		strcpy(sendBuff, "SHOWSTATS");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWSTATS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
		printf("Media de los precios de los productos: %s\n", recvBuff);
//		cout << "Media de los precios de los productos: " << recvBuff << endl;

		recv(s, recvBuff, sizeof(recvBuff), 0);
		printf("Media de los metros cuadrados de los supermercados: %s\n",
				recvBuff);
//		cout << "Media de los metros cuadrados de los supermercados: " << recvBuff << endl;

		logFile(INFO, "Estadísticas mostradas");

		printf(
				"\n¡Estadísticas mostradas! Pulse ENTER para volver al menú principal: ");
		fflush(stdout);
		fgets(strAux, 2, stdin);
		fflush(stdin);

		logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 3:
		logFile(INFO, "Opción 3 de userMenu seleccionada (mainMenu<<)");
		mainMenu(true);
		break;
	}
}

// NIVEL DE MENÚ: 2
void adminAccessMenu() {
	int pass;
	char str[10];

	printf("\n--------------------\n");
	printf("ACCESO ADMINISTRADOR\n");
	printf("--------------------\n\n");
	printf(
			"Introduzca la clave (si quiere volver al menú principal pulse 'q' y para continuar pulse ENTER): ");
	fflush(stdout);
	fgets(str, 6, stdin);
	fflush(stdin);
	sscanf(str, "%i", &pass);

	int propPass;
	sscanf(properties.propValue[2], "%i", &propPass);

	if (pass == propPass) {
		logFile(INFO, "Contraseña de administrador correcta (>>adminMenu)");
		adminMenu();
	} else if (str[0] == 'q') {
		logFile(INFO, "mainMenu<<");
		mainMenu(true);
	} else {
		logFile(INFO, "adminAccessMenu<<");
		adminAccessMenu();
	}

}

// NIVEL DE MENÚ: 1
void mainMenu(bool b) {
	int opt;
	char str[10];

	loadProperties(&properties, "config.prop");

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
	printf("Introduzca una opción: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logFile(INFO, "Opción 1 de mainMenu seleccionada (>>userMenu)");
		userMenu();
		break;

	case 2:
		logFile(INFO, "Opción 2 de mainMenu seleccionada (>>adminMenu)");
		adminAccessMenu();
		break;

	case 3:
		logFile(END,
				"Opción 3 de mainMenu seleccionada (ejecución finalizada)");
		exit(0);
	}

}
