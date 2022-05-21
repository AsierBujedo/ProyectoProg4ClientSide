/*
 * Data.h
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#ifndef CLASSES_DATA_H_
#define CLASSES_DATA_H_

#include "Ciudad.h"
#include "Provincia.h"

class Data {
public:
	Provincia *provincias;
	int num_provincias;
	Ciudad *ciudades;
	int num_ciudades;
public:
	Data();
	Data(Provincia *provincias, int num_provincias, Ciudad *ciudades,
			int num_ciudades);
	virtual ~Data();
	Data(const Data &other);
	Ciudad*& getCiudades();
	void setCiudades(Ciudad *&ciudades);
	int getNumCiudades();
	void setNumCiudades(int numCiudades);
	int getNumProvincias();
	void setNumProvincias(int numProvincias);
	Provincia*& getProvincias();
	void setProvincias(Provincia *&provincias);
	void addProvincia(Provincia p);
	void addCiudad(Ciudad c);
};

#endif /* CLASSES_DATA_H_ */
