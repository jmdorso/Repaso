/*
 * orquestas.h
 *
 *  Created on: Oct 8, 2019
 *      Author: mati
 */

#ifndef ORQUESTAS_H_
#define ORQUESTAS_H_

#define STATUS_EMPTY 0
#define STATUS_NOT_EMPTY 1
#define CANT_CARACTERES 51
#define CANT_REINTENTOS 2
#define CANT_ORQUESTAS 50

typedef struct
{
	int id;
	int status;
	//***************
	char nombre[51];
	char lugar[51];
	int tipo;

}Orquesta;

static int generarIdOrquesta(void);

int initLugarLibreOrquesta(Orquesta *aArray, int cantidad);
int altaOrquestaPorId(Orquesta *aArray, int cantidad,Orquesta orquesta);
int buscarLugarLibreOrquesta(Orquesta *aArray, int cantidad);
int buscarOrquestaPorId(Orquesta *aArray, int cantidad,int id);
int altaUnaSolaOrquestaPorUI(Orquesta *orquesta);
int imprimirArrayOrquestas(Orquesta *aArray, int cantidad);
int imprimirArrayOrquestasStatusOk(Orquesta *aArray, int cantidad);
int bajaOrquestaPorId(Orquesta *aArray, int cantidad,int id);

#endif /* ORQUESTAS_H_ */
