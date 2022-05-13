/*
 * Producto.cpp
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#include "../clases/Producto.h"

Producto::Producto(int id_prod, char* nom_prod, double precio_prod, char* desc_prod) {
	this->id_prod = id_prod;
	this->nom_prod = nom_prod;
	this->precio_prod = precio_prod;
	this->desc_prod = desc_prod;
}

Producto::~Producto() {
	delete this->nom_prod;
	delete this->desc_prod;
}

int Producto::getID() {
	return this->id_prod;
}

void Producto::setID(int id) {
	this->id_prod = id;
}

char* Producto::getName() {
	return this->nom_prod;
}

void Producto::setName(char* name) {
	this->nom_prod = name;
}

double Producto::getPrecio() {
	return this->precio_prod;
}

void Producto::setPrecio(double precio) {
	this->precio_prod = precio;
}

char* Producto::getDesc() {
	return this->desc_prod;
}

void Producto::setDesc(char* desc) {
	this->desc_prod = desc;
}
