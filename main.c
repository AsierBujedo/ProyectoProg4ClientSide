/*
 * main.c
 *
 *  Created on: 18 mar. 2022
 *      Author: asier
 */

#include "menu/menu.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "logger/logger.h"
#include "properties/properties.h"

int main() {
	openLogger("marketlog.log");
	Properties prop;
	FILE *file;
	if ((file = fopen("config.prop", "r"))) {
		fclose(file);
		loadProperties(&prop, "config.prop");
	} else {
		prop.numProp = 12;
		char **propName = malloc(sizeof(char*) * prop.numProp);
		propName[0] = "IP";
		propName[1] = "PORT";
		propName[2] = "ADMIN_PASS";
		propName[3] = "DEBUG";
		propName[4] = "DATABASE_DIR";
		propName[5] = "CITY_DIR";
		propName[6] = "EMPLOYEE_DIR";
		propName[7] = "PRODUCT_DIR";
		propName[8] = "PROVINCE_DIR";
		propName[9] = "SUPERMARKET_DIR";
		propName[10] = "WORKS_DIR";
		propName[11] = "SELLS_DIR";
		prop.propName = propName;

		char **propValues = malloc(sizeof(char*) * prop.numProp);
		propValues[0] = "127.0.0.1";
		propValues[1] = "1024";
		propValues[2] = "11111";
		propValues[3] = "1";
		propValues[4] = "DeustoMarket.db";
		propValues[5] = "dataSource/ciudad.csv";
		propValues[6] = "dataSource/empleado.csv";
		propValues[7] = "dataSource/producto.csv";
		propValues[8] = "dataSource/provincia.csv";
		propValues[9] = "dataSource/supermercado.csv";
		propValues[10] = "dataSource/trabaja.csv";
		propValues[11] = "dataSource/vende.csv";
		prop.propValue = propValues;

		createProperties(&prop, "config.prop");
	}

	mainMenu(false);
	closeLogger();

	return 0;
}
