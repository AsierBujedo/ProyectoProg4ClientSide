/*
 * main.cpp
 *
 *  Created on: 18 mar. 2022
 *      Author: asier
 */

#include "Menu/Menu.h"
#include "Classes/Data.h"
#include "Logger/Logger.h"
#include <stdio.h>

int main() {
	Menu menu;
	Properties prop;
	Logger logger;

	logger.openLogger("marketlog.log");
	menu.setLogger(&logger);
	prop.setLogger(&logger);
	FILE *file;
	if ((file = fopen("config.prop", "r"))) {
		fclose(file);
		prop.loadProperties(&prop, "config.prop");
		menu.setProperties(&prop);
	} else {
		prop.numProp = 3;
		char **propName = new char*[sizeof(char*) * prop.numProp];
		propName[0] = "IP_DESTINATION";
		propName[1] = "PORT";
		propName[2] = "ADMIN_PASS";
		prop.propName = propName;

		char **propValues = new char*[sizeof(char*) * prop.numProp];
		propValues[0] = "127.0.0.1";
		propValues[1] = "1024";
		propValues[2] = "11111";
		prop.propValue = propValues;

		prop.createProperties(&prop, "config.prop");
		menu.setProperties(&prop);
	}

	menu.prepareSocket();
	logger.closeLogger();

	return 0;
}
