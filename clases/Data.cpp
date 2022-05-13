/*
 * Data.cpp
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#include "../clases/Data.h"

Data::Data() {
}

Data::~Data() {
	delete this->productos;
	delete this->supermercados;
}

int Data::getNumProds() const {
	return num_prods;
}

void Data::setNumProds(int numProds) {
	num_prods = numProds;
}

int Data::getNumSmkts() const {
	return num_smkts;
}

void Data::setNumSmkts(int numSmkts) {
	num_smkts = numSmkts;
}

Producto*& Data::getProductos() {
	return productos;
}

void Data::setProductos(Producto *&productos) {
	this->productos = productos;
}

Supermercado*& Data::getSupermercados() {
	return supermercados;
}

void Data::setSupermercados(Supermercado *&supermercados) {
	this->supermercados = supermercados;
}
