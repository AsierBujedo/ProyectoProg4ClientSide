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

Producto* Data::getArrayP() {
	return this->productos;
}
void Data::setArrayP(Producto* prods) {
	this->productos =  prods;
}
Supermercado* Data::getArrayS() {
	return this->supermercados;
}
void Data::setArrayS(Supermercado* smkts) {
	this->supermercados = smkts;
}

int Data::getNumProds() {
	return this->num_prods;
}
void Data::setNumProds(int num) {
	this->num_prods = num;
}
int Data::getNumSmkts() {
	return this->num_smkts;
}
void Data::setNumSmkts(int num) {
	this->num_smkts = num;
}

