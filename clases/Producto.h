/*
 * Producto.h
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#ifndef CLASES_PRODUCTO_H_
#define CLASES_PRODUCTO_H_

class Producto {
public:
	int id_prod;
	char* nom_prod;
	double precio_prod;
	char* desc_prod;
public:
	Producto(int id_prod, char* nom_prod, double precio_prod, char* desc_prod);
	virtual ~Producto();
	char* getDescProd() const;
	void setDescProd(char *descProd);
	int getIdProd() const;
	void setIdProd(int idProd);
	char* getNomProd() const;
	void setNomProd(char *nomProd);
	double getPrecioProd() const;
	void setPrecioProd(double precioProd);
};

#endif /* CLASES_PRODUCTO_H_ */
