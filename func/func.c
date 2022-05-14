/*
 * func.c
 *
 *  Created on: 14 may 2022
 *      Author: asier
 */

#include "func.h"
#include "../logger/logger.h"
#include "../properties/properties.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init() {
	openLogger("marketlog.log");
	Properties prop;
	FILE *file;
	if ((file = fopen("config.prop", "r"))) {
		fclose(file);
		loadProperties(&prop, "config.prop");
	} else {
		prop.numProp = 3;
		char **propName = malloc(sizeof(char*) * prop.numProp);
		propName[0] = "IP_DESTINATION";
		propName[1] = "PORT";
		propName[2] = "ADMIN_PASS";
		prop.propName = propName;

		char **propValues = malloc(sizeof(char*) * prop.numProp);
		propValues[0] = "127.0.0.1";
		propValues[1] = "1024";
		propValues[2] = "11111";
		prop.propValue = propValues;

		createProperties(&prop, "config.prop");
	}
}
