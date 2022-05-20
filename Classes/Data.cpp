/*
 * Data.cpp
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#include "Data.h"

Data::Data(Producto *productos, int num_prods, Supermercado *supermercados,
		int num_smkts) {
	Producto *p = new Producto[num_prods];
	for (int i = 0; i < num_prods; ++i) {
		p[i] = productos[i];
	}
	this->productos = p;

	this->num_prods = num_prods;

	Supermercado *s = new Supermercado[num_smkts];
	for (int i = 0; i < num_smkts; ++i) {
		s[i] = supermercados[i];
	}
	this->supermercados = s;

	this->num_smkts = num_smkts;
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

void Data::addProducto(Producto p) {
	Producto *prod = new Producto[num_prods];
	for (int i = 0; i < num_prods; ++i) {
		prod[i] = productos[i];
	}
	prod[num_prods] = p;
	this->productos = prod;
	this->num_prods++;
}
void Data::addSupermercado(Supermercado s) {
	Supermercado *smkt = new Supermercado[num_smkts];
	for (int i = 0; i < num_smkts; ++i) {
		smkt[i] = supermercados[i];
	}
	smkt[num_smkts] = s;
	this->supermercados = smkt;
	this->num_smkts++;
}
