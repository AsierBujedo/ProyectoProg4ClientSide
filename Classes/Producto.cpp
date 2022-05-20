/*
 * Producto.cpp
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#include "Producto.h"

#include <string.h>

Producto::Producto() {
}

Producto::Producto(int id_prod, char *nom_prod, double precio_prod,
		char *desc_prod) {
	this->id_prod = id_prod;

	this->nom_prod = new char[strlen(nom_prod) + 1];
	strcpy(this->nom_prod, nom_prod);

	this->precio_prod = precio_prod;

	this->desc_prod = new char[strlen(desc_prod) + 1];
	strcpy(this->desc_prod, desc_prod);
}

Producto::~Producto() {
	delete this->nom_prod;
	delete this->desc_prod;
}

char* Producto::getDescProd() const {
	return desc_prod;
}

void Producto::setDescProd(char *descProd) {
	desc_prod = descProd;
}

int Producto::getIdProd() const {
	return id_prod;
}

void Producto::setIdProd(int idProd) {
	id_prod = idProd;
}

char* Producto::getNomProd() const {
	return nom_prod;
}

void Producto::setNomProd(char *nomProd) {
	nom_prod = nomProd;
}

double Producto::getPrecioProd() const {
	return precio_prod;
}

void Producto::setPrecioProd(double precioProd) {
	precio_prod = precioProd;
}

