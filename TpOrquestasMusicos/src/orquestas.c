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

static int generarIdOrquesta(void)
{
	static int idIncremental=0;
	idIncremental++;

	return idIncremental;
}

/** \brief Inicializa un array de Orquestas con el estado libre(es decir, un array vacio y listo para cargar)
 * \param *aArray es el array de orquestas
 * \param cantidad es la cantidad de elementos del array
 * \return -1 si hay algun error o 0 si esta bien.
 *
 */

int initLugarLibreOrquesta(Orquesta *aArray, int cantidad)
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

/** \brief Da de alta una orquesta (previamente cargada) en el array (en la primer posicion libre que encuentra)
 * \param *aArray es el array de orquestas
 * \param cantidad es la cantidad de elementos del array
 * \return -1 si hay algun error o el ID si esta bien.
 *
 */

int altaOrquestaPorId(Orquesta *aArray, int cantidad,Orquesta orquesta)
{
	int retorno = EXIT_ERROR;
	int posArray;

	if(aArray != NULL && cantidad >0)
	{
		posArray = buscarLugarLibreOrquesta(aArray,cantidad);
		if(posArray >= 0 && buscarOrquestaPorId(aArray,cantidad,orquesta.id) == -1)
			{
				orquesta.status=STATUS_NOT_EMPTY;
				orquesta.id=generarIdOrquesta();
				aArray[posArray] = orquesta;
				retorno = orquesta.id;
			}
	}
	return retorno;
}

/** \brief busca el primer lugar libre en el array
 * \param *aArray es el array de orquestas
 * \param cantidad es la cantidad de elementos del array
 * \return -1 si hay algun error o la POSICION EN EL ARRAY del primer elemento libre
 *
 */

int buscarLugarLibreOrquesta(Orquesta *aArray, int cantidad)
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
 * \param *aArray es el array de Orquestas
 * \param cantidad es la cantidad de elementos del array
 * \param id es el ID a buscar
 * \return -1 si hay algun error o la POSICION EN EL ARRAY del elemento con dicho ID
 *
 */

int buscarOrquestaPorId(Orquesta *aArray, int cantidad,int id)
{
	int retorno = EXIT_ERROR;
	int posArray;

	if(aArray != NULL && cantidad >0 && id >= 0)
	{
		for(posArray=0;posArray<cantidad;posArray++)
		{
			if(aArray[posArray].status == 1)
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


/** \brief le damos de alta a una orquesta a traves de interaccion con el usuario
 * \param *orquesta una variable del tipo Orquesta
 * \return -1 si hay algun error o 0 si esta bien
 *
 */

int altaUnaSolaOrquestaPorUI(Orquesta *orquesta)
{
	int retorno = EXIT_ERROR;
	char bufferNombre[CANT_CARACTERES];
	char bufferLugar[CANT_CARACTERES];
	int bufferTipo;

	getString(bufferNombre,"\nIngrese Nombre: ","\nError",1,CANT_CARACTERES,CANT_REINTENTOS);
	retorno = esNombreOApellido(bufferNombre,"No es un nombre valido");
	if(retorno == EXIT_SUCCESS)
	{
		getString(bufferLugar,"\nIngrese Lugar: ","\nError",1,CANT_CARACTERES,CANT_REINTENTOS);
		retorno = esAlfaNumerico(bufferLugar,"No es un lugar valido");
		if(retorno == EXIT_SUCCESS)
		{
			retorno = getInt(&bufferTipo,"\nIngrese Tipo: 1[Camara] - 2[Filarmonica] - 3[Sinfonica]: ",
					"\nError",1,3,CANT_REINTENTOS);
			if(retorno == EXIT_SUCCESS)
			{
				strncpy(orquesta->nombre,bufferNombre,CANT_CARACTERES);
				strncpy(orquesta->lugar,bufferLugar,CANT_CARACTERES);
				orquesta->tipo=bufferTipo;
			}
		}
	}
	return retorno;
}

/** \brief imprime el array completo sin exepciones de campos
 * \param *aArray es el array de orquestas
 * \param cantidad es la cantidad de elementos del array
 * \return -1 si hay algun error o 0 si esta bien
 *
 */

int imprimirArrayOrquestas(Orquesta *aArray, int cantidad)
{
	int i;
	int retorno = EXIT_ERROR;
	char tipoOrquesta[3][25] = {"Camara","Filarmonica","Sinfonica"};

	if(aArray != NULL && cantidad>0)
	{
		retorno = EXIT_SUCCESS;
		printf("\n--------------------------------LISTA DE ORQUESTAS--------------------------------\n");
		printf("%6s | %3s | %15s | %15s | %11s\n","STATUS","ID","NOMBRE","LUGAR","TIPO");
		for(i=0;i<cantidad;i++)
		{
			printf("%6d | %3d | %15s | %15s | %11s\n",
			aArray[i].status,aArray[i].id,aArray[i].nombre,aArray[i].lugar,tipoOrquesta[aArray[i].tipo-1]);
		}
	}
	return retorno;
}

/** \brief imprime elementos del array con el campo stado NOT EMPTY(es decir elementos cargados)
 * \param *aArray es el array de orquestas
 * \param cantidad es la cantidad de elementos del array
 * \return -1 si hay algun error o 0 si esta bien
 *
 */

int imprimirArrayOrquestasStatusOk(Orquesta *aArray, int cantidad)
{
	int i;
	int retorno = EXIT_ERROR;
	char tipoOrquesta[3][25] = {"Camara","Filarmonica","Sinfonica"};

	if(aArray != NULL && cantidad>0)
	{
		retorno = EXIT_SUCCESS;
		printf("\n--------------------------------LISTA DE ORQUESTAS--------------------------------\n");
		printf("%3s | %15s | %15s | %11s\n","ID","NOMBRE","LUGAR","TIPO");
		for(i=0;i<cantidad;i++)
		{
			if(aArray[i].status==STATUS_NOT_EMPTY)
			{
				printf("%3d | %15s | %15s | %11s\n",
				aArray[i].id,aArray[i].nombre,aArray[i].lugar,tipoOrquesta[aArray[i].tipo-1]);
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

int bajaOrquestaPorId(Orquesta *aArray, int cantidad,int id)
{

	int retorno = EXIT_ERROR;
	int posArray;
	if(aArray != NULL && cantidad>0 && id>=0)
	{
		posArray = buscarOrquestaPorId(aArray,cantidad,id);
		if(posArray != -1)
		{
			aArray[posArray].status = STATUS_EMPTY;
			retorno = EXIT_SUCCESS;
		}
	}
	return retorno;
}
