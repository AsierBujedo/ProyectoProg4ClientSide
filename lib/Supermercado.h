/*
 * Supermercado.h
 *
 *  Created on: 13 may 2022
 *      Author: asier
 */

#ifndef LIB_SUPERMERCADO_H_
#define LIB_SUPERMERCADO_H_

class Supermercado {
public:
	int cod_s;
	char* nom_s;
	char* dir_s;
	int tlf_s;
	double metros_cuad_s;
	int cod_ciu;
public:
	Supermercado(int cod_s, char* nom_s, char* dir_s, int tlf_s, double metros_cuad_s, int cod_ciu);
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

#endif /* LIB_SUPERMERCADO_H_ */
