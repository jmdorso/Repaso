/*
 * musicos.c
 *
 *  Created on: Oct 8, 2019
 *      Author: mati
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "orquestas.h"
#include "instrumentos.h"
#include "musicos.h"

/** \brief va generando un ID secuencial cada vez que es llamada
 * \param void, no recibe ningun paramentro.
 * \return el id incrementado cada vez que es llamada(debido a que esta declarada como static
 * no pierde el valor anterior)
 *
 */

static int generarIdMusico(void)
{
	static int idIncremental=0;
	idIncremental++;

	return idIncremental;
}

/** \brief Inicializa un array de Instrumentos con el estado libre(es decir, un array vacio y listo para cargar)
 * \param *aArray es el array de Instrumentos
 * \param cantidad es la cantidad de elementos del array
 * \return -1 si hay algun error o 0 si esta bien.
 *
 */

int initLugarLibreMusico(Musico *aArray, int cantidad)
{
	int retorno = EXIT_ERROR;
	int i;

	if(aArray != NULL && cantidad >0)
	{
		for(i=0;i<cantidad;i++)
		{
			aArray[i].status = STATUS_EMPTY;
		}
	retorno = EXIT_SUCCESS;
	}
	return retorno;
}

/** \brief Da de alta un Instrumento (previamente cargado) en el array (en la primer posicion libre que encuentra)
 * \param *aArray es el array de Instrumentos
 * \param cantidad es la cantidad de elementos del array
 * \return -1 si hay algun error o el ID si esta bien.
 *
 */

int altaMusicoPorId(Musico *aArray, int cantidad,Musico musico)
{
	int retorno = EXIT_ERROR;
	int posArray;

	if(aArray != NULL && cantidad >0)
	{
		posArray = buscarLugarLibreMusico(aArray,cantidad);
		if(posArray >= 0 && buscarMusicoPorId(aArray,cantidad,musico.idMusico) == -1)
			{
				musico.status=STATUS_NOT_EMPTY;
				musico.idMusico=generarIdMusico();
				aArray[posArray] = musico;
				retorno = musico.idMusico;
			}
	}
	return retorno;
}

/** \brief busca el primer lugar libre en el array
 * \param *aArray es el array de instrumentos
 * \param cantidad es la cantidad de elementos del array
 * \return -1 si hay algun error o la POSICION EN EL ARRAY del primer elemento libre
 *
 */

int buscarLugarLibreMusico(Musico *aArray, int cantidad)
{
	int retorno = EXIT_ERROR;
	int posArray;

	if(aArray != NULL && cantidad >0)
	{
		for(posArray=0;posArray<cantidad;posArray++)
		{
			if(aArray[posArray].status == STATUS_EMPTY)
			{
				retorno = posArray;
				break;
			}
		}
	}
	return retorno;
}

int buscarMusicoPorId(Musico *aArray, int cantidad,int id)
{
	int retorno = EXIT_ERROR;
	int posArray;

	if(aArray != NULL && cantidad >0 && id >= 0)
	{
		for(posArray=0;posArray<cantidad;posArray++)
		{
			if(aArray[posArray].status == STATUS_NOT_EMPTY)
			{
				if(aArray[posArray].idMusico == id)
				{
				retorno = posArray;
				break;
				}
			}
		}
	}
	return retorno;
}

/** \brief le damos de alta un instrumento a traves de interaccion con el usuario
 * \param *instrumento una variable del tipo instrumento
 * \return -1 si hay algun error o 0 si esta bien
 *
 */

int altaUnSoloMusicoPorUI(Musico *musico,Orquesta *aOrquesta,int cantOrquesta,Instrumento *aInstrumento,int cantInstrumento)
{
	int retorno = EXIT_ERROR;
	char bufferNombre[CANT_CARACTERES];
	char bufferApellido[CANT_CARACTERES];
	int bufferEdad;
	int bufferIdOrq;
	int auxIdOrq;
	int bufferIdInst;
	int auxIdInst;

	getString(bufferNombre,"\nIngrese Nombre: ","\nError",1,CANT_CARACTERES,CANT_REINTENTOS);
	retorno = esNombreOApellido(bufferNombre,"No es un nombre valido");
	if(retorno == EXIT_SUCCESS)
	{
		getString(bufferApellido,"\nIngrese Apellido: ","\nError",1,CANT_CARACTERES,CANT_REINTENTOS);
		retorno = esNombreOApellido(bufferApellido,"No es un nombre valido");
		if(retorno == EXIT_SUCCESS)
		{
			retorno = getInt(&bufferEdad,"\nIngrese Edad: ","\nError",1,100,CANT_REINTENTOS);
			if(retorno == EXIT_SUCCESS)
			{
				imprimirArrayOrquestasStatusOk(aOrquesta,cantOrquesta);
				retorno = getInt(&bufferIdOrq,"\nIngrese ID de la orquesta que participa: ","\nError",1,CANT_ORQUESTAS,CANT_REINTENTOS);
				if(retorno == EXIT_SUCCESS);
				{
					if(buscarOrquestaPorId(aOrquesta,cantOrquesta,bufferIdOrq)>=0)
					{
						imprimirArrayInstrumentosStatusOk(aInstrumento,cantInstrumento);
						retorno = getInt(&bufferIdInst,"\nIngrese ID del instrumento que toca: ","\nError",1,CANT_INSTRUMENTOS,CANT_REINTENTOS);
						if(retorno == EXIT_SUCCESS);
						{
							if(buscarInstrumentoPorId(aInstrumento,cantInstrumento,bufferIdInst)>=0)
							{
								strncpy(musico->nombre,bufferNombre,CANT_CARACTERES);
								strncpy(musico->apellido,bufferApellido,CANT_CARACTERES);
								musico->edad=bufferEdad;
								musico->idOrquesta=bufferIdOrq;
								musico->idInstrumento=bufferIdInst;
							}
							else
							{
								retorno=EXIT_ERROR;
							}
						}
					}
					else
					{
						retorno=EXIT_ERROR;
					}
				}
			}
		}
	}
	return retorno;
}

/** \brief imprime el array completo sin exepciones de campos
 * \param *aArray es el array de empleados
 * \param cantidad es la cantidad de elementos del array
 * \return -1 si hay algun error o 0 si esta bien
 *
 */

int imprimirArrayMusicos(Musico *aArray, int cantidad,Instrumento *aInst,int cantInst)
{
	int i;
	int auxId;
	int retorno = EXIT_ERROR;
	char tipoInstrumento[4][25] = {"Cuerda","Percusion","Viento-Madera","Viento-Metal"};

	if(aArray != NULL && cantidad>0)
	{
		retorno = EXIT_SUCCESS;
		printf("\n--------------------------------LISTA DE MUSICOS--------------------------------\n");
		printf("%6s | %3s | %15s | %15s | %3s | %15s | %15s\n","STATUS","ID","NOMBRE","APELLIDO","EDAD","INSTRUMENTO","TIPO");
		for(i=0;i<cantidad;i++)
		{
			auxId = buscarInstrumentoPorId(aInst,cantInst,aArray[i].idInstrumento);
			printf("%6d | %3d | %15s | %15s | %3d | %15s | %15s\n",
			aArray[i].status,aArray[i].idMusico,aArray[i].nombre,aArray[i].apellido,aArray[i].edad,aInst[auxId].nombre,tipoInstrumento[aInst[auxId].tipo-1]);
		}
	}
	return retorno;
}

/** \brief imprime elementos del array con el campo stado NOT EMPTY(es decir elementos cargados)
 * \param *aArray es el array de instrumentos
 * \param cantidad es la cantidad de elementos del array
 * \return -1 si hay algun error o 0 si esta bien
 *
 */

int imprimirArrayMusicosStatusOk(Musico *aArray, int cantidad,Instrumento *aInst,int cantInst)
{
	int i;
	int auxId;
	int retorno = EXIT_ERROR;
	char tipoInstrumento[4][25] = {"Cuerda","Percusion","Viento-Madera","Viento-Metal"};

	if(aArray != NULL && cantidad>0)
	{
		retorno = EXIT_SUCCESS;
		printf("\n--------------------------------LISTA DE MUSICOS--------------------------------\n");
		printf("%3s | %15s | %15s | %3s | %15s | %15s\n","ID","NOMBRE","APELLIDO","EDAD","INSTRUMENTO","TIPO");
		for(i=0;i<cantidad;i++)
		{
			if(aArray[i].status==STATUS_NOT_EMPTY)
			{
				auxId = buscarInstrumentoPorId(aInst,cantInst,aArray[i].idInstrumento);
				printf("%3d | %15s | %15s | %3d | %15s | %15s\n",
				aArray[i].idMusico,aArray[i].nombre,aArray[i].apellido,aArray[i].edad,aInst[auxId].nombre,tipoInstrumento[aInst[auxId].tipo-1]);
			}
		}
	}
	return retorno;
}

/** \brief busca una orquesta por ID y la da de baja mediante el campo status (dejandolo EMPTY)
 * \param *aArray es el array de orquestas
 * \param cantidad es la cantidad de elementos del array
 * \param id es el ID a buscar
 * \return -1 si hay algun error o 0 si esta bien.
 *
 */

int bajaMusicoPorId(Musico *aArray, int cantidad,int id)
{

	int retorno = EXIT_ERROR;
	int posArray;
	if(aArray != NULL && cantidad>0 && id>=0)
	{
		posArray = buscarMusicoPorId(aArray,cantidad,id);
		if(posArray != -1)
		{
			aArray[posArray].status = STATUS_EMPTY;
			retorno = EXIT_SUCCESS;
		}
	}
	return retorno;
}
