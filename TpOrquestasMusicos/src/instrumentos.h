/*
 * instrumentos.h
 *
 *  Created on: Oct 8, 2019
 *      Author: mati
 */

#ifndef INSTRUMENTOS_H_
#define INSTRUMENTOS_H_

#define STATUS_EMPTY 0
#define STATUS_NOT_EMPTY 1
#define CANT_CARACTERES 51
#define CANT_REINTENTOS 2
#define CANT_INSTRUMENTOS 20

typedef struct
{
	int id;
	int status;
	//***************
	char nombre[51];
	int tipo;

}Instrumento;

static int generarIdInstrumento(void);

int initLugarLibreInstrumento(Instrumento *aArray, int cantidad);
int altaInstrumentoPorId(Instrumento *aArray, int cantidad,Instrumento instrumento);
int buscarLugarLibreInstrumento(Instrumento *aArray, int cantidad);
int buscarInstrumentoPorId(Instrumento *aArray, int cantidad,int id);
int altaUnSoloInstrumentoPorUI(Instrumento *instrumento);
int imprimirArrayInstrumentos(Instrumento *aArray, int cantidad);
int imprimirArrayInstrumentosStatusOk(Instrumento *aArray, int cantidad);

#endif /* INSTRUMENTOS_H_ */
