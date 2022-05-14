/*
 * Data.h
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#ifndef CLASSES_DATA_H_
#define CLASSES_DATA_H_

#include "Producto.h"
#include "Supermercado.h"

class Data {
	Producto *productos;
	int num_prods;
	Supermercado *supermercados;
	int num_smkts;
public:
	Data(Producto *productos, int num_prods, Supermercado *supermercados,
			int num_smkts);
	virtual ~Data();
	int getNumProds() const;
	void setNumProds(int numProds);
	int getNumSmkts() const;
	void setNumSmkts(int numSmkts);
	Producto*& getProductos();
	void setProductos(Producto *&productos);
	Supermercado*& getSupermercados();
	void setSupermercados(Supermercado *&supermercados);
};

#endif /* CLASSES_DATA_H_ */
