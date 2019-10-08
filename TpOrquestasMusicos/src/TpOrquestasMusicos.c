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
#include <limits.h>
#include "utn.h"


int main(void) {
	char texto[50];
	int rdo;
	float altura;

	/*getString(texto,"Ingrese numero","\nError!",1,50,2);
	if(esSoloNumeros(texto,"\nNo es un numero valido")==0)
	{
		printf("%s",texto);
	}
	getString(texto,"Ingrese numero flotante","\nError!",1,50,2);
	if(esSoloNumerosFlotantes(texto,"\nNo es un numero valido")==0)
	{
		printf("%s",texto);
	}
	getString(texto,"Ingrese texto Alfa Numerico","\nError!",1,50,2);
	if(esAlfaNumerico(texto,"\nEl texto contiene un caracter no deseado, solo letras, numeros y espacios")==0)
	{
		printf("\n%s",texto);
	}*/
	rdo = 5;
	printf("\n\nEn la variable rdo esta cargado el num # %d\n\n",rdo);
	getValidIntFromString(&rdo,"Ingrese numero entero","\nError. Ingrese solo numeros",	INT_MIN,INT_MAX,2);
	printf("\n\nEn la variable rdo esta cargado el num # %d\nSi lo multiplico por 2 el resultado es %d\n",rdo,rdo*2);

	altura = 1.76;
	printf("\n\nEn la variable altura esta cargado el num # %.2f\n\n",altura);
	getValidFloatFromString(&altura,"Ingrese numero Flotante","\nError. Ingrese solo numeros",	INT_MIN,INT_MAX,2);
	printf("\n\nEn la variable altura esta cargado el num # %.2f\nSi crecio 5cm el resultado es %.2f\n",altura,altura+0.05);
	return EXIT_SUCCESS;
}
