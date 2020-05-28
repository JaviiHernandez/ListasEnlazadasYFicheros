/*
 *  All Rights Reserved.
 *  © 2020 Javier Hernández Santos
 *  javii.hernandez@usal.es
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listaEnlazadaSimple.h"



/*----------------------------------*
 *		FUNCIONES PRINCIPALES		*
 *----------------------------------*/

/*
 *  int crearVacia(ListaEnlazadaRef)   
 *      - 'raiz' apunta a NULL
 *      - Devolvemos 0
 */

int crearVacia(ListaEnlazadaRef raiz) {

	*raiz = NULL;
	return 0;

} //End of crearVacia()


/*
 *  int estaVacia(ListaEnlazada)    
 *      - Devuele si se encuentra vacia
 */

int estaVacia(ListaEnlazada raiz) {

	return (raiz == NULL);

} //end of estaVacia()


/*
 *  tipoNodoRef creaNodo(tipoInfoRef)   
 *      - Reserva correctamente memoria para el nuevo nodo
 *      - Guarda el primer valor de info recibido en la funcion
 *      - El siguiente apunta a NULL
 *      - Devuelve el nodo creado
 */

tipoNodoRef creaNodo(tipoInfoRef info) {

    tipoNodoRef nuevo;
    if (NULL == (nuevo = (tipoNodoRef) malloc(sizeof(tipoNodo)))) {

        #ifdef DEBUG
        fprintf(stderr, "Error: no reserva memoria\n");
        #endif
		return NULL;
    } 
	else {

        nuevo->info = *info;
        nuevo->sig = NULL;
    }

    return nuevo;

} //End of creaNodo()


/*------------------------------*
 *		FUNCIONES INSERTAR		*
 *------------------------------*/

/*
 *	int insertarNodoComienzo(ListaEnlazadaRef raiz, tipoInfoRef info)
 * 		- Crea un nuevo nodo
 * 		- Guardamos la informacion en el nodo 
 * 		- El siguiente apunta al principio de la lista
 */

int insertarNodoComienzo(ListaEnlazadaRef raiz, tipoInfoRef info) {

	tipoNodoRef nuevo;
	
	if (NULL == (nuevo = creaNodo(info))) {

		#ifdef DEBUG
		fprintf(stderr, "ERROR: crear nodo\n");
		#endif
		return -1;
	}

	nuevo->info = *info;
	nuevo->sig = *raiz;
	*raiz = nuevo;

	return 0;

} //End of insertarNodoComienzo()


/*
 *	int insertarNodoFinal(ListaEnlazadaRef raiz, tipoInfoRef info)
 * 		- Crea un nodo nuevo
 * 		- Guardamos info en el nuevo nodo
 * 		- Recorre la lista hasta posicionarse al final
 * 		- Inserta el nodo en la ultima posicion
 */

int insertarNodoFinal(ListaEnlazadaRef raiz, tipoInfoRef info) {

	tipoNodoRef nuevo, indice;

	if (NULL == (nuevo = creaNodo(info))) {

		#ifdef DEBUG
		fprintf(stderr, "ERROR: crear nodo\n");
		#endif
		return -1;

	}

	nuevo->info = *info;
	nuevo->sig = NULL;
	indice = *raiz;

	if(raiz == NULL)
		*raiz = nuevo;

	else {

		while(indice->sig != NULL)
			indice = indice->sig;

		indice->sig = nuevo;

	}

	return 0;

} //End of insertarNodoAlFinal()


/*
 *	int insertarAntesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info)
 * 		- Crea un nuevo nodo
 * 		- Comprueba los datos para insertar el nodo
 * 		- Recorre la lista hasta insertar el nodo
 * 		- En caso de que no se pueda libera el nodo creado
 */

int insertarAntesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info) {

	tipoNodoRef nuevo, anterior;
	
	if (NULL == (nuevo = creaNodo(info))) {

		#ifdef DEBUG
		fprintf(stderr, "ERROR: crear nodo\n");
		#endif
		return -1;

	} 
	else {

		if (estaVacia(*raiz) || pos == NULL || pos == *raiz) {

			nuevo->sig = *raiz;
			*raiz = nuevo;

		} 
		else {

			anterior = *raiz;
			while (anterior != NULL && anterior->sig != pos)
				anterior = anterior->sig;

			if (anterior != NULL) {

				nuevo->sig = pos;
				anterior->sig = nuevo;

			} 
			else {

				free (nuevo);
				#ifdef DEBUG
				fprintf(stderr, "Error: %p posicion inexistente\n", pos);
				#endif
				return -2;

			}
		}

		return 0;

	}	

} //End of insertarAntesDeNodo()


/*
 *	int insertarDespuesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info)
 * 		- Crea un nuevo nodo
 * 		- Guardamos la informacion en el nodo
 * 		- El siguiente apunta a NULL
 * 		- Comprueba si indice es NULL, en este caso, este es el nodo nuevo
 * 		- Si ya tenemos una lista, esta se recorre hasta el final hasta insertarlo
 */

int insertarDespuesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info) {

	tipoNodoRef nuevo, indice;
	
	if (NULL == (nuevo = creaNodo(info))) {

		#ifdef DEBUG
		fprintf(stderr, "ERROR: crear nodo\n");
		#endif
		return -1;

	}

	nuevo->info = *info;
	nuevo->sig = NULL;

	indice = *raiz;
	if (indice == NULL) 
		*raiz = nuevo;

	else {

		while (indice->sig != NULL) 
			indice = indice->sig;
		
		indice->sig = nuevo;
	}

	return 0;

} //End of insertarDespuesDeNodo()


/*
 *	int	insertarNodoPosicionIndice(ListaEnlazadaRef raiz, int indice, tipoInfoRef info)
 * 		- Crea un nuevo nodo
 * 		- Recorre la lista buscando la posicion
 * 		- Si la lista esta vacia lo inserta al principio
 * 		- En caso contrario inserta el nodo en la posicion indicada
 */

int	insertarNodoPosicionIndice(ListaEnlazadaRef raiz, int indice, tipoInfoRef info) {

	int i = 0;
	tipoNodoRef nuevo, aux, anterior;

	if (NULL == (nuevo = creaNodo(info))) {

		#ifdef DEBUG
		fprintf(stderr, "ERROR: crear nodo\n");
		#endif
		return -1;

	}

	aux = *raiz;
	anterior = NULL;

	while (aux->sig != NULL && i < indice) {

		i++;
		anterior = aux;
		aux = aux->sig;

	}

	if (*raiz == NULL) {

		*raiz = nuevo;
		nuevo->sig = NULL;

	} 
	else if (anterior == NULL) {

		if (insertarNodoComienzo(raiz, info) == -1) 
			return -2;

	} 
	else {

		anterior->sig = nuevo;
		nuevo->sig = aux;

	}

	return 0;

} //End of insertarNodoPosicionIndice()


/*------------------------------*
 *		FUNCIONES ELIMINAR		*
 *------------------------------*/

/*
 *	int	eliminarNodo(ListaEnlazadaRef raiz, tipoNodoRef pos)
 * 		- Creamos un tipoNodoRef que apunta al inicio de la lista
 * 		- Recorre la lista hasta llegar a la posicion
 * 		- Eliminamos el nodo situado en la posicion
 */

int	eliminarNodo(ListaEnlazadaRef raiz, tipoNodoRef pos) {

	tipoNodoRef anterior;
	
	anterior = *raiz;
	while (anterior->sig != pos)
		anterior = anterior->sig;

	anterior->sig = pos->sig;

	free(pos);
	return 0;

} //End of eliminarNodo()


/*
 *	int eliminarNodoComienzo(ListaEnlazadaRef raiz)
 * 		- Creamos un tipoNodoRef
 * 		- Apuntamos este tipoNodoRef al inicio de la lista
 * 		- Liberamos el tipoNodoRef eliminando el nodo inicial
 */

int eliminarNodoComienzo(ListaEnlazadaRef raiz) {

	tipoNodoRef aBorrar;
	
	aBorrar = *raiz;
	*raiz = (*raiz)->sig;
	free(aBorrar);

	return 0;

} //End of eliminarNodoComienzo()


/*
 *	int eliminarNodoFinal(ListaEnlazadaRef raiz)	
 * 		- Recorre la lista hasta llegar al final
 * 		- Elimina el nodo que se encuentra en esta posicion
 */

int eliminarNodoFinal(ListaEnlazadaRef raiz) {

	tipoNodoRef anterior, aBorrar;

	if (raiz != NULL) {

		aBorrar = *raiz;
		anterior = NULL;

		while (aBorrar->sig != NULL) {

			anterior = aBorrar;
			aBorrar = aBorrar->sig;

		}

		if (anterior == NULL) {

			raiz = NULL;
			free(aBorrar);

		} 
		else {

			anterior->sig = NULL;
			free(aBorrar);

		}
	}

	return 0;

} //End of eliminarNodoFinal()


/*
 *	int eliminarNodoPosicionIndice(ListaEnlazadaRef raiz, int indice)
 * 		- Comprobamos que el indice sea mayor que 0
 * 		- Recorremos la lista hasta llegar al indice
 * 		- Eliminamos el indice y unimos el anterior con el siguiente
 */

int eliminarNodoPosicionIndice(ListaEnlazadaRef raiz, int indice) {

	int k = 0;
	tipoNodoRef aBorrar, anterior;
	
	if (indice < 0) {

		#ifdef DEBUG
		fprintf(stderr, "ERROR: indice no admitido\n");
		#endif
		return -1;

	}
	
	aBorrar = *raiz;
	anterior = NULL;
	
	while ((aBorrar != NULL) && (k < indice)) {

		k++;
		anterior = aBorrar;
		aBorrar = aBorrar->sig;

	}
	
	if (k == indice) {

		if (anterior == NULL) 
			*raiz = aBorrar->sig;

		else
			anterior->sig = aBorrar->sig;
		
		free(aBorrar);
	}

	return 0;

} //End of eliminarNodoPosicionIndice()


/*------------------------------*
 *		 FUNCIONES EXTRA		*
 *------------------------------*/

/*
 *	tipoInfo devolverInfoPosicionIndice(ListaEnlazada raiz, int indice)
 * 		- Recorre la lista hasta llegar al indice
 * 		- Una vez alcanzado el nodo devuelve el campo 'info' de este
 */

tipoInfo devolverInfoPosicionIndice(ListaEnlazada raiz, int indice) {

	tipoNodoRef aux;
	int i = 0;
	
	aux = raiz;
	
	while (aux->sig != NULL && i < indice) {

		aux = aux->sig;
		i++;

	}

	return aux->info;

} //End of devolverInfoPosicionIndice()


/*
 *  int liberarListaEnlazada(ListaEnlazadaRef)   (int liberarListaEnlazada(struct tipoNodo **))
 *      - Comprueba si la lista esta vacia
 *      - Recorre toda la lista enlazada liberando los nodos
 *      - Finalmente 'raiz' apunta a NULL
 *      - Devuelve 0
 */

int liberarListaEnlazada(ListaEnlazadaRef raiz) {

    tipoNodoRef aborrar, aux;
    
    if (estaVacia(*raiz))
        return -1;

    else {

        aux = *raiz;
        while (aux != NULL) {

            aborrar = aux;
            aux = aux->sig;
            free (aborrar);

        }

        *raiz = NULL;
        return 0;
    }

} //End of liberarListaEnlazada()


/*
 *	int insertarOrdenada(ListaEnlazadaRef raiz, tipoInfoRef info)
 * 		- Si la lista esta vacia o el campo 'info' es mayor inserta al inicio
 * 		- Si no, recorre la lista buscando el campo mayor para insertar el nodo
 */

int insertarOrdenadaValor(ListaEnlazadaRef raiz, tipoInfoRef info) {

	tipoNodoRef aux;
	
	if(estaVacia(*raiz) || (*raiz)->info > *info) 
		return insertarNodoComienzo(raiz, info);

	else {

		aux = *raiz;
		while(aux->sig != NULL && aux->sig->info < *info)
			aux = aux->sig;

		return insertarDespuesDeNodo(raiz, aux, info);

	}

} //End of insertarOrdenadaValor()


/*
 *  int mostrarListaEnlazada(ListaEnlazada)  
 *      - Imprime en pantalla el titulo
 *      - Recorre la lista imprimiendo los valores
 */

int mostrarListaEnlazada(ListaEnlazada raiz) {

	tipoNodoRef aImprimir;
	int res = 0, i = 0;
	
	printf("\n\n");
	printf("%-14s%-10s\n","  Posicion", "Valor");
	printf("%-14s%-10s\n","  ==========", "======");


	aImprimir = raiz;
	while (aImprimir != NULL) {

		printf("\t%3d)\t%7d\n", ++i, aImprimir->info);
		aImprimir = aImprimir->sig;

	}

	return res;

} //End of mostrarListaEnlazada()


/*
 *  int crearListaValoresAleatorios(ListaEnlazadaRef, int)   
 *      - Comprueba si la lista esta vacia
 *      - Introduce los valores mediante un bucle for
 *      - Devuelve 0 si se ha completado correctamente
 */

int crearListaValoresAleatorios(ListaEnlazadaRef raiz, int numNodos) {

	int i;
	tipoInfo temp;
	
	if (estaVacia(*raiz)) {

		srand(time(NULL));
		for (i = 0; i < numNodos; i++) {

            temp = rand()%100;
            insertarDespuesDeNodo(raiz, NULL, &temp);
            //insertarAntesDeNodo(raiz, NULL, &temp);
            //insertarNodoFinal(raiz, &temp);
			//insertarNodoComienzo(raiz, &temp);

		}

		return 0;

	}

	return -1;

} //End of crearListaValoresAleatorios()


/*
 *	int guardarListaEnlazadaTexto(ListaEnlazada raiz, char *nombreFichero)
 * 		- Comprueba si la lista esta vacia
 * 		- Abre fichero en modo 'escritura'
 * 		- Recorre la lista guardando en el fichero los valores
 * 		- Cierra fichero
 */

int guardarListaEnlazadaTexto(ListaEnlazada raiz, char *nombreFichero) {

	tipoNodoRef aux;
	FILE *f;
	int cont = 0;

	if(estaVacia(raiz)) 
		return 0;

	else {

		if(NULL == (f = fopen (nombreFichero, "w"))) {

			#ifdef DEBUG
			fprintf(stderr, "ERROR: No se pudo abrir el fichero\n");
			#endif
			return -1;

		} 
		else {

			aux = raiz;
			while(aux != NULL) {

				fprintf(f, "%d ", aux->info);
				cont++;
				aux = aux->sig;

			}

			fclose(f);
			return cont;

		}
	}

} //End of guardarListaEnlazadaTexto()


/*
 *	int cargarListaEnlazadaTexto(ListaEnlazadaRef raiz, char *nombreFichero)
 * 		- Abrimos el fichero en modo 'lectura'
 * 		- Comprobamos los parametros
 * 		- Guardamos la lista ordenada
 * 		- Cerramos fichero 
 */

int cargarListaEnlazadaTexto(ListaEnlazadaRef raiz, char *nombreFichero) {

	tipoInfo aux;
	FILE *f;
	int cont = 0;

	if(NULL == (f = fopen(nombreFichero, "r"))) {

		#ifdef DEBUG
		fprintf(stderr, "ERROR: No se pudo abrir el fichero\n");
		#endif
		return -1;

	}
	else {

		if (1 == fscanf(f,"%d",&aux)) 
			printf("\t %3d)\t%7d\n", ++cont, aux);
		
		else {

			#ifdef DEBUG
			fprintf(stderr, "ERROR: No se pudo leer el fichero\n");
			#endif
			fclose(f);
			return -2;

		}

		while(!feof(f)) {

			if(0 > insertarOrdenadaValor(raiz, &aux)) {

				#ifdef DEBUG
				fprintf(stderr, "ERROR: Insertar ordenada (1)\n");
				#endif
				fclose(f);
				return -1;

			}
			if(1 != fscanf(f,"%d",&aux)) {

				if (!feof(f)) {

					#ifdef DEBUG
					fprintf(stderr, "ERROR: Insertar ordenada (2)\n");
					#endif
					fclose(f);
					return -2;

				}

			} 
			else 
				printf ("\t%3d)\t%7d\n", ++cont, aux);
			
		}

		fclose(f);
		return cont;

	}

} //End of cargarListaEnlazadaTexto()