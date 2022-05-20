/*
 * Producto.h
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#ifndef CLASSES_PRODUCTO_H_
#define CLASSES_PRODUCTO_H_

class Producto {
public:
	int id_prod;
	char *nom_prod;
	double precio_prod;
	char *desc_prod;
public:
	Producto();
	Producto(int id_prod, char *nom_prod, double precio_prod, char *desc_prod);
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

#endif /* CLASSES_PRODUCTO_H_ */
