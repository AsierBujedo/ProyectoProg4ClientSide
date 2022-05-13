/*
 * Producto.h
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#ifndef LIB_PRODUCTO_H_
#define LIB_PRODUCTO_H_

class Producto {
public:
	int id_prod;
	char* nom_prod;
	double precio_prod;
	char* desc_prod;
public:
	Producto(int id_prod, char* nom_prod, double precio_prod, char* desc_prod);
	virtual ~Producto();
	int getID();
	void setID(int id);
	char* getName();
	void setName(char* name);
	double getPrecio();
	void setPrecio(double precio);
	char* getDesc();
	void setDesc(char* desc);
};

#endif /* LIB_PRODUCTO_H_ */
