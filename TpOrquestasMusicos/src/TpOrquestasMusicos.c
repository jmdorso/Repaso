/*
 ============================================================================
 Name        : TpOrquestasMusicos.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "orquestas.h"
#include "instrumentos.h"
#include "musicos.h"

#define ALTA_OK 1
#define ALTA_DNS 0

int main(void)
{
	char seguir = 's';
	char salir;
	char confirmarBaja;
	char confirmarModif;
	Orquesta unaOrquestaAlta;
	Orquesta unaOrquestaBaja;
	Orquesta aOrquesta[CANT_ORQUESTAS];
	Instrumento unInstrumentoAlta;
	Instrumento aInstrumento[CANT_INSTRUMENTOS];
	Musico unMusicoAlta;
	Musico unMusicoBaja;
	Musico unMusicoModif;
	Musico aMusico[CANT_MUSICOS];
	int opcion;
	int flagAlta=ALTA_DNS;
	int auxId;
	int id;

	initLugarLibreOrquesta(aOrquesta,CANT_ORQUESTAS);
	initLugarLibreInstrumento(aInstrumento,CANT_INSTRUMENTOS);
	initLugarLibreMusico(aMusico,CANT_MUSICOS);

	do
	{
		printf("----------------------------------------------------------------------------------\n");
	    printf("\tModelo primer parcial 1_2019. Gestion de orquestas || Juan Martin Dorso\n\n");
	    printf("01. Agregar Orquesta\n");
	    printf("02. Eliminar Orquesta\n");
	    printf("03. Imprimir Orquestas\n");
	    printf("04. Agregar Musico\n");
	    printf("05. Modificar Musico\n");
	    printf("06. Eliminar Musico\n");
	    printf("07. Imprimir Musicos\n");
	    printf("08. Agregar Instrumento\n");
	    printf("09. Imprimir Instrumentos\n");
	    printf("10. Informar\n");
	    printf("11. Salir\n\n");

	    if(getValidIntFromString(&opcion,"\tIngrese opcion: ","\nError",1,11,CANT_REINTENTOS)==0)
	    {
	    	switch(opcion)
	    	{
	    		case 1:
	    				if(altaUnaSolaOrquestaPorUI(&unaOrquestaAlta)==EXIT_SUCCESS)
	    				{
	    					auxId=altaOrquestaPorId(aOrquesta,CANT_ORQUESTAS,unaOrquestaAlta);
	    					if(auxId>EXIT_SUCCESS)
	    					{
			    				flagAlta=ALTA_OK;
			    				printf("\n\nSe ingreso la orquesta con ID: # %d\n\n",auxId);
	    					}
	    				}
	    				break;
	    		case 2:
						imprimirArrayOrquestasStatusOk(aOrquesta,CANT_ORQUESTAS);
						getValidIntFromString(&auxId,"\nIngrese el ID: ","\nError\n",1,CANT_ORQUESTAS,CANT_REINTENTOS);
						unaOrquestaBaja.id = auxId;
						auxId = buscarOrquestaPorId(aOrquesta,CANT_ORQUESTAS,unaOrquestaBaja.id);
						if(aOrquesta[auxId].status== STATUS_NOT_EMPTY)
						{
							printf("Quiere Eliminar la siguiente Orquesta: \n");
							printf("Nombre: %s - Lugar: %s - ID: %d",aOrquesta[auxId].nombre,aOrquesta[auxId].lugar,aOrquesta[auxId].id);
							getChar(&confirmarBaja,
									"\nSeguro desea dar de baja? Ingrese s (o cualquier tecla para continuar): ",
									"\nERROR. Verifique si ingreso una letra y/o desactive mayuscula\n",
									'a',
									'z',
									CANT_REINTENTOS);
							if(confirmarBaja == 's' || confirmarBaja == 'S')
							{
								if(bajaOrquestaPorId(aOrquesta,CANT_ORQUESTAS,unaOrquestaBaja.id)==EXIT_SUCCESS)
								{
									printf("\nBAJA EXITOSA\n\n");
								}
								else
								{
									printf("\nERROR EN BAJA\n\n");
								}
							}
						}
						else
						{
							printf("\n\nNo existe orquesta con ese ID\n\n");
						}
						break;
	    		case 3:
	    				imprimirArrayOrquestasStatusOk(aOrquesta,CANT_ORQUESTAS);
	    				break;
	    		case 4:
						if(altaUnSoloMusicoPorUI(&unMusicoAlta,aOrquesta,CANT_ORQUESTAS,aInstrumento,CANT_INSTRUMENTOS)==EXIT_SUCCESS)
						{
							auxId=altaMusicoPorId(aMusico,CANT_MUSICOS,unMusicoAlta);
							if(auxId>EXIT_SUCCESS)
							{
								flagAlta=ALTA_OK;
								printf("\n\nSe ingreso un Musico con ID: # %d\n\n",auxId);
							}
						}
						break;
	    		case 7:
	    				imprimirArrayMusicosStatusOk(aMusico,CANT_MUSICOS,aInstrumento,CANT_INSTRUMENTOS);
	    				break;
	    		case 8:
	    				if(altaUnSoloInstrumentoPorUI(&unInstrumentoAlta)==EXIT_SUCCESS)
	       				{
	    					auxId=altaInstrumentoPorId(aInstrumento,CANT_INSTRUMENTOS,unInstrumentoAlta);
	  				    	if(auxId>EXIT_SUCCESS)
	    				    {
	    						flagAlta=ALTA_OK;
	    						printf("\n\nSe ingreso el instrumento con ID: # %d\n\n",auxId);
	    				    }
	       				}
	    				break;
	    		case 9:
	    				imprimirArrayInstrumentosStatusOk(aInstrumento,CANT_INSTRUMENTOS);
	    				break;
	    		case 11:
	    				getChar(&salir,
	    						"\nSeguro desea salir? Ingrese s (o cualquier tecla para continuar): ",
	    						"\nERROR. Verifique si ingreso una letra y/o desactive mayuscula\n",
								'a',
	    						'z',
								CANT_REINTENTOS);
	    				if(salir == 's' || salir == 'S')
	    			     {
	    					printf("\n\n\tEl programa se cerrara.");
	    			        seguir = 'n';
	    			     }
	       				break;
	    	}
	    }
	}while(seguir=='s' || seguir=='S');

	return EXIT_SUCCESS;
}
