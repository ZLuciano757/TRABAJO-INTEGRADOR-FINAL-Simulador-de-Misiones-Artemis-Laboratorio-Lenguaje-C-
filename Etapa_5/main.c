#include "artemis.h"
#include "validaciones.h"

#include <stdio.h>

/* Controla el menu principal hasta que el usuario elige salir. */
int main(void)
{
    int opcionElegida = -1;

    mostrarTitulo();

    while (opcionElegida != 0) {
        mostrarMenu();

        if (!leerNumeroEntero("Opcion: ", 0, 2, &opcionElegida)) {
            puts("\nSe finalizo la entrada de datos.");
            break;
        }

        if (opcionElegida == 1) {
            ejecutarMision();
        } else if (opcionElegida == 2) {
            mostrarReporte();
        }
    }

    puts("Simulacion finalizada.");
    return 0;
}
