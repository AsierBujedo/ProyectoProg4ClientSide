/*
 * Provincia.h
 *
 *  Created on: 20 may. 2022
 *      Author: Iker López
 */

#ifndef CLASSES_PROVINCIA_H_
#define CLASSES_PROVINCIA_H_

class Provincia {
public:
	int cod_prov;
	char *nom_prov;
public:
	Provincia();
	Provincia(int cod_prov, char *nom_provincia);
	virtual ~Provincia();
	Provincia(const Provincia &other);
	int getCodProv();
	void setCodProv(int codProv);
	char* getNomProv();
	void setNomProv(char *nomProv);
};

#endif /* CLASSES_PROVINCIA_H_ */
