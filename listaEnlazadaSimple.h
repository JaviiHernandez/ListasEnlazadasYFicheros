/*
 *  All Rights Reserved.
 *  © 2020 Javier Hernández Santos
 *  javii.hernandez@usal.es
 */

#ifndef __LISTAENLAZADASIMPLE_H__
#define __LISTAENLAZADASIMPLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int tipoInfo;
typedef tipoInfo *tipoInfoRef;

/* ESTRUCTURA DEL NODO */

typedef struct tipoNodo {

	tipoInfo info;				
	struct tipoNodo * sig;

} tipoNodo;

typedef tipoNodo *tipoNodoRef;

typedef tipoNodo * ListaEnlazada;
typedef ListaEnlazada *ListaEnlazadaRef;


/* FUNCIONES PRINCIPALES */

int crearVacia(ListaEnlazadaRef raiz);
int estaVacia(ListaEnlazada raiz);
int liberarListaEnlazada(ListaEnlazadaRef raiz);

/* FUNCIONES PARA INSERTAR */

int insertarNodoComienzo(ListaEnlazadaRef raiz, tipoInfoRef info);
int insertarNodoFinal(ListaEnlazadaRef raiz, tipoInfoRef info);
int insertarAntesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info);
int insertarDespuesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info);
int insertarNodoPosicionIndice(ListaEnlazadaRef raiz, int indice, tipoInfoRef info);

/* FUNCIONES PARA ELIMINAR */

int eliminarNodo(ListaEnlazadaRef raiz, tipoNodoRef pos);
int eliminarNodoComienzo(ListaEnlazadaRef raiz);
int eliminarNodoFinal(ListaEnlazadaRef raiz);
int eliminarNodoPosicionIndice(ListaEnlazadaRef raiz, int indice);

/* FUNCIONES EXTRA */

tipoInfo devolverInfoPosicionIndice(ListaEnlazada raiz, int indice);
int insertarOrdenadaValor(ListaEnlazadaRef raiz, tipoInfoRef info);

int mostrarListaEnlazada(ListaEnlazada raiz);
int crearListaValoresAleatorios(ListaEnlazadaRef raiz, int numNodos);

int guardarListaEnlazadaTexto(ListaEnlazada raiz, char *nombreFichero);
int cargarListaEnlazadaTexto(ListaEnlazadaRef raiz, char *nombreFichero);

#endif