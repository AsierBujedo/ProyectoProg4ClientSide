/*
 * Logger.cpp
 *
 *  Created on: 19 mar. 2022
 *      Author: asier
 */

#include "Logger.h"
#include "../Properties/Properties.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static FILE *f;

void Logger::openLogger(char name[]) {
	f = fopen(name, "w");
	fprintf(f,
			"------------------------------\nFichero log - DEUSTOMARKET\n------------------------------\n");
	fprintf(stderr,
			"\n------------------------------\nFichero log - DEUSTOMARKET\n------------------------------\n");
}

int Logger::closeLogger() {
	fprintf(f, "\n\nFINAL DEL ARCHIVO");
	return fclose(f);
}

void Logger::logFile(LEVEL l, char desc[]) {

	if (l == INFO) {
		char buffer[100];
		strcat(strcpy(buffer, "\n[INFO]   "), desc);
		fprintf(f, buffer);
		fprintf(stderr, buffer);
	} else if (l == WARN) {
		char buffer[100];
		strcat(strcpy(buffer, "\n[WARN]   "), desc);
		fprintf(f, buffer);
		fprintf(stderr, buffer);
	} else if (l == ERRORL) {
		char buffer[100];
		strcat(strcpy(buffer, "\n[ERROR]   "), desc);
		fprintf(f, buffer);
		fprintf(stderr, buffer);
	} else if (l == END) {
		char buffer[100];
		strcat(strcpy(buffer, "\n[END]   "), desc);
		fprintf(f, buffer);
		fprintf(stderr, buffer);
	}
}
