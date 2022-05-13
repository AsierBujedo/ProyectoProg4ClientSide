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
	Producto* getArrayP();
	void setArrayP(Producto* prods);
	Supermercado* getArrayS();
	void setArrayS(Supermercado* smkts);
	int getNumProds();
	void setNumProds(int num);
	int getNumSmkts();
	void setNumSmkts(int num);

};

#endif /* CLASES_DATA_H_ */
