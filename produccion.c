#include "produccion.h"
#include <string.h>
#include <stdio.h>


float ingresaFloat(const char* mensaje) {
    float valor;
    int valido = 0;
    while (!valido) {
        printf("%s: ", mensaje);
        if (scanf("%f", &valor) == 1) {
            if (valor >= 0) {
                valido = 1;
            } else {
                printf("Error: El valor no puede ser negativo.\n");
            }
        } else {
            printf("Error: Entrada invalida. Por favor, ingrese un numero.\n");
            while (getchar() != '\n'); 
        }
    }
    while (getchar() != '\n'); 
    return valor;
}

int ingresaEntero(const char* mensaje) {
    int valor;
    int valido = 0;
    while (!valido) {
        printf("%s: ", mensaje);
        if (scanf("%d", &valor) == 1) {
            if (valor >= 0) {
                valido = 1;
            } else {
                printf("Error: El valor no puede ser negativo.\n");
            }
        } else {
            printf("Error: Entrada invalida. Por favor, ingrese un numero entero.\n");
            while (getchar() != '\n'); 
        }
    }
    while (getchar() != '\n'); 
    return valor;
}

void ingresarDatos(char nombres[][MAX_NAME_LENGTH], float* tiempos, float* recursos, float* cobre, int* demandas, int* cantidad_productos) {
    if (*cantidad_productos >= MAX_PRODUCTS) {
        printf("Ya se ha alcanzado el maximo de %d productos.\n", MAX_PRODUCTS);
        return;
    }

    char nombre_temp[MAX_NAME_LENGTH];
    int valido = 0;

    while (!valido) {
        printf("Ingrese el nombre del producto %d: ", *cantidad_productos + 1);
        scanf("%49s", nombre_temp);
        while (getchar() != '\n'); 

        if (buscarProducto(nombres, *cantidad_productos, nombre_temp) != -1) {
            printf("Error: El nombre '%s' ya existe. Por favor ingrese otro nombre.\n", nombre_temp);
        } else {
            valido = 1;
        }
    }
    
    strcpy(nombres[*cantidad_productos], nombre_temp);

   
    tiempos[*cantidad_productos]  = ingresaFloat("Tiempo de produccion (en horas)");
    recursos[*cantidad_productos] = ingresaFloat("Cantidad de Aluminio (mg)");
    cobre[*cantidad_productos]    = ingresaFloat("Cantidad en cobre (mg)");
    demandas[*cantidad_productos] = ingresaEntero("Demanda del producto");

    printf("Producto agregado correctamente.\n");
    (*cantidad_productos)++;
}

void mostrarProductos(const char nombres[][MAX_NAME_LENGTH], const float* tiempos, const float* recursos, const float* cobre, const int* demandas, int cantidad_productos) {
    if (cantidad_productos == 0) {
        printf("No hay productos para mostrar.\n");
        return;
    }
    printf("\n--- Lista de Productos ---\n");
    for (int i = 0; i < cantidad_productos; ++i) {
        printf("Producto %d:\n", i + 1);
        printf("  Nombre: %s\n", nombres[i]);
        printf("  Tiempo de Fabricacion: %.2fh\n", tiempos[i]);
        printf("  Cantidad de Aluminio: %.2f mg\n", recursos[i]);
        printf("  Cantidad de Cobre: %.2f mg\n", cobre[i]);
        printf("  Demanda: %d unidades\n", demandas[i]);
    }
}

int buscarProducto(const char nombres[][MAX_NAME_LENGTH], int cantidad_productos, const char* nombre_buscar) {
    for (int i = 0; i < cantidad_productos; ++i) {
        if (strcmp(nombres[i], nombre_buscar) == 0) {
            return i; 
        }
    }
    return -1; 
}

void editarProducto(char nombres[][MAX_NAME_LENGTH], float* tiempos, float* recursos, float* cobre, int* demandas, int cantidad_productos) {
    if (cantidad_productos == 0) {
        printf("No hay productos para editar.\n");
        return;
    }
    char nombre_buscar[MAX_NAME_LENGTH];
    printf("Ingrese el nombre del producto que desea editar: ");
    scanf("%49s", nombre_buscar);
    while (getchar() != '\n');

    int indice = buscarProducto(nombres, cantidad_productos, nombre_buscar);

    if (indice != -1) {
        printf("Editando producto: %s\n", nombres[indice]);
        
        int opcion = 0;
        do {
            printf("\n--- Menu de Edicion para '%s' ---\n", nombres[indice]);
            printf("1. Editar Nombre\n");
            printf("2. Editar Tiempo de Fabricacion\n");
            printf("3. Editar Cantidad de Aluminio\n");
            printf("4. Editar Cantidad de Cobre\n");
            printf("5. Editar Demanda\n");
            printf("6. Salir de edicion\n");
            
            opcion = ingresaEntero("Seleccione una opcion");

            switch(opcion) {
                case 1: {
                    char nuevo_nombre[MAX_NAME_LENGTH];
                    int valido = 0;
                    while (!valido) {
                        printf("Ingrese el nuevo nombre: ");
                        scanf("%49s", nuevo_nombre);
                        while (getchar() != '\n');

                        int indice_existente = buscarProducto(nombres, cantidad_productos, nuevo_nombre);
                        if (indice_existente != -1 && indice_existente != indice) {
                            printf("Error: El nombre '%s' ya esta en uso por otro producto.\n", nuevo_nombre);
                        } else {
                            valido = 1;
                        }
                    }
                    strcpy(nombres[indice], nuevo_nombre);
                    printf("Nombre actualizado.\n");
                    break;
                }
                case 2:
                    tiempos[indice] = ingresaFloat("Ingrese el nuevo tiempo de fabricacion");
                    printf("Tiempo actualizado.\n");
                    break;
                case 3:
                    recursos[indice] = ingresaFloat("Ingrese la nueva cantidad de aluminio en mg");
                    printf("Aluminio actualizado.\n");
                    break;
                case 4:
                    cobre[indice] = ingresaFloat("Ingrese la nueva cantidad de cobre en mg");
                    printf("Cobre actualizado.\n");
                    break;
                case 5:
                    demandas[indice] = ingresaEntero("Ingrese la nueva demanda");
                    printf("Demanda actualizada.\n");
                    break;
                case 6:
                    printf("Finalizando edicion del producto.\n");
                    break;
                default:
                    printf("Opcion invalida. Intente de nuevo.\n");
            }

        } while (opcion != 6);

    } else {
        printf("Producto no encontrado.\n");
    }
}

void eliminarProducto(char nombres[][MAX_NAME_LENGTH], float* tiempos, float* recursos, float* cobre, int* demandas, int* cantidad_productos) {
    if (*cantidad_productos == 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }
    char nombre_buscar[MAX_NAME_LENGTH];
    printf("Ingrese el nombre del producto que desea eliminar: ");
    scanf("%49s", nombre_buscar);
    while (getchar() != '\n');

    int indice = buscarProducto(nombres, *cantidad_productos, nombre_buscar);

    if (indice != -1) {
        for (int i = indice; i < *cantidad_productos - 1; ++i) {
            strcpy(nombres[i], nombres[i + 1]);
            tiempos[i] = tiempos[i + 1];
            recursos[i] = recursos[i + 1];
            cobre[i] = cobre[i + 1];
            demandas[i] = demandas[i + 1];
        }
        (*cantidad_productos)--;
        printf("Producto eliminado.\n");
    } else {
        printf("Producto no encontrado.\n");
    }
}

void calcularTotales(const char nombres[][MAX_NAME_LENGTH], const float* tiempos, const float* recursos, const float* cobre, const int* demandas, int cantidad_productos) {
    if (cantidad_productos == 0) {
        printf("No hay productos para calcular.\n");
        return;
    }

    double tiempo_total = 0;
    double recursos_totales = 0;
    double cobre_total = 0;

    for (int i = 0; i < cantidad_productos; i++) {
        tiempo_total += (double)tiempos[i] * demandas[i];
        recursos_totales += (double)recursos[i] * demandas[i];
        cobre_total += (double)cobre[i] * demandas[i];
    }

    printf("\n--- Totales de Produccion ---\n");
    printf("Tiempo total de fabricacion requerido: %.2f horas.\n", tiempo_total);
    printf("Cantidad total de aluminio necesaria: %.2f mg.\n", recursos_totales);
    printf("Cantidad total de cobre necesaria: %.2f mg.\n", cobre_total);
}

void verificarViabilidad(const char nombres[][MAX_NAME_LENGTH], const float* tiempos, const float* recursos, const float* cobre, const int* demandas, int cantidad_productos) {
    if (cantidad_productos == 0) {
        printf("No hay productos para verificar.\n");
        return;
    }

    double tiempo_total_req = 0;
    double recursos_totales_req = 0;
    double cobre_total_req = 0;

    for (int i = 0; i < cantidad_productos; i++) {
        tiempo_total_req += (double)tiempos[i] * demandas[i];
        recursos_totales_req += (double)recursos[i] * demandas[i];
        cobre_total_req += (double)cobre[i] * demandas[i];
    }

    float tiempo_disponible;
    float recursos_disponibles;
    float cobre_disponible;

    tiempo_disponible = ingresaFloat("Ingrese el tiempo de produccion total disponible (en horas)");
    recursos_disponibles = ingresaFloat("Ingrese la cantidad de aluminio total disponible");
    cobre_disponible = ingresaFloat("Ingrese la cantidad de cobre total disponible");

    printf("\n--- Analisis de Viabilidad ---\n");
    printf("Tiempo total requerido: %.2f horas.\n", tiempo_total_req);
    printf("Aluminio total requerido: %.2f mg.\n", recursos_totales_req);
    printf("Cobre total requerido: %.2f mg.\n", cobre_total_req);
    printf("Tiempo total disponible: %.2f horas.\n", tiempo_disponible);
    printf("Aluminio total disponible: %.2f mg.\n", recursos_disponibles);
    printf("Cobre total disponible: %.2f mg.\n", cobre_disponible);

    if (tiempo_total_req <= tiempo_disponible && recursos_totales_req <= recursos_disponibles && cobre_total_req <= cobre_disponible) {
        printf("\nConclusion: La fabrica PUEDE cumplir con la demanda.\n");
    } else {
        printf("\nConclusion: La fabrica NO PUEDE cumplir con la demanda.\n");
        if (tiempo_total_req > tiempo_disponible) {
            printf("  - Deficit de tiempo: %.2f horas.\n", tiempo_total_req - tiempo_disponible);
        }
        if (recursos_totales_req > recursos_disponibles) {
            printf("  - Deficit de aluminio: %.2f mg.\n", recursos_totales_req - recursos_disponibles);
        }
        if (cobre_total_req > cobre_disponible) {
            printf("  - Deficit de cobre: %.2f mg.\n", cobre_total_req - cobre_disponible);
        }
    }
}