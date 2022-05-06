/*
 * menu.h
 *
 *  Created on: 1 abr. 2022
 *      Author: Iker López
 */

#ifndef MENU_MENU_H_
#define MENU_MENU_H_
#include <stdbool.h>

int prepareSocket();
void mainMenu(bool b);
void adminAccessMenu();
void userMenu();
void adminMenu();
void queryBDMenu(bool b); // Se ha añadido el argumento bool b
void updateBDMenu();
void manageSuperMenu(bool b); // Se ha añadido el argumento bool b
void manageProdMenu(bool b); // Se ha añadido el argumento bool b

#endif /* MENU_MENU_H_ */
