/*
 * Properties.h
 *
 *  Created on: 1 abr. 2022
 *      Author: asier
 */

#include "../Logger/Logger.h"

#ifndef PROPERTIES_H_
#define PROPERTIES_H_

class Properties {
public:
	int numProp;
	char **propName;
	char **propValue;
private:
	Logger *logger;
public:
	void loadProperties(Properties *properties, char name[]);
	void createProperties(Properties *properties, char name[]);
	void allocate(Properties *prop, char name[]);
	void setLogger(Logger *logger);
};

#endif /* PROPERTIES_H_ */
