#ifndef PRODUCCION_H
#define PRODUCCION_H

#include <stdio.h>

#define MAX_PRODUCTS 5
#define MAX_NAME_LENGTH 50


void ingresarDatos(char nombres[][MAX_NAME_LENGTH], float tiempos[], float recursos[], float cobre[], int demandas[], int* cantidad_productos);
void mostrarProductos(const char nombres[][MAX_NAME_LENGTH], const float tiempos[], const float recursos[], const float cobre[], const int demandas[], int cantidad_productos);
void editarProducto(char nombres[][MAX_NAME_LENGTH], float tiempos[], float recursos[], float cobre[], int demandas[], int cantidad_productos);
void eliminarProducto(char nombres[][MAX_NAME_LENGTH], float tiempos[], float recursos[], float cobre[], int demandas[], int* cantidad_productos);
void calcularTotales(const char nombres[][MAX_NAME_LENGTH], const float tiempos[], const float recursos[], const float cobre[], const int demandas[], int cantidad_productos);
void verificarViabilidad(const char nombres[][MAX_NAME_LENGTH], const float tiempos[], const float recursos[], const float cobre[], const int demandas[], int cantidad_productos);
int buscarProducto(const char nombres[][MAX_NAME_LENGTH], int cantidad_productos, const char* nombre_buscar);


float ingresaFloat(const char* mensaje);
int ingresaEntero(const char* mensaje);

#endif