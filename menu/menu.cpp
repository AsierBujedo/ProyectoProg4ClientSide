
/*
 * menu.cpp
 *
 *  Created on: 3 may. 2022
 *      Author: Iker L�pez
 */

extern "C" {
#include "menu.h"
#include "../logger/logger.h"
#include "../properties/properties.h"
}

//#include "menu.h"
//#include "../handler/server/server.h"
//#include "../functions/functions.h"
//#include "../handler/logger/logger.h"
//#include "../handler/properties/properties.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <iostream>

using namespace std;

Properties properties;
SOCKET s;
char sendBuff[512], recvBuff[512];
#define SERVER_IP "127.0.0.1" // Fichero de configuraci�n
#define SERVER_PORT 6000 // Fichero de configuraci�n

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

// NIVEL DE MEN�: 5 (administrador)
void manageProdMenu() {
	char str[512];
	char strAux[2];
	int id_prod;
	char nom_prod[128];
	double precio_prod;
	char desc_prod[128];

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
		logFile(INFO, "Opci�n 1 de manageProdMenu seleccionada (addProduct)");

		printf("\n---------------\n");
		printf("A�ADIR PRODUCTO\n");
		printf("---------------\n\n");

		printf("\nIntroduzca el c�digo: ");
			fflush(stdout);
			fgets(str, 512, stdin);
			fflush(stdin);
			sscanf(str, "%i", &id_prod);

			printf("\nIntroduzca el nombre (separe la palabras con '_'): ");
			fflush(stdout);
			fgets(nom_prod, 512, stdin);
			fflush(stdin);
			sscanf(nom_prod, "%s", nom_prod);

			printf("\nIntroduzca el precio: ");
			fflush(stdout);
			fgets(str, 512, stdin);
			fflush(stdin);
			sscanf(str, "%lf", &precio_prod);

			printf("\nIntroduzca la descripci�n (separe la palabras con '_'): ");
			fflush(stdout);
			fgets(desc_prod, 512, stdin);
			fflush(stdin);
			sscanf(desc_prod, "%s", desc_prod);



		// SENDING command ADDPROD
		strcpy(sendBuff, "ADDPROD");

		//FALTA PROBAR; IGUAL EL CASTEO DA PROBLEMAS
		char* precio_char;

		sprintf(precio_char,"%f",precio_prod);

		strcpy(sendBuff, (char*) id_prod);
		strcpy(sendBuff, nom_prod);
		strcpy(sendBuff, precio_char);
		strcpy(sendBuff, desc_prod);

		strcpy(sendBuff, "ADDPROD-END");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command ADDPROD from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
//		printf("Suma = %s \n", recvBuff);
		cout << " " << endl;

		logFile(INFO, "manageProdMenu<<");
		manageProdMenu();
		break;

	case 2:
		logFile(INFO,
				"Opci�n 2 de manageProdMenu seleccionada (deleteProduct)");

		// SENDING command DELPROD
		strcpy(sendBuff, "DELPROD");
		strcpy(sendBuff, "DELPROD-END");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command DELPROD from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
//		printf("Suma = %s \n", recvBuff);
		cout << " " << endl;

		logFile(INFO, "manageProdMenu<<");
		manageProdMenu();
		break;

	case 3:
		logFile(INFO,
				"Opci�n 3 de manageProdMenu seleccionada (updateProduct)");

		// SENDING command UDPROD
		strcpy(sendBuff, "UDPROD");
		strcpy(sendBuff, "UDPROD-END");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command UDPROD from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
//		printf("Suma = %s \n", recvBuff);
		cout << " " << endl;

		logFile(INFO, "manageProdMenu<<");
		manageProdMenu();
		break;

	case 4:
		logFile(INFO,
				"Opci�n 4 de manageProdMenu seleccionada (updateBDMenu<<)");
		updateBDMenu();
		logFile(INFO, "manageProdMenu<<");
		manageProdMenu();
		break;
	}
}

// NIVEL DE MEN�: 5 (administrador)
void manageSuperMenu() {
	int opt;
	char str[10];

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
		logFile(INFO,
				"Opci�n 1 de manageSuperMenu seleccionada (addSupermarket)");

		// SENDING command ADDSMKT
		strcpy(sendBuff, "ADDSMKT");
		strcpy(sendBuff, "ADDSMKT-END");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command ADDSMKT from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
//		printf("Suma = %s \n", recvBuff);
		cout << " " << endl;

		logFile(INFO, "manageSuperMenu<<");
		manageSuperMenu();
		break;

	case 2:
		logFile(INFO,
				"Opci�n 2 de manageSuperMenu seleccionada (deleteSupermarket)");

		// SENDING command DELSMKT
		strcpy(sendBuff, "DELSMKT");
		strcpy(sendBuff, "DELSMKT-END");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command DELSMKT from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
//		printf("Suma = %s \n", recvBuff);
		cout << " " << endl;

		logFile(INFO, "manageSuperMenu<<");
		manageSuperMenu();
		break;

	case 3:
		logFile(INFO,
				"Opci�n 3 de manageSuperMenu seleccionada (updateSupermarket())");

		// SENDING command UDSMKT
		strcpy(sendBuff, "UDSMKT");
		strcpy(sendBuff, "UDSMKT-END");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command UDSMKT from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
//		printf("Suma = %s \n", recvBuff);
		cout << " " << endl;

		logFile(INFO, "manageSuperMenu<<");
		manageSuperMenu();
		break;

	case 4:
		logFile(INFO,
				"Opci�n 4 de manageSuperMenu seleccionada (updateBDMenu<<)");
		updateBDMenu();
		break;
	}
}

// NIVEL DE MEN�: 4
void updateBDMenu() {
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
		logFile(INFO,
				"Opci�n 1 de updateBDMenu seleccionada (>>manageSuperMenu)");
		manageSuperMenu();
		break;

	case 2:
		logFile(INFO,
				"Opci�n 2 de updateBDMenu seleccionada (>>manageProdMenu)");
		manageProdMenu();
		break;

	case 3:
		logFile(INFO, "Opci�n 3 de updateBDMenu seleccionada (adminMenu<<)");
		adminMenu();
		break;
	}
}

// NIVEL DE MEN�: 3 (usuario) y 4 (administrador)
void queryBDMenu() {
	int opt;
	char str[10];

	printf("\n-----------------\n");
	printf("CONSULTAS A LA BD\n");
	printf("-----------------\n\n");
	printf("1. Visualizar supermercados\n");
	printf("2. Visualizar productos\n");
	printf("3. Volver a men� principal\n");
	printf("Introduzca una opci�n: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logFile(INFO,
				"Opci�n 1 de queryBDMenu seleccionada (showSupermarkets)");

		// SENDING command SHOWSMKTS
		strcpy(sendBuff, "SHOWSMKTS");
		strcpy(sendBuff, "SHOWSMKTS-END");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWSMKTS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
//		printf("Suma = %s \n", recvBuff);
		cout << " " << endl;

		logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 2:
		logFile(INFO, "Opci�n 2 de queryBDMenu seleccionada (showProducts)");

		// SENDING command SHOWPRODS
		strcpy(sendBuff, "SHOWPRODS");
		strcpy(sendBuff, "SHOWPRODS-END");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWPRODS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
//		printf("Suma = %s \n", recvBuff);
		cout << " " << endl;

		logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 3:
		logFile(INFO, "Opci�n 3 de queryBDMenu seleccionada (mainMenu<<)");
		mainMenu(true);
		break;
	}
}

// NIVEL DE MEN�: 3
void adminMenu() {
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
		logFile(INFO, "Opci�n 1 de adminMenu seleccionada (>>updateBDMenu)");
		updateBDMenu();
		break;

	case 2:
		logFile(INFO, "Opci�n 2 de adminMenu seleccionada (>>queryBDMenu)");
		queryBDMenu();
		break;

	case 3:
		logFile(INFO, "Opci�n 3 de adminMenu seleccionada (showStatistics)");

		// SENDING command SHOWSTATS
		strcpy(sendBuff, "SHOWSTATS");
		strcpy(sendBuff, "SHOWSTATS-END");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWSTATS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
//		printf("Suma = %s \n", recvBuff);
		cout << " " << endl;

		logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 4:
		logFile(INFO, "Opci�n 4 de adminMenu seleccionada (mainMenu<<)");
		mainMenu(true);
		break;
	}
}

// NIVEL DE MEN�: 2
void userMenu() {
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
		logFile(INFO, "Opci�n 1 de userMenu seleccionada (>>queryBDMenu)");
		queryBDMenu();
		break;

	case 2:
		logFile(INFO, "Opci�n 2 de userMenu seleccionada (showStatistics)");

		// SENDING command SHOWSTATS
		strcpy(sendBuff, "SHOWSTATS");
		strcpy(sendBuff, "SHOWSTATS-END");
		send(s, sendBuff, sizeof(sendBuff), 0);

		// RECEIVING response to command SHOWSTATS from the server
		recv(s, recvBuff, sizeof(recvBuff), 0);
//		printf("Suma = %s \n", recvBuff);
		cout << " " << endl;

		logFile(INFO, "mainMenu<<");
		mainMenu(true);
		break;

	case 3:
		logFile(INFO, "Opci�n 3 de userMenu seleccionada (mainMenu<<)");
		mainMenu(true);
		break;
	}
}

// NIVEL DE MEN�: 2
void adminAccessMenu() {
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
	sscanf(properties.propValue[2], "%i", &propPass);

	if (pass == propPass) {
		logFile(INFO, "Contrase�a de administrador correcta (>>adminMenu)");
		adminMenu();
	} else if (str[0] == 'q') {
		logFile(INFO, "mainMenu<<");
		mainMenu(true);
	} else {
		logFile(INFO, "adminAccessMenu<<");
		adminAccessMenu();
	}

}

// NIVEL DE MEN�: 1
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
	printf("Introduzca una opci�n: ");
	fflush(stdout);
	fgets(str, 2, stdin);
	fflush(stdin);
	sscanf(str, "%i", &opt);

	switch (opt) {
	case 1:
		logFile(INFO, "Opci�n 1 de mainMenu seleccionada (>>userMenu)");
		userMenu();
		break;

	case 2:
		logFile(INFO, "Opci�n 2 de mainMenu seleccionada (>>adminMenu)");
		adminAccessMenu();
		break;

	case 3:
		logFile(END,
				"Opci�n 3 de mainMenu seleccionada (ejecuci�n finalizada)");
		exit(0);
	}

}

