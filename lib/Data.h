/*
 * Data.h
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#ifndef LIB_DATA_H_
#define LIB_DATA_H_

#include "Producto.h"
#include "Supermercado.h"

class Data {
	Producto* productos;
	int num_prods;
	Supermercado* supermercados;
	int num_smkts;
public:
	Data();
	virtual ~Data();
	Producto* getArrayP();
	void setArrayP(Producto* prods);
	Supermercado* getArrayS();
	void setArrayS(Supermercado* smkts);
	int getNumProds();
	void setNumProds(int num);
	int getNumSmkts();
	void setNumSmkts(int num);

};

#endif /* LIB_DATA_H_ */
