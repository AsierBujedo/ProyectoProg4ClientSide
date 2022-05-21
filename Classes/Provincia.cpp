/*
 * Provincia.cpp
 *
 *  Created on: 20 may. 2022
 *      Author: Iker López
 */

#include "Provincia.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

Provincia::Provincia() {

}

Provincia::Provincia(int cod_prov, char *nom_prov) {
	this->cod_prov = cod_prov;

	this->nom_prov = new char[strlen(nom_prov) + 1];
	strcpy(this->nom_prov, nom_prov);
}

Provincia::~Provincia() {

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
	this->nom_prov = new char[strlen(nomProv) + 1];
	strcpy(this->nom_prov, nomProv);
}
