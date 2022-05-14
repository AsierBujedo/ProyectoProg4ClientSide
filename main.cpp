/*
 * main.c
 *
 *  Created on: 18 mar. 2022
 *      Author: asier
 */

extern "C" {
#include "menu/menu.h"
#include "logger/logger.h"
#include "functions/functions.h"
}

int main() {
	init();
	prepareSocket();
	closeLogger();

	return 0;
}
