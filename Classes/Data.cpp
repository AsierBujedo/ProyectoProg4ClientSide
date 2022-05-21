/*
 * Data.cpp
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#include "Data.h"

Data::Data() {
	this->provincias = new Provincia[0];
	this->num_provincias = 0;
	this->ciudades = new Ciudad[0];
	this->num_ciudades = 0;
}

Data::Data(Provincia *provincias, int num_provincias, Ciudad *ciudades,
		int num_ciudades) {
	this->provincias = new Provincia[num_provincias];
	for (int i = 0; i < num_provincias; ++i) {
		this->provincias[i] = provincias[i];
	}

	this->num_provincias = num_provincias;

	this->ciudades = new Ciudad[num_ciudades];
	for (int i = 0; i < num_ciudades; ++i) {
		this->ciudades[i] = ciudades[i];
	}

	this->num_ciudades = num_ciudades;
}

Data::~Data() {
	delete[] provincias;
	delete[] ciudades;
}

Data::Data(const Data &other) {
	this->provincias = new Provincia[other.num_provincias];
	for (int i = 0; i < other.num_provincias; ++i) {
		this->provincias[i] = other.provincias[i];
	}

	this->num_provincias = other.num_provincias;

	this->ciudades = new Ciudad[other.num_ciudades];
	for (int i = 0; i < other.num_ciudades; ++i) {
		this->ciudades[i] = other.ciudades[i];
	}

	this->num_ciudades = other.num_ciudades;
}

Ciudad*& Data::getCiudades() {
	return ciudades;
}

void Data::setCiudades(Ciudad *&ciudades) {
	this->ciudades = ciudades;
}

int Data::getNumCiudades() {
	return num_ciudades;
}

void Data::setNumCiudades(int numCiudades) {
	num_ciudades = numCiudades;
}

int Data::getNumProvincias() {
	return num_provincias;
}

void Data::setNumProvincias(int numProvincias) {
	num_provincias = numProvincias;
}

Provincia*& Data::getProvincias() {
	return provincias;
}

void Data::setProvincias(Provincia *&provincias) {
	this->provincias = provincias;
}

void Data::addProvincia(Provincia p) {
	Provincia *provincias = new Provincia[num_provincias];
	for (int i = 0; i < num_provincias; ++i) {
		provincias[i] = this->provincias[i];
	}
	provincias[num_provincias] = p;
	this->provincias = provincias;
	this->num_provincias++;
}

void Data::addCiudad(Ciudad c) {
	Ciudad *ciudades = new Ciudad[num_ciudades];
	for (int i = 0; i < num_ciudades; ++i) {
		ciudades[i] = this->ciudades[i];
	}
	ciudades[num_ciudades] = c;
	this->ciudades = ciudades;
	this->num_ciudades++;
}
