#include "artemis.h"
#include "validaciones.h"

#include <stdio.h>

int main(void)
{
    int opcion;

    mostrarTitulo();

    do {
        int opcionMaxima;

        mostrarMenu();

#if ETAPA >= 2
        opcionMaxima = 2;
#else
        opcionMaxima = 1;
#endif

        opcion = leerEntero("Opción: ", 0, opcionMaxima);

        switch (opcion) {
        case 1:
            ejecutarMision();
            break;

#if ETAPA >= 2
        case 2:
            mostrarReporte();
            break;
#endif

        case 0:
            puts("Simulación finalizada. Buen viaje, Orion.");
            break;

        default:
            /* La validación del rango evita llegar a esta rama. */
            break;
        }
    } while (opcion != 0);

    return 0;
}
