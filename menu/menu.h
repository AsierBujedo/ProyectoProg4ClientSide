/*
 * menu.h
 *
 *  Created on: 1 abr. 2022
 *      Author: Iker López
 */
#include <stdbool.h>

#ifndef MENU_H_
#define MENU_H_

int prepareSocket();
void mainMenu(bool b);
void adminAccessMenu();
void userMenu();
void adminMenu();
void queryBDMenu(bool b); // Se ha añadido el argumento bool b
void updateBDMenu();
void manageSuperMenu(bool b); // Se ha añadido el argumento bool b
void manageProdMenu(bool b); // Se ha añadido el argumento bool b

#endif /* MENU_H_ */
