#ifndef OPERACIONES_H
#define OPERACIONES_H

#define MAX_PRODUCTOS 100
#define MAX_CLIENTES 100
#define MAX_FACTURAS 100
#define MAX_GENEROS 5

typedef struct {
    char nombre[50];
    int cantidad;
    float precio;
    char genero[40];
} Producto;

typedef struct {
    char cedula[11];
    char nombre[50];
} Cliente;

typedef struct {
    char fecha[11];
    char cedula[11];
    char nombre[50];
    float montoPagado;
    int productosComprados;
} Factura;

typedef struct {
    int vinilos;
    int cds;
    int cassettes;
} Inventario;

extern Producto productos[MAX_PRODUCTOS];
extern int numProductos;
extern Cliente clientes[MAX_CLIENTES];
extern int numClientes;
extern Factura facturas[MAX_FACTURAS];
extern int numFacturas;
extern Inventario inventario[MAX_GENEROS];
extern const char* generos[MAX_GENEROS];

void cargarProductos();
void guardarProductos();
void cargarClientes();
void guardarClientes();
void cargarFacturas();
void guardarFacturas();
void checkGenerosAumento(char genero[], int cantidad, char nombre[]);
void aumentarProductos(int prod, int cant, char nomb[]);
void agregarProducto();
void modificarProducto();
void eliminarProducto();
void aumentarStock();
void agregarCliente();
void modificarCliente();
void ingresoCedula(char cedula[]);
void crearFactura();
void listarClientes();
void listarFacturas();
void checkGenerosDisminuir(char genero[], int cantidad, char nombre[]);
void disminuirProductos(int prod, int cant, char nomb[]);
void consultarProducto();
void verProductos();
void consultarCliente();
void buscarFactura();

#endif
