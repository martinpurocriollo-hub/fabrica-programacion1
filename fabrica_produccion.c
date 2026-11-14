#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROD 5

void ingresarProductos(char nombres[][50], int *cantidades, float *tiempos, float *recursos, int *numProductos);
void mostrarProductos(char nombres[][50], int *cantidades, float *tiempos, float *recursos, int numProductos);
void buscarProducto(char nombres[][50], int numProductos, char *buscado, int *indiceEncontrado);
void editarProducto(char nombres[][50], int *cantidades, float *tiempos, float *recursos, int numProductos);
void eliminarProducto(char nombres[][50], int *cantidades, float *tiempos, float *recursos, int *numProductos);
void calcularOptimizacion(int *cantidades, float *tiempos, float *recursos, int numProductos);

int main() {
    char nombres[MAX_PROD][50];
    int cantidades[MAX_PROD];
    float tiempos[MAX_PROD];
    float recursos[MAX_PROD];
    int numProductos = 0;
    int opcion;

    do {
        printf("\n===================================================\n");
        printf("    SISTEMA DE OPTIMIZACION - FABRICA ELECTRONICA  \n");
        printf("===================================================\n");
        printf(" 1. Ingresar producto                             \n");
        printf(" 2. Mostrar listado de productos                  \n");
        printf(" 3. Editar producto                               \n");
        printf(" 4. Eliminar producto                             \n");
        printf(" 5. Calcular tiempo, recursos y cumplimiento      \n");
        printf(" 6. Salir                                         \n");
        printf("===================================================\n");
        printf(" Seleccione una opcion (1-6): ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ingresarProductos(nombres, cantidades, tiempos, recursos, &numProductos);
                break;
            case 2:
                mostrarProductos(nombres, cantidades, tiempos, recursos, numProductos);
                break;
            case 3:
                editarProducto(nombres, cantidades, tiempos, recursos, numProductos);
                break;
            case 4:
                eliminarProducto(nombres, cantidades, tiempos, recursos, &numProductos);
                break;
            case 5:
                calcularOptimizacion(cantidades, tiempos, recursos, numProductos);
                break;
            case 6:
                printf("\nSaliendo del sistema de optimizacion...\n");
                break;
            default:
                printf("\n[!] Opcion incorrecta. Intente nuevamente.\n");
        }

    } while (opcion != 6);

    return 0;
}

void ingresarProductos(char nombres[][50], int *cantidades, float *tiempos, float *recursos, int *numProductos) {
    if (*numProductos >= MAX_PROD) {
        printf("\n[!] Ya se han ingresado el maximo de %d productos.\n", MAX_PROD);
        return;
    }
    
    printf("\n--- Registro de Producto %d/%d ---\n", *numProductos + 1, MAX_PROD);
    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombres[*numProductos]);
    
    printf("Ingrese la cantidad demandada: ");
    scanf("%d", cantidades + *numProductos);
    while (*(cantidades + *numProductos) < 0) {
        printf("Error. La cantidad no puede ser negativa. Reingrese: ");
        scanf("%d", cantidades + *numProductos);
    }
    
    printf("Ingrese el tiempo de fabricacion por unidad (horas): ");
    scanf("%f", tiempos + *numProductos);
    while (*(tiempos + *numProductos) < 0) {
        printf("Error. El tiempo no puede ser negativo. Reingrese: ");
        scanf("%f", tiempos + *numProductos);
    }
    
    printf("Ingrese la cantidad de recursos por unidad: ");
    scanf("%f", recursos + *numProductos);
    while (*(recursos + *numProductos) < 0) {
        printf("Error. Los recursos no pueden ser negativos. Reingrese: ");
        scanf("%f", recursos + *numProductos);
    }
    
    (*numProductos)++;
    printf("\n[Exito] Producto registrado correctamente.\n");
}

void mostrarProductos(char nombres[][50], int *cantidades, float *tiempos, float *recursos, int numProductos) {
    if (numProductos == 0) {
        printf("\n[!] No hay productos registrados en el sistema.\n");
        return;
    }
    
    printf("\n==================== LISTADO DE PRODUCTOS ====================\n");
    printf("%-5s | %-15s | %-10s | %-15s | %-15s\n", "No.", "Nombre", "Demanda", "Tiempo U. (h)", "Recurso U.");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < numProductos; i++) {
        printf("%-5d | %-15s | %-10d | %-15.2f | %-15.2f\n", 
               i + 1, *(nombres + i), *(cantidades + i), *(tiempos + i), *(recursos + i));
    }
    printf("==============================================================\n");
}

void buscarProducto(char nombres[][50], int numProductos, char *buscado, int *indiceEncontrado) {
    *indiceEncontrado = -1;
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(*(nombres + i), buscado) == 0) {
            *indiceEncontrado = i;
            break;
        }
    }
}

void editarProducto(char nombres[][50], int *cantidades, float *tiempos, float *recursos, int numProductos) {
    if (numProductos == 0) {
        printf("\n[!] No hay productos para editar.\n");
        return;
    }
    
    char nombreBuscado[50];
    int indice = -1;
    
    printf("\n--- Editar Producto ---\n");
    printf("Ingrese el nombre del producto que desea buscar y editar: ");
    scanf("%s", nombreBuscado);
    
    buscarProducto(nombres, numProductos, nombreBuscado, &indice);
    
    if (indice == -1) {
        printf("\n[!] Producto no encontrado en el sistema.\n");
    } else {
        printf("\n[OK] Producto encontrado en la posicion %d.\n", indice + 1);
        printf("Ingrese el nuevo nombre del producto: ");
        scanf("%s", nombres[indice]);
        
        printf("Ingrese la nueva cantidad demandada: ");
        scanf("%d", cantidades + indice);
        
        printf("Ingrese el nuevo tiempo de fabricacion por unidad (h): ");
        scanf("%f", tiempos + indice);
        
        printf("Ingrese la nueva cantidad de recursos por unidad: ");
        scanf("%f", recursos + indice);
        
        printf("\n[Exito] Producto modificado correctamente.\n");
    }
}

void eliminarProducto(char nombres[][50], int *cantidades, float *tiempos, float *recursos, int *numProductos) {
    if (*numProductos == 0) {
        printf("\n[!] No hay productos para eliminar.\n");
        return;
    }
    
    char nombreBuscado[50];
    int indice = -1;
    
    printf("\n--- Eliminar Producto ---\n");
    printf("Ingrese el nombre del producto que desea eliminar: ");
    scanf("%s", nombreBuscado);
    
    buscarProducto(nombres, *numProductos, nombreBuscado, &indice);
    
    if (indice == -1) {
        printf("\n[!] Producto no encontrado.\n");
    } else {
        for (int i = indice; i < *numProductos - 1; i++) {
            strcpy(nombres[i], nombres[i + 1]);
            *(cantidades + i) = *(cantidades + i + 1);
            *(tiempos + i) = *(tiempos + i + 1);
            *(recursos + i) = *(recursos + i + 1);
        }
        (*numProductos)--;
        printf("\n[Exito] Producto eliminado correctamente.\n");
    }
}

void calcularOptimizacion(int *cantidades, float *tiempos, float *recursos, int numProductos) {
    if (numProductos == 0) {
        printf("\n[!] No hay productos registrados para calcular la optimizacion.\n");
        return;
    }
    
    float tiempoDisponible, recursosDisponibles;
    float tiempoTotal = 0;
    float recursosTotales = 0;
    
    printf("\n--- Analisis de Optimizacion y Produccion ---\n");
    printf("Ingrese el tiempo total disponible en la fabrica (horas): ");
    scanf("%f", &tiempoDisponible);
    
    printf("Ingrese la cantidad total de recursos disponibles en la fabrica: ");
    scanf("%f", &recursosDisponibles);
    
    for (int i = 0; i < numProductos; i++) {
        float tiempoProd = (*(cantidades + i)) * (*(tiempos + i));
        float recursoProd = (*(cantidades + i)) * (*(recursos + i));
        tiempoTotal += tiempoProd;
        recursosTotales += recursoProd;
    }
    
    printf("\n================ RESULTADOS DEL ANALISIS ================\n");
    printf("Tiempo total de fabricacion requerido: %.2f horas\n", tiempoTotal);
    printf("Recursos totales requeridos: %.2f unidades\n", recursosTotales);
    printf("---------------------------------------------------------\n");
    printf("Limite de tiempo disponible: %.2f horas\n", tiempoDisponible);
    printf("Limite de recursos disponibles: %.2f unidades\n", recursosDisponibles);
    printf("---------------------------------------------------------\n");
    
    if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles) {
        printf("[ESTADO] La fabrica PUEDE cumplir con toda la demanda.\n");
        printf("         Los recursos y el tiempo son suficientes.\n");
    } else {
        printf("[ESTADO] La fabrica NO PUEDE cumplir con toda la demanda.\n");
        if (tiempoTotal > tiempoDisponible) {
            printf("  -> Exceso de tiempo requerido: %.2f horas (Faltan horas)\n", tiempoTotal - tiempoDisponible);
        }
        if (recursosTotales > recursosDisponibles) {
            printf("  -> Exceso de recursos requeridos: %.2f unidades (Faltan recursos)\n", recursosTotales - recursosDisponibles);
        }
    }
    printf("=========================================================\n");
}