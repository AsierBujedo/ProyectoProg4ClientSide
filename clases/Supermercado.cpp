/*
 * Supermercado.cpp
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#include "../clases/Supermercado.h"

Supermercado::Supermercado(int cod_s, char* nom_s, char* dir_s, int tlf_s, double metros_cuad_s, int cod_ciu) {
	this->cod_s = cod_s;
	this->nom_s = nom_s;
	this->dir_s = dir_s;
	this->tlf_s = tlf_s;
	this->metros_cuad_s = metros_cuad_s;
	this->cod_ciu = cod_ciu;
}

Supermercado::~Supermercado() {
	delete this->nom_s;
	delete this->dir_s;
}

int Supermercado::getCodCiu() const {
	return this->cod_ciu;
}

void Supermercado::setCodCiu(int codCiu) {
	this->cod_ciu = codCiu;
}

int Supermercado::getCodS() const {
	return this->cod_s;
}

void Supermercado::setCodS(int codS) {
	this->cod_s = codS;
}

char* Supermercado::getDirS() const {
	return this->dir_s;
}

void Supermercado::setDirS(char *dirS) {
	this->dir_s = dirS;
}

double Supermercado::getMetrosCuadS() const {
	return this->metros_cuad_s;
}

void Supermercado::setMetrosCuadS(double metrosCuadS) {
	this->metros_cuad_s = metrosCuadS;
}

char* Supermercado::getNomS() const {
	return this->nom_s;
}

void Supermercado::setNomS(char *nomS) {
	this->nom_s = nomS;
}

int Supermercado::getTlfS() const {
	return this->tlf_s;
}

void Supermercado::setTlfS(int tlfS) {
	this->tlf_s = tlfS;
}
