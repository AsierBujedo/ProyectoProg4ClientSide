/*
 * Data.h
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#ifndef CLASES_DATA_H_
#define CLASES_DATA_H_

#include "../clases/Producto.h"
#include "../clases/Supermercado.h"

class Data {
	Producto* productos;
	int num_prods;
	Supermercado* supermercados;
	int num_smkts;
public:
	Data();
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

#endif /* CLASES_DATA_H_ */
