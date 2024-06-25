#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir el número máximo de tiquetes que se pueden almacenar
#define MAX_TICKETS 100

// Estructura para representar un tiquete
typedef struct {
    int numeroFactura;         // Número de factura del tiquete
    int cedula;                // Cédula del comprador
    char nombre[100];          // Nombre del comprador
    int localidad;             // Localidad deseada
    int cantidadEntradas;      // Cantidad de entradas compradas
    float subtotal;            // Subtotal del costo de las entradas
    float cargosServicio;      // Cargos adicionales por servicios
    float totalPagar;          // Total a pagar por el tiquete
} Ticket;

// Arreglo para almacenar los tiquetes
Ticket tickets[MAX_TICKETS];
int ticketCount = 0; // Contador de tiquetes almacenados

// Declaración de funciones
void insertarTicket();
void consultarTicket();
void modificarTicket();
void borrarTicket();
void mostrarMenu();

// Función principal
int main() {
    int opcion;

    // Bucle para mostrar el menú hasta que el usuario decida salir
    do {
        mostrarMenu();
        scanf("%d", &opcion);

        // Seleccionar la acción correspondiente a la opción ingresada
        switch (opcion) {
            case 1:
                insertarTicket();
                break;
            case 2:
                consultarTicket();
                break;
            case 3:
                modificarTicket();
                break;
            case 4:
                borrarTicket();
                break;
            case 5:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    return 0;
}

// Función para mostrar el menú de opciones
void mostrarMenu() {
    printf("\nMenu de opciones:\n");
    printf("1. Insertar tiquete\n");
    printf("2. Consultar tiquete\n");
    printf("3. Modificar tiquete\n");
    printf("4. Borrar tiquete\n");
    printf("5. Salir\n");
    printf("Ingrese una opcion: ");
}

// Función para insertar un nuevo tiquete
void insertarTicket() {
    if (ticketCount >= MAX_TICKETS) {
        printf("Error: No se pueden agregar más tiquetes.\n");
        return;
    }

    Ticket t; // Crear una variable de tipo Ticket para almacenar los datos ingresados
    const float cargoServicioPorEntrada = 1000.0; // Costo del cargo por servicio por cada entrada
    char nombreLocalidad[20]; // Cadena para almacenar el nombre de la localidad

    // Pedir al usuario que ingrese los datos del tiquete
    printf("Ingrese el numero de factura: ");
    scanf("%d", &t.numeroFactura);

    printf("Ingrese la cedula del comprador: ");
    scanf("%d", &t.cedula);

    printf("Ingrese el nombre del comprador: ");
    scanf("%s", t.nombre);

    // Pedir la localidad deseada y validar la entrada
    do {
        printf("Ingrese la localidad deseada (1-Sol Norte/Sur, 2-Sombra Este/Oeste, 3-Preferencial): ");
        scanf("%d", &t.localidad);
    } while (t.localidad < 1 || t.localidad > 3);

    // Pedir la cantidad de entradas y validar la entrada
    do {
        printf("Ingrese la cantidad de entradas (maximo 4): ");
        scanf("%d", &t.cantidadEntradas);
    } while (t.cantidadEntradas < 1 || t.cantidadEntradas > 4);

    // Calcular el subtotal en función de la localidad y la cantidad de entradas
    if (t.localidad == 1) {
        t.subtotal = t.cantidadEntradas * 10500.0; // Precio para Sol Norte/Sur
        snprintf(nombreLocalidad, sizeof(nombreLocalidad), "Sol Norte/Sur");
    } else if (t.localidad == 2) {
        t.subtotal = t.cantidadEntradas * 20500.0; // Precio para Sombra Este/Oeste
        snprintf(nombreLocalidad, sizeof(nombreLocalidad), "Sombra Este/Oeste");
    } else if (t.localidad == 3) {
        t.subtotal = t.cantidadEntradas * 25500.0; // Precio para Preferencial
        snprintf(nombreLocalidad, sizeof(nombreLocalidad), "Preferencial");
    }

    // Calcular los cargos por servicio y el total a pagar
    t.cargosServicio = t.cantidadEntradas * cargoServicioPorEntrada;
    t.totalPagar = t.subtotal + t.cargosServicio;

    // Almacenar el tiquete en el arreglo y aumentar el contador
    tickets[ticketCount++] = t;

    // Mostrar los detalles del tiquete agregado
    printf("Tiquete agregado con exito!\n");
    printf("Numero de Factura: %d\n", t.numeroFactura);
    printf("Cedula: %d\n", t.cedula);
    printf("Nombre comprador: %s\n", t.nombre);
    printf("Localidad: %s\n", nombreLocalidad);
    printf("Cantidad de Entradas: %d\n", t.cantidadEntradas);
    printf("Subtotal: %.2f colones\n", t.subtotal);
    printf("Cargos por Servicios: %.2f colones\n", t.cargosServicio);
    printf("Total a pagar: %.2f colones\n\n", t.totalPagar);
}

// Función para consultar un tiquete existente
void consultarTicket() {
    int numeroFactura, found = 0;

    printf("Ingrese el numero de factura a consultar: ");
    scanf("%d", &numeroFactura);

    // Buscar el tiquete en el arreglo
    for (int i = 0; i < ticketCount; i++) {
        if (tickets[i].numeroFactura == numeroFactura) {
            // Si se encuentra el tiquete, mostrar los detalles
            printf("Tiquete encontrado!\n");
            printf("Numero de Factura: %d\n", tickets[i].numeroFactura);
            printf("Cedula: %d\n", tickets[i].cedula);
            printf("Nombre comprador: %s\n", tickets[i].nombre);
            printf("Localidad: %d\n", tickets[i].localidad);
            printf("Cantidad de Entradas: %d\n", tickets[i].cantidadEntradas);
            printf("Subtotal: %.2f colones\n", tickets[i].subtotal);
            printf("Cargos por Servicios: %.2f colones\n", tickets[i].cargosServicio);
            printf("Total a pagar: %.2f colones\n\n", tickets[i].totalPagar);
            found = 1;
            break;
        }
    }

    // Si no se encuentra el tiquete, mostrar un mensaje
    if (!found) {
        printf("Tiquete no encontrado.\n");
    }
}

// Función para modificar un tiquete existente
void modificarTicket() {
    int numeroFactura, found = 0;

    printf("Ingrese el numero de factura a modificar: ");
    scanf("%d", &numeroFactura);

    // Buscar el tiquete en el arreglo
    for (int i = 0; i < ticketCount; i++) {
        if (tickets[i].numeroFactura == numeroFactura) {
            found = 1;

            // Pedir los nuevos datos del tiquete
            printf("Ingrese la nueva cedula del comprador: ");
            scanf("%d", &tickets[i].cedula);

            printf("Ingrese el nuevo nombre del comprador: ");
            scanf("%s", tickets[i].nombre);

            // Pedir y validar la nueva localidad
            do {
                printf("Ingrese la nueva localidad deseada (1-Sol Norte/Sur, 2-Sombra Este/Oeste, 3-Preferencial): ");
                scanf("%d", &tickets[i].localidad);
            } while (tickets[i].localidad < 1 || tickets[i].localidad > 3);

            // Pedir y validar la nueva cantidad de entradas
            do {
                printf("Ingrese la nueva cantidad de entradas (maximo 4): ");
                scanf("%d", &tickets[i].cantidadEntradas);
            } while (tickets[i].cantidadEntradas < 1 || tickets[i].cantidadEntradas > 4);

            // Calcular el nuevo subtotal, cargos por servicio y total a pagar
            const float cargoServicioPorEntrada = 1000.0;
            if (tickets[i].localidad == 1) {
                tickets[i].subtotal = tickets[i].cantidadEntradas * 10500.0;
            } else if (tickets[i].localidad == 2) {
                tickets[i].subtotal = tickets[i].cantidadEntradas * 20500.0;
            } else if (tickets[i].localidad == 3) {
                tickets[i].subtotal = tickets[i].cantidadEntradas * 25500.0;
            }

            tickets[i].cargosServicio = tickets[i].cantidadEntradas * cargoServicioPorEntrada;
            tickets[i].totalPagar = tickets[i].subtotal + tickets[i].cargosServicio;

            // Mostrar los detalles del tiquete modificado
            printf("Tiquete modificado con exito!\n");
            printf("Numero de Factura: %d\n", tickets[i].numeroFactura);
            printf("Cedula: %d\n", tickets[i].cedula);
            printf("Nombre comprador: %s\n", tickets[i].nombre);
            printf("Localidad: %d\n", tickets[i].localidad);
            printf("Cantidad de Entradas: %d\n", tickets[i].cantidadEntradas);
            printf("Subtotal: %.2f colones\n", tickets[i].subtotal);
            printf("Cargos por Servicios: %.2f colones\n", tickets[i].cargosServicio);
            printf("Total a pagar: %.2f colones\n\n", tickets[i].totalPagar);

            break;
        }
    }

    // Si no se encuentra el tiquete, mostrar un mensaje
    if (!found) {
        printf("Tiquete no encontrado.\n");
    }
}

// Función para borrar un tiquete existente
void borrarTicket() {
    int numeroFactura, found = 0;

    printf("Ingrese el numero de factura a borrar: ");
    scanf("%d", &numeroFactura);

    // Buscar el tiquete en el arreglo
    for (int i = 0; i < ticketCount; i++) {
        if (tickets[i].numeroFactura == numeroFactura) {
            found = 1;

            // Desplazar todos los tiquetes subsiguientes una posición hacia atrás
            for (int j = i; j < ticketCount - 1; j++) {
                tickets[j] = tickets[j + 1];
            }

            ticketCount--; // Disminuir el contador de tiquetes
            printf("Tiquete borrado con exito!\n");
            break;
        }
    }

    // Si no se encuentra el tiquete, mostrar un mensaje
    if (!found) {
        printf("Tiquete no encontrado.\n");
    }
}
