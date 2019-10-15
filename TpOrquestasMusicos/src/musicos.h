/*
 * musicos.h
 *
 *  Created on: Oct 8, 2019
 *      Author: mati
 */

#ifndef MUSICOS_H_
#define MUSICOS_H_

#define STATUS_EMPTY 0
#define STATUS_NOT_EMPTY 1
#define CANT_CARACTERES 51
#define CANT_REINTENTOS 2
#define CANT_MUSICOS 1000

typedef struct
{
	int idMusico;
	int status;
	//***************
	char nombre[51];
	char apellido[51];
	int edad;
	int idOrquesta;
	int idInstrumento;

}Musico;

static int generarIdMusico(void);

int initLugarLibreMusico(Musico *aArray, int cantidad);
int altaMusicoPorId(Musico *aArray, int cantidad,Musico musico);
int buscarLugarLibreMusico(Musico *aArray, int cantidad);
int buscarMusicoPorId(Musico *aArray, int cantidad,int id);
int altaUnSoloMusicoPorUI(Musico *musico,Orquesta *aOrquesta,int cantOrquesta,Instrumento *aInstrumento,int cantInstrumento);
int imprimirArrayMusicos(Musico *aArray, int cantidad,Instrumento *aInst,int cantInst);
int imprimirArrayMusicosStatusOk(Musico *aArray, int cantidad,Instrumento *aInst,int cantInst);
int bajaMusicoPorId(Musico *aArray, int cantidad,int id);

#endif /* MUSICOS_H_ */
