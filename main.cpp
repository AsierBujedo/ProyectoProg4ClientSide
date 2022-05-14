/*
 * main.c
 *
 *  Created on: 18 mar. 2022
 *      Author: asier
 */
extern "C" {
#include "func/func.h"
#include "menu/menu.h"
#include "logger/logger.h"
#include "properties/properties.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

int main() {


	prepareSocket();
	closeLogger();

	return 0;
}
