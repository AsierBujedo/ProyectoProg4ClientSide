/*
 * Supermercado.h
 *
 *  Created on: 14 may. 2022
 *      Author: Iker López
 */

#ifndef CLASSES_SUPERMERCADO_H_
#define CLASSES_SUPERMERCADO_H_

class Supermercado {
public:
	int cod_s;
	char *nom_s;
	char *dir_s;
	int tlf_s;
	double metros_cuad_s;
	int cod_ciu;
public:
	Supermercado();
	Supermercado(int cod_s, char *nom_s, char *dir_s, int tlf_s,
			double metros_cuad_s, int cod_ciu);
	virtual ~Supermercado();
	int getCodCiu() const;
	void setCodCiu(int codCiu);
	int getCodS() const;
	void setCodS(int codS);
	char* getDirS() const;
	void setDirS(char *dirS);
	double getMetrosCuadS() const;
	void setMetrosCuadS(double metrosCuadS);
	char* getNomS() const;
	void setNomS(char *nomS);
	int getTlfS() const;
	void setTlfS(int tlfS);
};

#endif /* CLASSES_SUPERMERCADO_H_ */
