/*
 * orquestas.c
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

static int generarIdInstrumento(void)
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

int initLugarLibreInstrumento(Instrumento *aArray, int cantidad)
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

int altaInstrumentoPorId(Instrumento *aArray, int cantidad,Instrumento instrumento)
{
	int retorno = EXIT_ERROR;
	int posArray;

	if(aArray != NULL && cantidad >0)
	{
		posArray = buscarLugarLibreInstrumento(aArray,cantidad);
		if(posArray >= 0 && buscarInstrumentoPorId(aArray,cantidad,instrumento.id) == -1)
			{
				instrumento.status=STATUS_NOT_EMPTY;
				instrumento.id=generarIdInstrumento();
				aArray[posArray] = instrumento;
				retorno = instrumento.id;
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

int buscarLugarLibreInstrumento(Instrumento *aArray, int cantidad)
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

/** \brief busca el elemento con el ID indicado en el array
 * \param *aArray es el array de Instrumentos
 * \param cantidad es la cantidad de elementos del array
 * \param id es el ID a buscar
 * \return -1 si hay algun error o la POSICION EN EL ARRAY del elemento con dicho ID
 *
 */

int buscarInstrumentoPorId(Instrumento *aArray, int cantidad,int id)
{
	int retorno = EXIT_ERROR;
	int posArray;

	if(aArray != NULL && cantidad >0 && id >= 0)
	{
		for(posArray=0;posArray<cantidad;posArray++)
		{
			if(aArray[posArray].status == STATUS_NOT_EMPTY)
			{
				if(aArray[posArray].id == id)
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

int altaUnSoloInstrumentoPorUI(Instrumento *instrumento)
{
	int retorno = EXIT_ERROR;
	char bufferNombre[CANT_CARACTERES];
	int bufferTipo;

	getString(bufferNombre,"\nIngrese Nombre: ","\nError",1,CANT_CARACTERES,CANT_REINTENTOS);
	retorno = esNombreOApellido(bufferNombre,"No es un nombre valido");
	if(retorno == EXIT_SUCCESS)
	{
		retorno = getInt(&bufferTipo,"\nIngrese Tipo: 1[Cuerda] - 2[Percusion] - 3[Viento-Madera] - 4[Viento-Metal]: ",
				"\nError",1,4,CANT_REINTENTOS);
		if(retorno == EXIT_SUCCESS)
		{
			strncpy(instrumento->nombre,bufferNombre,CANT_CARACTERES);
			instrumento->tipo=bufferTipo;
		}
	}
	return retorno;
}

/** \brief imprime el array completo sin exepciones de campos
 * \param *aArray es el array de isntrumentos
 * \param cantidad es la cantidad de elementos del array
 * \return -1 si hay algun error o 0 si esta bien
 *
 */

int imprimirArrayInstrumentos(Instrumento *aArray, int cantidad)
{
	int i;
	int retorno = EXIT_ERROR;
	char tipoInstrumento[4][25] = {"Cuerda","Percusion","Viento-Madera","Viento-Metal"};

	if(aArray != NULL && cantidad>0)
	{
		retorno = EXIT_SUCCESS;
		printf("\n--------------------------------LISTA DE INSTRUMENTOS--------------------------------\n");
		printf("%6s | %3s | %15s | %11s\n","STATUS","ID","NOMBRE","TIPO");
		for(i=0;i<cantidad;i++)
		{
			printf("%6d | %3d | %15s | %11s\n",
			aArray[i].status,aArray[i].id,aArray[i].nombre,tipoInstrumento[aArray[i].tipo-1]);
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

int imprimirArrayInstrumentosStatusOk(Instrumento *aArray, int cantidad)
{
	int i;
	int retorno = EXIT_ERROR;
	char tipoInstrumento[4][25] = {"Cuerda","Percusion","Viento-Madera","Viento-Metal"};


	if(aArray != NULL && cantidad>0)
	{
		retorno = EXIT_SUCCESS;
		printf("\n--------------------------------LISTA DE INSTRUMENTOS--------------------------------\n");
		printf("%3s | %15s | %11s\n","ID","NOMBRE","TIPO");
		for(i=0;i<cantidad;i++)
		{
			if(aArray[i].status==STATUS_NOT_EMPTY)
			{
				printf("%3d | %15s | %11s\n",
				aArray[i].id,aArray[i].nombre,tipoInstrumento[aArray[i].tipo-1]);
			}
		}
	}
	return retorno;
}
