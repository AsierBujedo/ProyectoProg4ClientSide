/*
 * Ciudad.cpp
 *
 *  Created on: 20 may. 2022
 *      Author: Iker López
 */

#include "Ciudad.h"
#include <string.h>

Ciudad::Ciudad() {

}

Ciudad::Ciudad(int cod_ciu, char *nom_ciu, int cod_prov) {
	this->cod_ciu = cod_ciu;

	this->nom_ciu = new char[strlen(nom_ciu) + 1];
	strcpy(this->nom_ciu, nom_ciu);

	this->cod_prov = cod_prov;
}

Ciudad::~Ciudad() {
	delete[] nom_ciu;
}

Ciudad::Ciudad(const Ciudad &other) {
	this->cod_ciu = other.cod_ciu;

	this->nom_ciu = new char[strlen(other.nom_ciu) + 1];
	strcpy(this->nom_ciu, other.nom_ciu);

	this->cod_prov = other.cod_prov;
}

int Ciudad::getCodCiu() {
	return cod_ciu;
}

void Ciudad::setCodCiu(int codCiu) {
	cod_ciu = codCiu;
}

int Ciudad::getCodProv() {
	return cod_prov;
}

void Ciudad::setCodProv(int codProv) {
	cod_prov = codProv;
}

char* Ciudad::getNomCiu() {
	return nom_ciu;
}

void Ciudad::setNomCiu(char *nomCiu) {
	nom_ciu = nomCiu;
}

