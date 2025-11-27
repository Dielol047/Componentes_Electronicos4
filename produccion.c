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

void ingresarDatos(char nombres[][MAX_NAME_LENGTH], float* tiempos, float* recursos, float* cobre, int* cantidad_productos) {
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

    printf("Producto agregado correctamente.\n");
    (*cantidad_productos)++;
}

void mostrarProductos(const char nombres[][MAX_NAME_LENGTH], const float* tiempos, const float* recursos, const float* cobre, int cantidad_productos) {
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

void editarProducto(char nombres[][MAX_NAME_LENGTH], float* tiempos, float* recursos, float* cobre, int cantidad_productos) {
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
            printf("5. Salir de edicion\n");
            
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
                    printf("Finalizando edicion del producto.\n");
                    break;
                default:
                    printf("Opcion invalida. Intente de nuevo.\n");
            }

        } while (opcion != 5);

    } else {
        printf("Producto no encontrado.\n");
    }
}

void eliminarProducto(char nombres[][MAX_NAME_LENGTH], float* tiempos, float* recursos, float* cobre, int* cantidad_productos) {
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
        }
        (*cantidad_productos)--;
        printf("Producto eliminado.\n");
    } else {
        printf("Producto no encontrado.\n");
    }
}


void ingresarRecursosDisponibles(float* tiempo_disp, float* alum_disp, float* cobre_disp) {
    printf("\n--- Estado Actual de Recursos ---\n");
    printf("  Tiempo disponible:   %.2f horas\n", *tiempo_disp);
    printf("  Aluminio disponible: %.2f mg\n", *alum_disp);
    printf("  Cobre disponible:    %.2f mg\n", *cobre_disp);

    printf("\n--- Actualizar Recursos ---\n");
    *tiempo_disp = ingresaFloat("Ingrese la nueva cantidad de horas disponibles");
    *alum_disp = ingresaFloat("Ingrese la nueva cantidad de aluminio total (mg)");
    *cobre_disp = ingresaFloat("Ingrese la nueva cantidad de cobre total (mg)");
    printf("Recursos actualizados exitosamente.\n");
}


void gestionarCarrito(const char nombres[][MAX_NAME_LENGTH], const float tiempos[], const float recursos[], const float cobre[], int cantidad_productos, float* tiempo_disp, float* alum_disp, float* cobre_disp) {
    if (cantidad_productos == 0) {
        printf("No hay productos definidos para comprar.\n");
        return;
    }

    
    int cantidades[MAX_PRODUCTS] = {0};
    int opcion_menu = 0;
    int en_carrito = 1;

    while (en_carrito) {
        printf("\n======= MENU CARRITO DE COMPRA =======\n");
        printf("Seleccione un producto para agregrar/modificar unidades:\n");
        
        
        for (int i = 0; i < cantidad_productos; i++) {
            printf("%d. %s (Actualmente en carrito: %d)\n", i + 1, nombres[i], cantidades[i]);
        }
        
        
        int opc_confirmar = cantidad_productos + 1;
        int opc_salir = cantidad_productos + 2;

        printf("%d. CONFIRMAR PROCESO DE PRODUCCION\n", opc_confirmar);
        printf("%d. Volver al Menu Principal (Cancelar)\n", opc_salir);
        printf("======================================\n");

        opcion_menu = ingresaEntero("Seleccione una opcion");

        
        if (opcion_menu >= 1 && opcion_menu <= cantidad_productos) {
            
            int idx = opcion_menu - 1; 
            
            printf("\n--- Producto seleccionado: %s ---\n", nombres[idx]);
            printf("Unidades actuales: %d\n", cantidades[idx]);
            printf("Ingrese la nueva cantidad de unidades (0 para quitar, -1 para cancelar): ");
            
            int nueva_cantidad;
            if (scanf("%d", &nueva_cantidad) == 1) {
                while(getchar() != '\n'); 
                
                if (nueva_cantidad >= 0) {
                    cantidades[idx] = nueva_cantidad;
                    printf(">> Cantidad actualizada correctamente.\n");
                } else {
                    printf(">> Operacion cancelada. Volviendo a la lista de productos.\n");
                }
            } else {
                while(getchar() != '\n');
                printf(">> Error: Entrada no valida.\n");
            }

        } 
        else if (opcion_menu == opc_confirmar) {
            
            double tiempo_req_total = 0;
            double alum_req_total = 0;
            double cobre_req_total = 0;
            int hay_items = 0;

            for (int i = 0; i < cantidad_productos; ++i) {
                if (cantidades[i] > 0) {
                    tiempo_req_total += (double)tiempos[i] * cantidades[i];
                    alum_req_total += (double)recursos[i] * cantidades[i];
                    cobre_req_total += (double)cobre[i] * cantidades[i];
                    hay_items++;
                }
            }

            if (hay_items == 0) {
                printf("\n>> El carrito esta vacio. Seleccione productos primero.\n");
            } else {
                printf("\n--- Resumen Final ---\n");
                printf("Tiempo requerido:   %.2f h\n", tiempo_req_total);
                printf("Aluminio requerido: %.2f mg\n", alum_req_total);
                printf("Cobre requerido:    %.2f mg\n", cobre_req_total);
                printf("-------------------------\n");
                printf("Recursos Disponibles -> T: %.2f h, Al: %.2f mg, Cu: %.2f mg\n", *tiempo_disp, *alum_disp, *cobre_disp);

                if (tiempo_req_total > *tiempo_disp || alum_req_total > *alum_disp || cobre_req_total > *cobre_disp) {
                    printf("\n[ERROR] RECURSOS INSUFICIENTES. Ajuste cantidades en el carrito.\n");
                } else {
                    int confirm = ingresaEntero("Confirma descontar estos recursos? (1: Si, 2: No)");
                    if (confirm == 1) {
                        *tiempo_disp -= (float)tiempo_req_total;
                        *alum_disp -= (float)alum_req_total;
                        *cobre_disp -= (float)cobre_req_total;
                        printf("\n>> Produccion EXITOSA. Recursos descontados.\n");
                        en_carrito = 0; 
                    } else {
                        printf("\n>> Confirmacion cancelada. Volviendo al carrito.\n");
                    }
                }
            }

        } 
        else if (opcion_menu == opc_salir) {
            
            printf("\n>> Saliendo del carrito sin realizar cambios.\n");
            en_carrito = 0; 
        } 
        else {
            printf("\n>> Opcion invalida. Intente nuevamente.\n");
        }
    }
}
