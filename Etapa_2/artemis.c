#include "artemis.h"
#include "validaciones.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

static Mision misionActual;
static Resultado resultadoActual;
static int hayReporte = 0;

void mostrarTitulo(void)
{
    puts("\n==============================================");
    puts("     ARTEMIS: SIMULADOR DE INYECCION TLI");
    puts("==============================================");
}

void mostrarMenu(void)
{
    puts("\n1. Iniciar misión");

#if ETAPA >= 2
    puts("2. Ver último reporte");
#endif

    puts("0. Salir");
}

void ejecutarMision(void)
{
#if ETAPA == 1
    puts("\nOrion se prepara para la maniobra TLI.");
    puts("En la siguiente etapa se incorporarán los datos de la misión.");

#elif ETAPA == 2
    memset(&misionActual, 0, sizeof misionActual);

    leerTexto("\nNombre del operador/a: ",
              misionActual.nombre,
              sizeof misionActual.nombre);
    misionActual.masa = leerReal("Masa de Orion en kg [1, 100000]: ",
                                 1.0, 100000.0);
    misionActual.velocidad = leerReal("Velocidad TLI en m/s [1, 50000]: ",
                                      1.0, 50000.0);
    misionActual.altitud = leerReal("Altitud LEO en m [1, 1000000]: ",
                                    1.0, 1000000.0);
    misionActual.distancia = leerReal(
        "Distancia Tierra-Luna en m [1e6, 1e9]: ",
        1e6, 1e9
    );

    hayReporte = 1;

    puts("\nDatos de la misión registrados.");
    puts("Con los motores apagados, Orion continúa por inercia.");
    puts("Los cálculos físicos se incorporarán en la siguiente etapa.");

#elif ETAPA >= 3
    memset(&misionActual, 0, sizeof misionActual);

    leerTexto("\nNombre del operador/a: ",
              misionActual.nombre,
              sizeof misionActual.nombre);
    misionActual.masa = leerReal("Masa de Orion en kg [1, 100000]: ",
                                 1.0, 100000.0);
    misionActual.velocidad = leerReal("Velocidad TLI en m/s [1, 50000]: ",
                                      1.0, 50000.0);
    misionActual.altitud = leerReal("Altitud LEO en m [1, 1000000]: ",
                                    1.0, 1000000.0);
    misionActual.distancia = leerReal(
        "Distancia Tierra-Luna en m [1e6, 1e9]: ",
        1e6, 1e9
    );

    misionActual.constanteG = G;
    misionActual.masaTierra = MASA_TIERRA;
    misionActual.masaLuna = MASA_LUNA;

#if ETAPA >= 4
    puts("\nConstantes de referencia cargadas. Puede ajustarlas:");
    misionActual.constanteG = leerReal(
        "Constante G [1e-12, 1e-9]: ", 1e-12, 1e-9
    );
    misionActual.masaTierra = leerReal(
        "Masa terrestre en kg [1e23, 1e25]: ", 1e23, 1e25
    );
    misionActual.masaLuna = leerReal(
        "Masa lunar en kg [1e21, 1e23]: ", 1e21, 1e23
    );

    {
        const char *eventos[] = {
            "TLI ejecutada e ICPS desacoplada",
            "Crucero translunar con motores apagados",
            "Llegada a la región de equilibrio idealizada"
        };
        int puntaje = 100;
        int decision;
        size_t i;

        puts("\n--- EVENTOS DE LA MISION ---");

        for (i = 0; i < sizeof eventos / sizeof eventos[0]; i++) {
            printf("\nEvento %zu: %s\n", i + 1, eventos[i]);
            puts("1. Monitoreo nominal");
            puts("2. Registrar alerta");

            decision = leerEntero("Seleccione 1 o 2: ", 1, 2);

            if (decision == 2) {
                puntaje -= 10;
                puts("Alerta registrada. Se descuentan 10 puntos.");
            } else {
                puts("Telemetría nominal registrada.");
            }
        }

        printf("\nMisión completada. Puntaje operativo: %d/100.\n",
               puntaje);
    }
#endif

    calcularResultado(&misionActual, &resultadoActual);
    hayReporte = 1;
    mostrarReporte();
#endif
}

void calcularResultado(const Mision *mision, Resultado *resultado)
{
    if (mision == NULL || resultado == NULL) {
        return;
    }

#if ETAPA >= 3
    {
        double radioInicial = RADIO_TIERRA + mision->altitud;
        double equilibrio = mision->distancia *
            sqrt(mision->masaTierra) /
            (sqrt(mision->masaTierra) + sqrt(mision->masaLuna));
        double potencialInicial;
        double potencialEquilibrio;

        resultado->energiaCinetica =
            0.5 * mision->masa * mision->velocidad * mision->velocidad;
        resultado->rapidezEscape =
            sqrt(2.0 * mision->constanteG * mision->masaTierra /
                 radioInicial);
        resultado->posicionEquilibrio = equilibrio;

        potencialInicial =
            -mision->constanteG * mision->masaTierra / radioInicial
            -mision->constanteG * mision->masaLuna /
                (mision->distancia - radioInicial);

        potencialEquilibrio =
            -mision->constanteG * mision->masaTierra / equilibrio
            -mision->constanteG * mision->masaLuna /
                (mision->distancia - equilibrio);

        resultado->cambioEnergiaPotencial =
            potencialEquilibrio - potencialInicial;
        resultado->trabajoPorKilogramo =
            resultado->cambioEnergiaPotencial
            - 0.5 * mision->velocidad * mision->velocidad;
        resultado->trabajoTotal =
            resultado->trabajoPorKilogramo * mision->masa;
    }
#else
    (void)mision;
    (void)resultado;
#endif
}

void mostrarReporte(void)
{
#if ETAPA == 1
    puts("\nTodavía no hay datos para mostrar.");

#elif ETAPA == 2
    if (!hayReporte) {
        puts("\nPrimero debe iniciar una misión.");
        return;
    }

    puts("\n--- DATOS REGISTRADOS ---");
    printf("Operador/a: %s\n", misionActual.nombre);
    printf("Masa de Orion: %.2f kg\n", misionActual.masa);
    printf("Velocidad TLI: %.2f m/s\n", misionActual.velocidad);
    printf("Altitud LEO: %.2f m\n", misionActual.altitud);
    printf("Distancia Tierra-Luna: %.2f m\n", misionActual.distancia);

#elif ETAPA >= 3
    if (!hayReporte) {
        puts("\nPrimero debe iniciar una misión.");
        return;
    }

    puts("\n--- REPORTE FISICO ---");
    printf("Operador/a: %s\n", misionActual.nombre);
    printf("Energía cinética inicial: %.6e J\n",
           resultadoActual.energiaCinetica);
    printf("Rapidez de escape ideal en LEO: %.2f m/s\n",
           resultadoActual.rapidezEscape);
    printf("Punto de equilibrio idealizado: %.2f km desde la Tierra\n",
           resultadoActual.posicionEquilibrio / 1000.0);
    printf("Cambio de energía potencial: %.6e J/kg\n",
           resultadoActual.cambioEnergiaPotencial);
    printf("Trabajo externo estimado: %.6e J/kg\n",
           resultadoActual.trabajoPorKilogramo);
    printf("Trabajo externo total estimado: %.6e J\n",
           resultadoActual.trabajoTotal);

    puts("\nCon los motores apagados, la inercia mantiene el movimiento.");
    puts("La gravedad cambia progresivamente la velocidad de Orion.");

#if ETAPA >= 4
    puts("El modelo supone una trayectoria radial simplificada.");
    puts("La ida requiere energía para alejarse del pozo gravitatorio terrestre;");
    puts("el regreso libera energía potencial al acercarse nuevamente a la Tierra.");
#endif
#endif
}
