#include <stdio.h>
#include "lectura.h"
#include "operaciones.h"

void leerProductos() {
    FILE *archivo = fopen("productos.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %d %f %s", productos[numProductos].nombre, &productos[numProductos].cantidad, &productos[numProductos].precio, productos[numProductos].genero) != EOF) {
            numProductos++;
        }
        fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo de productos.\n");
    }
}

void leerClientes() {
    FILE *archivo = fopen("clientes.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %s", clientes[numClientes].cedula, clientes[numClientes].nombre) != EOF) {
            numClientes++;
        }
        fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo de clientes.\n");
    }
}

void leerFacturas() {
    FILE *archivo = fopen("facturas.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %s %s %f %d", facturas[numFacturas].fecha, facturas[numFacturas].cedula, facturas[numFacturas].nombre, &facturas[numFacturas].montoPagado, &facturas[numFacturas].productosComprados) != EOF) {
            numFacturas++;
        }
        fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo de facturas.\n");
    }
}

