/*
 *  All Rights Reserved.
 *  © 2020 Javier Hernández Santos
 *  javii.hernandez@usal.es
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "listaEnlazadaSimple.h"

int main(int argc, const char * argv[]) {

	char menu[] = "Listas enlazadas:\n" 
                    "A) Crear lista aleatoria\n" 
                    "B) Agregar al principio\n" 
                    "C) Agregar al final\n" 
                    "D) Insertar en posicion por indice\n" 
                    "E) Devolver valor en posicion por indice\n" 
                    "F) Eliminar al principio\n" 
                    "G) Eliminar al final\n" 
                    "H) Eliminar en posicion por indice\n" 
                    "I) Crear lista ordenada\n"
                    "J) Guardar lista en fichero de texto\n"
                    "K) Cargar lista de fichero de texto\n"
                    "V) Mostrar lista\n" 
                    "L) Liberar listas\n" 
                    "Q) Salir\n";

    ListaEnlazada raiz,raizOrdenada;
	tipoNodoRef aux;
	int indice,i;
    char opcion;
	tipoInfo temp  = 1234, temp2 = 4321;
	   
    crearVacia(&raiz);
	crearVacia(&raizOrdenada);
	
    do {

        system("cls");
		printf("%s ",menu);
        printf("Introduce opcion: ");
        scanf("%c%*c",&opcion);

		opcion = toupper(opcion);
		switch (opcion) {

			case 'A':
                printf("\nIntroduce el numero de nodos: ");
                scanf("%d%*c", &i);
                printf("\nAhora la cargo con valores aleatorios: %d\n",
                       crearListaValoresAleatorios(&raiz, i));
                break;

			case 'B':
				printf("\n\nInsertando nodo comienzo: %d", insertarNodoComienzo(&raiz, &temp));
				break;

			case 'C':                
                printf("\n\nInsertando nodo final: %d", insertarNodoFinal(&raiz, &temp2));
				break;

			case 'D':
				printf("\nIntroduce una posicion como entero: ");
                scanf("%d%*c", &indice);
                
                insertarNodoPosicionIndice(&raiz, indice, &temp2);
                break;

            case 'E':
                printf("\nIntroduce una posicion como entero: ");
                scanf("%d%*c", &indice);
                
                printf("\nEl valor almacendo en la posicion %d es %d\n", indice,devolverInfoPosicionIndice(raiz, indice));
                break;

            case 'F':
				printf("\n\nEliminando nodo comienzo: %d", eliminarNodoComienzo(&raiz));
				break;

			case 'G':
				printf("\n\nEliminando nodo final: %d", eliminarNodoFinal(&raiz));
				break;

			case 'H':
                printf("\nIntroduce una posición como entero: ");
                scanf("%d%*c", &indice);
                printf("\n\nEliminando nodo: %d",eliminarNodoPosicionIndice(&raiz, indice));
                break;

            case 'I':
                printf("\n\nCreando raizOrdenada...\n\n");
                while (!estaVacia(raiz)) {
                    insertarOrdenadaValor(&raizOrdenada, &raiz->info);
                    eliminarNodoComienzo(&raiz);
                }
                printf("\n\nAhora raizOrdenada contiene los elementos ordenados. raiz está vacía.\n\n");
                break;


            /*
             *  Para el correcto funcionamiento del fichero
             *  se recomienda cambiar la ubicacion que viene por defecto
             *  de este.
             */

            case 'J':
                printf("\n\nGuardando Lista Enlazada en Fichero...\n\n");
                guardarListaEnlazadaTexto(raiz, "C:\\Users\\Usuario\\Desktop\\listaEnlazada\\lista.txt");
                break;

            case 'K':
                printf("\n\nCargando Lista Enlazada con Fichero...\n\n");
                cargarListaEnlazadaTexto(&raizOrdenada, "C:\\Users\\Usuario\\Desktop\\listaEnlazada\\lista.txt");
                break;

            case 'V':
                printf("Mostrando lista raiz: %d\n",mostrarListaEnlazada(raiz));
                printf("Mostrando lista raizOrdenada: %d\n",mostrarListaEnlazada(raizOrdenada));
                break;

            case 'Q':
				printf("\n\nSaliendo.\n\n");

            case 'L':
                printf("Liberacion raiz: %d\n",liberarListaEnlazada(&raiz));
                printf("Liberacion raizOrdenada: %d\n",liberarListaEnlazada(&raizOrdenada));
                break;

            default:
				printf("\n\nOpcion incorrecta!\n\n");
				break;
		}

        printf("\nPulse enter...");
        getchar();
	} 

    while ('Q' != opcion);

	printf("\n\nTerminacion normal del programa.\n\n");
    return 0;

} //End of main()

