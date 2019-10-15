/*
 * informes.c
 *
 *  Created on: Oct 9, 2019
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
#include "informes.h"





int menuInformes(Pedidos *aArrayPed, int cantPed, Clientes *aArrayClientes, int cantClientes, auxContador *aArrayCont, int cantCont)
{
	int retorno= EXIT_ERROR;
	char opcion;
	int id;
	float acumulador;
	while(getChar(&opcion, "Ingrese una opcion de informes\n  a)Cantidad maxima de desechos\n    b)Suma total.\n    c)Suma total por cuit\n", "NO es una opcion valida.",'a','z',3)!=0)
			{
				printf("ERROR.\n ");
			}
	switch (opcion)
	{
	case 'a':
		//buscarPedidoConMasDesechos(aArrayPed,cantPed);
		buscarCuitConMasDesechos (aArrayClientes, cantClientes, aArrayPed,cantPed);
		break;
	case 'b':
		sumaTotalesDeDesechos(aArrayPed,cantPed,&acumulador);
		printf("La suma total de desechos es: %.2f \n",acumulador);
		sumaTotalesDeResiduosPorTipo(aArrayPed, cantPed,1,&acumulador);
		printf("La suma total de HDPE es: %.2f \n",acumulador);
		sumaTotalesDeResiduosPorTipo(aArrayPed, cantPed,2,&acumulador);
		printf("La suma total de LDPE es: %.2f \n",acumulador);
		sumaTotalesDeResiduosPorTipo(aArrayPed, cantPed,3,&acumulador);
		printf("La suma total de PP es: %.2f \n",acumulador);
		sumaTotalesDeResiduosPorTipo(aArrayPed, cantPed,4,&acumulador);
		printf("La suma total de desechos es: %.2f \n",acumulador);
		sumaTotalesDeResiduosPorTipo(aArrayPed, cantPed,5,&acumulador);
		printf("La suma total de residuos es: %.2f \n",acumulador);
		break;
	case 'c':
		ordenarPorIdCliente(aArrayPed,cantPed);
		cantidadKilosPorTipoPorCuit(aArrayPed, cantPed, aArrayCont, cantCont,aArrayClientes,cantClientes,1);
		printf("\n");
		cantidadKilosPorTipoPorCuit(aArrayPed, cantPed, aArrayCont, cantCont,aArrayClientes,cantClientes,2);
		printf("\n");
		cantidadKilosPorTipoPorCuit(aArrayPed, cantPed, aArrayCont, cantCont,aArrayClientes,cantClientes,3);
		printf("\n");
		cantidadKilosPorTipoPorCuit(aArrayPed, cantPed, aArrayCont, cantCont,aArrayClientes,cantClientes,4);
		printf("\n");
		cantidadKilosPorTipoPorCuit(aArrayPed, cantPed, aArrayCont, cantCont,aArrayClientes,cantClientes,5);
		printf("\n");
		break;
	case 'd':
		imprimirArrayClientes(aArrayClientes,QTY_CLIENTES);
		if(getInt(&id,"Indique el id que desea consultar\n", "NO es un id valido\n", 1,100,2)!=0)
		{
			printf("ERROR. \n");
			break;
		}
		while(buscarClientePorId(aArrayClientes, QTY_CLIENTES,id)==-1)
		{
			getInt(&id,"NO es un id valido, reingrese\n", "NO es un id valido\n", 1,100,2);

		}
		printf("Ha seleccionado el siguiente ID para modificar. \n");
		imprimirDatosClientePorId(aArrayClientes,QTY_CLIENTES,id);
		sumaTotalesDeResiduosPorIdClienteIngresado(aArrayPed, cantPed,1,&acumulador, id);
		printf("La suma total de HDPE para el id %d es: %.2f \n",id,acumulador);
		sumaTotalesDeResiduosPorIdClienteIngresado(aArrayPed, cantPed,2,&acumulador, id);
		printf("La suma total de LDPE para el id %d es: %.2f \n",id,acumulador);
		sumaTotalesDeResiduosPorIdClienteIngresado(aArrayPed, cantPed,3,&acumulador, id);
		printf("La suma total de PP para el id %d es: %.2f \n",id,acumulador);
		sumaTotalesDeResiduosPorIdClienteIngresado(aArrayPed, cantPed,4,&acumulador, id);
		printf("La suma total de desechos para el id %d es: %.2f \n",id,acumulador);
		sumaTotalesDeResiduosPorIdClienteIngresado(aArrayPed, cantPed,5,&acumulador, id);
		printf("La suma total de residuos para el id %d es: %.2f \n",id,acumulador);
		break;
	}
	return retorno;
}

/**
 * \brief BUsca el primer lugar de pedido completo/procesado y devuelve el fracaso o la posicion
 * \param *aArray array que se le pasa a la funcion
 * \param cantidad tamaño del array
 * \return devuelve el -1 (EXIT_ERROR) en caso de que el array sea nulo o que su tamaño sea invalido o la primer posicion del array procesado/completo, para ser utilizado
 *
 */

int buscarPrimerLugarPedidoCompletoProcesado(Pedidos *aArray, int cantidad)
{
	int retorno = EXIT_ERROR;
	int i;
	if(aArray != NULL && cantidad > 0)
	{
		for(i=0;i<cantidad;i++)
		{
			if(aArray[i].status == STATUS_COMPLETO)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Busca e imprime el id Cliente con mayor cantidad de desechos
 * \param *aArray array que se le pasa a la funcion
 * \param cantidad tamaño del array
 * \return devuelve el -1 (EXIT_ERROR) en caso de que el array sea nulo o que su tamaño sea invalido o devuelve el id maximo en caso de exito
 *
 */
int buscarPedidoConMasDesechos(Pedidos *aArray, int cantidad)
{
	int retorno=EXIT_ERROR;
	float maximosKilosDesechos;
	int maximoIdCliente;
	int primerPosicionOcupada= buscarPrimerLugarPedidoCompletoProcesado(aArray,cantidad);
	int i;
	if(aArray != NULL && cantidad > 0)
	{
		maximosKilosDesechos=aArray[primerPosicionOcupada].kilosDesecho_4;
		maximoIdCliente=aArray[primerPosicionOcupada].idCliente;
		for(i=0;i<cantidad;i++)
		{
			if(aArray[i].kilosDesecho_4>maximosKilosDesechos && aArray[i].status==STATUS_COMPLETO)
			{
				maximosKilosDesechos=aArray[i].kilosDesecho_4;
				maximoIdCliente=aArray[i].idCliente;
			}
		}
		printf("La cantidad maxima de desechos es %.2f ",maximosKilosDesechos);
		retorno=maximoIdCliente;
	}
	return retorno;
}


int buscarCuitConMasDesechos (Clientes *aArrayClientes, int cantClientes, Pedidos *aArrayPedidos, int cantPed)
{
	int retorno=EXIT_ERROR;
	int id;
	int index;
	if(aArrayClientes != NULL && cantClientes > 0 &&aArrayPedidos != NULL && cantPed > 0)
	{
		id=buscarPedidoConMasDesechos(aArrayPedidos, cantPed);
		index=buscarClientePorId(aArrayClientes,cantClientes,id);
		printf(" y el cuit es %s \n",aArrayClientes[index].cuit);
	}
	return retorno;
}


float sumaTotalesDeDesechos(Pedidos *aArrayPed, int cantPed, float *acumulador)
{
	float retorno =EXIT_ERROR;
	int i;
	*acumulador=0.00;
	if(aArrayPed != NULL && cantPed > 0)
	{
		for(i=0;i<cantPed;i++)
		{
			if(aArrayPed[i].status==STATUS_COMPLETO)
			{
				*acumulador=*acumulador+aArrayPed[i].kilosDesecho_4;
			}
		}
		retorno=*acumulador;
	}
	return retorno;
}


float sumaTotalesDeResiduosPorTipo(Pedidos *aArrayPed, int cantPed, int opcion,float *acumulador)
{
	float retorno =EXIT_ERROR;
	int i;
	*acumulador=0.00;
	if(aArrayPed != NULL && cantPed > 0)
	{
		for(i=0;i<cantPed;i++)
		{
			if(aArrayPed[i].status==STATUS_COMPLETO)
			{
				switch(opcion)
				{
				case 1:
					*acumulador=*acumulador+aArrayPed[i].kilosHdpe_1;
					break;
				case 2:
					*acumulador=*acumulador+aArrayPed[i].kilosLdpe_2;
					break;
				case 3:
					*acumulador=*acumulador+aArrayPed[i].kilosPp_3;
					break;
				case 4:
					*acumulador=*acumulador+aArrayPed[i].kilosDesecho_4;
					break;
				case 5:
					*acumulador=*acumulador+aArrayPed[i].kilosTotales;
					break;
				}
			}
		}
		retorno=*acumulador;
	}
	return retorno;
}



float cantidadKilosPorTipoPorCuit(Pedidos *aArray, int cantidad, auxContador *aArrayCont, int cantCont,Clientes *aArrayClientes, int cantClientes, int opcion)
{
	float retorno=EXIT_ERROR;
	int i;
	int j;
	initLugarLibreContador(aArrayCont,cantCont);
	if(aArray != NULL && cantidad>0 && aArrayClientes!=NULL && cantClientes>0)
	{
		retorno=EXIT_SUCCESS;
		for(i=0;i<cantCont;i++)
		{
			aArrayCont[i].idCliente=aArray[i].idCliente;
			//aArrayCont[i].contador =0;
			aArrayCont[i].acumulador=0;
		}
		for(i=0;i<cantCont;i++)
		{
			for(j=0;j<cantidad;j++)
			{
				if(aArray[j].status == STATUS_COMPLETO && aArrayCont[i].idCliente==aArray[j].idCliente)
				{
					switch(opcion)
					{
					case 1:
						//aArrayCont[i].contador++;
						aArrayCont[i].status=STATUS_COMPLETO;
						aArrayCont[i].acumulador=aArrayCont[i].acumulador+aArray[j].kilosHdpe_1;
						break;
					case 2:
						aArrayCont[i].status=STATUS_COMPLETO;
						aArrayCont[i].acumulador=aArrayCont[i].acumulador+aArray[j].kilosLdpe_2;
						break;
					case 3:
						aArrayCont[i].status=STATUS_COMPLETO;
						aArrayCont[i].acumulador=aArrayCont[i].acumulador+aArray[j].kilosPp_3;
						break;
					case 4:
						aArrayCont[i].status=STATUS_COMPLETO;
						aArrayCont[i].acumulador=aArrayCont[i].acumulador+aArray[j].kilosDesecho_4;
						break;
					case 5:
						aArrayCont[i].status=STATUS_COMPLETO;
						aArrayCont[i].acumulador=aArrayCont[i].acumulador+aArray[j].kilosTotales;
						break;
					}
				}
			}
		}

		imprimirCantidadKilosPorTipoPorPorCuit(aArrayCont,cantCont,aArrayClientes,cantClientes,opcion);
	}
	return retorno;
}



int imprimirCantidadKilosPorTipoPorPorCuit(auxContador *aArrayCont, int cantCont,Clientes *aArrayClientes, int cantClientes, int opcion)
{
	int retorno =EXIT_ERROR;
	int i;
	int j;
	if(aArrayCont != NULL && cantCont>0 && aArrayClientes!=NULL && cantClientes>0)
	{
		retorno=EXIT_SUCCESS;
		for(i=0;i<cantCont;i++)
		{
			for(j=0;j<cantClientes;j++)
				if(aArrayCont[i].status==STATUS_COMPLETO && aArrayCont[i].idCliente!=aArrayCont[i+1].idCliente && aArrayCont[i].idCliente==aArrayClientes[j].id)
				{
					switch(opcion)
					{
					case 1:
						printf("El cliente con Cuit %s - ID Cliente %d - NOmbre %s - Direccion %s - Localidad %s tiene %.2f Kilos de HDPE\n",aArrayClientes[j].cuit,aArrayClientes[j].id,aArrayClientes[j].nombre,aArrayClientes[j].direccion,aArrayClientes[j].localidad,aArrayCont[i].acumulador);
						break;
					case 2:
						printf("El cliente con Cuit %s - ID Cliente %d - NOmbre %s - Direccion %s - Localidad %s tiene %.2f Kilos de LDPE\n",aArrayClientes[j].cuit,aArrayClientes[j].id,aArrayClientes[j].nombre,aArrayClientes[j].direccion,aArrayClientes[j].localidad,aArrayCont[i].acumulador);
						break;
					case 3:
						printf("El cliente con Cuit %s - ID Cliente %d - NOmbre %s - Direccion %s - Localidad %s tiene %.2f Kilos de PP\n",aArrayClientes[j].cuit,aArrayClientes[j].id,aArrayClientes[j].nombre,aArrayClientes[j].direccion,aArrayClientes[j].localidad,aArrayCont[i].acumulador);
						break;
					case 4:
						printf("El cliente con Cuit %s - ID Cliente %d - NOmbre %s - Direccion %s - Localidad %s tiene %.2f Kilos de desecho\n",aArrayClientes[j].cuit,aArrayClientes[j].id,aArrayClientes[j].nombre,aArrayClientes[j].direccion,aArrayClientes[j].localidad,aArrayCont[i].acumulador);
						break;
					case 5:
						printf("El cliente con Cuit %s - ID Cliente %d - NOmbre %s - Direccion %s - Localidad %s tiene %.2f Kilos Totales\n",aArrayClientes[j].cuit,aArrayClientes[j].id,aArrayClientes[j].nombre,aArrayClientes[j].direccion,aArrayClientes[j].localidad,aArrayCont[i].acumulador);
						break;
				}
			}
		}
	}
	return retorno;
}


float sumaTotalesDeResiduosPorIdClienteIngresado(Pedidos *aArrayPed, int cantPed, int opcion,float *acumulador, int id)
{
	float retorno =EXIT_ERROR;
	int i;
	*acumulador=0.00;
	if(aArrayPed != NULL && cantPed > 0)
	{
		for(i=0;i<cantPed;i++)
		{
			if(aArrayPed[i].status==STATUS_COMPLETO &&aArrayPed[i].idCliente==id)
			{
				switch(opcion)
				{
				case 1:
					*acumulador=*acumulador+aArrayPed[i].kilosHdpe_1;
					break;
				case 2:
					*acumulador=*acumulador+aArrayPed[i].kilosLdpe_2;
					break;
				case 3:
					*acumulador=*acumulador+aArrayPed[i].kilosPp_3;
					break;
				case 4:
					*acumulador=*acumulador+aArrayPed[i].kilosDesecho_4;
					break;
				case 5:
					*acumulador=*acumulador+aArrayPed[i].kilosTotales;
					break;
				}
			}
		}
		retorno=*acumulador;
	}
	return retorno;
}
