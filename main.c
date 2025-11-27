#include "produccion.h"
#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_NAME_LENGTH 50


int main() {
    char nombres[MAX_PRODUCTS][MAX_NAME_LENGTH];
    float tiempos[MAX_PRODUCTS] = {0.0f};
    float recursos[MAX_PRODUCTS] = {0.0f};
    float cobre[MAX_PRODUCTS] = {0.0f};
    
    // Variables para stock/disponibilidad global
    float tiempo_disponible = 0.0f;
    float aluminio_disponible = 0.0f;
    float cobre_disponible = 0.0f;

    int cantidad_productos = 0;
    int opcion;

    do {
        printf("\n--- Gestion de Produccion (C) ---\n");
        printf("1. Ingresar productos\n");
        printf("2. Mostrar productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Ingresar Recursos (Tiempo, Aluminio, Cobre)\n");
        printf("6. Carrito de Produccion (Descontar recursos)\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        if(scanf("%d", &opcion) != 1) {
             while (getchar() != '\n'); 
             opcion = 0;
        } else {
             while (getchar() != '\n');
        }

        switch (opcion) {
            case 1:
                ingresarDatos(nombres, tiempos, recursos, cobre, &cantidad_productos);
                break;
            case 2:
                mostrarProductos(nombres, tiempos, recursos, cobre, cantidad_productos);
                break;
            case 3:
                editarProducto(nombres, tiempos, recursos, cobre, cantidad_productos);
                break;
            case 4:
                eliminarProducto(nombres, tiempos, recursos, cobre, &cantidad_productos);
                break;
            case 5:
                ingresarRecursosDisponibles(&tiempo_disponible, &aluminio_disponible, &cobre_disponible);
                break;
            case 6:
                gestionarCarrito(nombres, tiempos, recursos, cobre, cantidad_productos, &tiempo_disponible, &aluminio_disponible, &cobre_disponible);
                break;
            case 7:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 7);

    return 0;
}
