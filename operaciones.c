#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "operaciones.h"

Producto productos[MAX_PRODUCTOS];
int numProductos = 0;
Cliente clientes[MAX_CLIENTES];
int numClientes = 0;
Factura facturas[MAX_FACTURAS];
int numFacturas = 0;
Inventario inventario[MAX_GENEROS] = {};
const char* generos[MAX_GENEROS] = {"Jazz", "Funk", "Pop", "Reguetón", "Clásico"};

void cargarProductos() {
    FILE *archivo = fopen("productos.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %d %f %s", productos[numProductos].nombre, &productos[numProductos].cantidad, &productos[numProductos].precio, productos[numProductos].genero) != EOF) {
            numProductos++;
        }
        fclose(archivo);
    }
}

void guardarProductos() {
    FILE *archivo = fopen("productos.txt", "w");
    for (int i = 0; i < numProductos; i++) {
        fprintf(archivo, "%s %d %.2f %s\n", productos[i].nombre, productos[i].cantidad, productos[i].precio, productos[i].genero);
    }
    fclose(archivo);
}

void cargarClientes() {
    FILE *archivo = fopen("clientes.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %s", clientes[numClientes].cedula, clientes[numClientes].nombre) != EOF) {
            numClientes++;
        }
        fclose(archivo);
    }
}

void guardarClientes() {
    FILE *archivo = fopen("clientes.txt", "w");
    for (int i = 0; i < numClientes; i++) {
        fprintf(archivo, "%s %s\n", clientes[i].cedula, clientes[i].nombre);
    }
    fclose(archivo);
}

void cargarFacturas() {
    FILE *archivo = fopen("facturas.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %s %s %f %d", facturas[numFacturas].fecha, facturas[numFacturas].cedula, facturas[numFacturas].nombre, &facturas[numFacturas].montoPagado, &facturas[numFacturas].productosComprados) != EOF) {
            numFacturas++;
        }
        fclose(archivo);
    }
}

void guardarFacturas() {
    FILE *archivo = fopen("facturas.txt", "w");
    for (int i = 0; i < numFacturas; i++) {
        fprintf(archivo, "%s %s %s %.2f %d\n", facturas[i].fecha, facturas[i].cedula, facturas[i].nombre, facturas[i].montoPagado, facturas[i].productosComprados);
    }
    fclose(archivo);
}

void checkGenerosAumento(char genero[], int cantidad, char nombre[]) {
    if (strcmp(genero, "Jazz") == 0) {
        aumentarProductos(0, cantidad, nombre);
    } else if (strcmp(genero, "Funk") == 0) {
        aumentarProductos(1, cantidad, nombre);
    } else if (strcmp(genero, "Pop") == 0) {
        aumentarProductos(2, cantidad, nombre);
    } else if (strcmp(genero, "Reguetón") == 0) {
        aumentarProductos(3, cantidad, nombre);
    } else if (strcmp(genero, "Clásico") == 0) {
        aumentarProductos(4, cantidad, nombre);
    }
}

void aumentarProductos(int prod, int cant, char nomb[]) {
    if (strcmp(nomb, "Vinilo") == 0) {
        inventario[prod].vinilos = inventario[prod].vinilos + cant;
    } else if (strcmp(nomb, "CDs") == 0) {
        inventario[prod].cds = inventario[prod].cds + cant;
    } else if (strcmp(nomb, "Cassetes") == 0) {
        inventario[prod].cassettes = inventario[prod].cassettes + cant;
    }
}

void agregarProducto() {
    if (numProductos >= MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos.\n");
        return;
    }
    printf("Ingrese el nombre del producto: ");
    scanf("%s", productos[numProductos].nombre);
    printf("Ingrese la cantidad del producto: ");
    scanf("%d", &productos[numProductos].cantidad);
    printf("Ingrese el precio del producto: ");
    scanf("%f", &productos[numProductos].precio);
    printf("Ingrese el género del producto: ");
    scanf("%s", productos[numProductos].genero);
    checkGenerosAumento(productos[numProductos].genero, productos[numProductos].cantidad, productos[numProductos].nombre);
    numProductos++;
    guardarProductos();
    printf("Producto agregado exitosamente.\n");
}

void modificarProducto() {
    char nombre[50];
    printf("Ingrese el nombre del producto a modificar: ");
    scanf("%s", nombre);
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            printf("Ingrese la nueva cantidad: ");
            scanf("%d", &productos[i].cantidad);
            printf("Ingrese el nuevo precio: ");
            scanf("%f", &productos[i].precio);
            guardarProductos();
            printf("Producto modificado exitosamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void eliminarProducto() {
    char nombre[50];
    printf("Ingrese el nombre del producto a eliminar: ");
    scanf("%s", nombre);
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            for (int j = i; j < numProductos - 1; j++) {
                productos[j] = productos[j + 1];
            }
            numProductos--;
            guardarProductos();
            printf("Producto eliminado exitosamente.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void aumentarStock() {
    char nombre[50];
    int cantidad;
    char genero[40];
    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombre);
    printf("Ingrese la cantidad a aumentar: ");
    scanf("%d", &cantidad);
    printf("Ingrese el nombre del género: ");
    scanf("%s", genero);
    checkGenerosAumento(genero, cantidad, nombre);
    printf("Stock aumentado exitosamente.\n");
}

void agregarCliente() {
    if (numClientes >= MAX_CLIENTES) {
        printf("No se pueden agregar más clientes.\n");
        return;
    }
    ingresoCedula(clientes[numClientes].cedula);
    printf("Ingrese el nombre del cliente: ");
    scanf("%s", clientes[numClientes].nombre);
    numClientes++;
    guardarClientes();
    printf("Cliente agregado exitosamente.\n");
}

void modificarCliente() {
    char cedula[11];
    printf("Ingrese la cédula del cliente a modificar: ");
    scanf("%s", cedula);
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cedula, cedula) == 0) {
            printf("Ingrese el nuevo nombre: ");
            scanf("%s", clientes[i].nombre);
            guardarClientes();
            printf("Cliente modificado exitosamente.\n");
            return;
        }
    }
    printf("Cliente no encontrado.\n");
}

void ingresoCedula(char cedula[]) {
    int flag = 0;
    while (flag == 0) {
        printf("Ingrese la cédula del cliente: ");
        scanf("%s", cedula);
        flag = 1;
        for (int i = 0; i < numClientes; i++) {
            if (strcmp(clientes[i].cedula, cedula) == 0) {
                printf("La cédula ya está registrada. Ingrese otra cédula.\n");
                flag = 0;
                break;
            }
        }
    }
}

void crearFactura() {
    if (numFacturas >= MAX_FACTURAS) {
        printf("No se pueden agregar más facturas.\n");
        return;
    }
    int flag = 0;
    int pos = -1;
    while (flag == 0) {
        printf("Ingrese la cédula del cliente: ");
        scanf("%s", facturas[numFacturas].cedula);
        for (int i = 0; i < numClientes; i++) {
            if (strcmp(clientes[i].cedula, facturas[numFacturas].cedula) == 0) {
                pos = i;
                flag = 1;
            }
        }
        if (flag == 0) {
            printf("Cliente no encontrado\n");
        }
    }
    printf("Ingrese la fecha (dd/mm/aaaa): ");
    scanf("%s", facturas[numFacturas].fecha);
    strcpy(facturas[numFacturas].nombre, clientes[pos].nombre);
    printf("Ingrese el monto pagado: ");
    scanf("%f", &facturas[numFacturas].montoPagado);
    printf("Ingrese la cantidad de productos comprados: ");
    scanf("%d", &facturas[numFacturas].productosComprados);
    numFacturas++;
    guardarFacturas();
    printf("Factura creada exitosamente.\n");
}

void listarClientes() {
    printf("Listado de clientes:\n");
    for (int i = 0; i < numClientes; i++) {
        printf("%s %s\n", clientes[i].cedula, clientes[i].nombre);
    }
}

void listarFacturas() {
    printf("Listado de facturas:\n");
    for (int i = 0; i < numFacturas; i++) {
        printf("Fecha: %s, Cédula: %s, Nombre: %s, Monto: %.2f, Productos: %d\n", facturas[i].fecha, facturas[i].cedula, facturas[i].nombre, facturas[i].montoPagado, facturas[i].productosComprados);
    }
}

void checkGenerosDisminuir(char genero[], int cantidad, char nombre[]) {
    if (strcmp(genero, "Jazz") == 0) {
        disminuirProductos(0, cantidad, nombre);
    } else if (strcmp(genero, "Funk") == 0) {
        disminuirProductos(1, cantidad, nombre);
    } else if (strcmp(genero, "Pop") == 0) {
        disminuirProductos(2, cantidad, nombre);
    } else if (strcmp(genero, "Reguetón") == 0) {
        disminuirProductos(3, cantidad, nombre);
    } else if (strcmp(genero, "Clásico") == 0) {
        disminuirProductos(4, cantidad, nombre);
    }
}

void disminuirProductos(int prod, int cant, char nomb[]) {
    if (strcmp(nomb, "Vinilo") == 0) {
        inventario[prod].vinilos = inventario[prod].vinilos - cant;
    } else if (strcmp(nomb, "CDs") == 0) {
        inventario[prod].cds = inventario[prod].cds - cant;
    } else if (strcmp(nomb, "Cassetes") == 0) {
        inventario[prod].cassettes = inventario[prod].cassettes - cant;
    }
}

void consultarProducto() {
    char nombre[50];
    printf("Ingrese el nombre del producto a consultar: ");
    scanf("%s", nombre);
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            printf("Producto: %s, Cantidad: %d, Precio: %.2f, Género: %s\n", productos[i].nombre, productos[i].cantidad, productos[i].precio, productos[i].genero);
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void verProductos() {
    printf("Listado de productos:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("Producto: %s, Cantidad: %d, Precio: %.2f, Género: %s\n", productos[i].nombre, productos[i].cantidad, productos[i].precio, productos[i].genero);
    }
}

void consultarCliente() {
    char cedula[11];
    printf("Ingrese la cédula del cliente a consultar: ");
    scanf("%s", cedula);
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cedula, cedula) == 0) {
            printf("Cédula: %s, Nombre: %s\n", clientes[i].cedula, clientes[i].nombre);
            return;
        }
    }
    printf("Cliente no encontrado.\n");
}

void buscarFactura() {
    char cedula[11];
    printf("Ingrese la cédula del cliente de la factura a buscar: ");
    scanf("%s", cedula);
    for (int i = 0; i < numFacturas; i++) {
        if (strcmp(facturas[i].cedula, cedula) == 0) {
            printf("Fecha: %s, Cédula: %s, Nombre: %s, Monto: %.2f, Productos: %d\n", facturas[i].fecha, facturas[i].cedula, facturas[i].nombre, facturas[i].montoPagado, facturas[i].productosComprados);
            return;
        }
    }
    printf("Factura no encontrada.\n");
}
