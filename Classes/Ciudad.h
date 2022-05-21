/*
 * Ciudad.h
 *
 *  Created on: 20 may. 2022
 *      Author: Iker López
 */

#ifndef CLASSES_CIUDAD_H_
#define CLASSES_CIUDAD_H_

class Ciudad {
public:
	int cod_ciu;
	char *nom_ciu;
	int cod_prov;
public:
	Ciudad();
	Ciudad(int cod_ciu, char *nom_ciu, int cod_prov);
	virtual ~Ciudad();
	Ciudad(const Ciudad &other);
	int getCodCiu();
	void setCodCiu(int codCiu);
	int getCodProv();
	void setCodProv(int codProv);
	char* getNomCiu();
	void setNomCiu(char *nomCiu);
};

#endif /* CLASSES_CIUDAD_H_ */
