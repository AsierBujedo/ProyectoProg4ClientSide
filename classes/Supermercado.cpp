/*
 * Supermercado.cpp
 *
 *  Created on: 14 may. 2022
 *      Author: Iker López
 */

#include "Supermercado.h"

#include "Supermercado.h"
#include <string.h>

Supermercado::Supermercado() {
}

Supermercado::Supermercado(int cod_s, char *nom_s, char *dir_s, int tlf_s,
		double metros_cuad_s, int cod_ciu) {
	this->cod_s = cod_s;

	this->nom_s = new char[strlen(nom_s) + 1];
	strcpy(this->nom_s, nom_s);

	this->dir_s = new char[strlen(dir_s) + 1];
	strcpy(this->dir_s, dir_s);

	this->tlf_s = tlf_s;
	this->metros_cuad_s = metros_cuad_s;
	this->cod_ciu = cod_ciu;
}

Supermercado::~Supermercado() {
	delete this->nom_s;
	delete this->dir_s;
}

int Supermercado::getCodCiu() const {
	return cod_ciu;
}

void Supermercado::setCodCiu(int codCiu) {
	cod_ciu = codCiu;
}

int Supermercado::getCodS() const {
	return cod_s;
}

void Supermercado::setCodS(int codS) {
	cod_s = codS;
}

char* Supermercado::getDirS() const {
	return dir_s;
}

void Supermercado::setDirS(char *dirS) {
	dir_s = dirS;
}

double Supermercado::getMetrosCuadS() const {
	return metros_cuad_s;
}

void Supermercado::setMetrosCuadS(double metrosCuadS) {
	metros_cuad_s = metrosCuadS;
}

char* Supermercado::getNomS() const {
	return nom_s;
}

void Supermercado::setNomS(char *nomS) {
	nom_s = nomS;
}

int Supermercado::getTlfS() const {
	return tlf_s;
}

void Supermercado::setTlfS(int tlfS) {
	tlf_s = tlfS;
}

