/*
 * Menu.h
 *
 *  Created on: 1 abr. 2022
 *      Author: Iker López
 */
#include <stdbool.h>
#include <winsock2.h>

#include "../Classes/Data.h"
#include "../Logger/Logger.h"
#include "../Properties/Properties.h"

#ifndef MENU_H_
#define MENU_H_

class Menu {
public:
	Data *data;
	SOCKET *s;
	Properties *prop;
	Logger *logger;
public:
	int prepareSocket();
	void mainMenu(bool b);
	void adminAccessMenu();
	void userMenu();
	void adminMenu();
	void queryBDMenu(bool b); // Se ha añadido el argumento bool b
	void updateBDMenu();
	void manageSuperMenu(bool b); // Se ha añadido el argumento bool b
	void manageProdMenu(bool b); // Se ha añadido el argumento bool b
	void setProperties(Properties *prop);
	void setLogger(Logger *logger);
	void setData(Data d);
};

#endif /* MENU_H_ */
