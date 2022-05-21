/*
 * Provincia.cpp
 *
 *  Created on: 20 may. 2022
 *      Author: Iker López
 */

#include "Provincia.h"
#include <string.h>

Provincia::Provincia() {

}

Provincia::Provincia(int cod_prov, char *nom_prov) {
	this->cod_prov = cod_prov;

	this->nom_prov = new char[strlen(nom_prov) + 1];
	strcpy(this->nom_prov, nom_prov);
}

Provincia::~Provincia() {
	delete[] nom_prov;
}

Provincia::Provincia(const Provincia &other) {
	this->cod_prov = other.cod_prov;

	this->nom_prov = new char[strlen(other.nom_prov) + 1];
	strcpy(this->nom_prov, other.nom_prov);
}

int Provincia::getCodProv() {
	return cod_prov;
}

void Provincia::setCodProv(int codProv) {
	cod_prov = codProv;
}

char* Provincia::getNomProv() {
	return nom_prov;
}

void Provincia::setNomProv(char *nomProv) {
	nom_prov = nomProv;
}

