#include "artemis.h"
#include "validaciones.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

/* Conserva la ultima mision para poder consultar su reporte desde el menu. */
static Mision misionActual;
static Resultado resultadoActual;
static int hayMisionCalculada = 0;

/* Solicita los datos variables que se utilizan en los calculos del problema. */
static int pedirDatosMision(Mision *mision)
{
    if (!leerTexto("Nombre del operador/a: ", mision->nombreOperador,
                   sizeof mision->nombreOperador)) {
        return 0;
    }

    if (!leerNumeroReal("Masa de Orion en kg [1, 100000]: ",
                        1.0, 100000.0, &mision->masaOrion)) {
        return 0;
    }

    if (!leerNumeroReal("Velocidad TLI en m/s [1, 50000]: ",
                        1.0, 50000.0, &mision->velocidadTli)) {
        return 0;
    }

    if (!leerNumeroReal("Altitud LEO en m [1, 1000000]: ",
                        1.0, 1000000.0, &mision->altitudLeo)) {
        return 0;
    }

    if (!leerNumeroReal("Distancia Tierra-Luna en m [1e7, 1e9]: ",
                        1e7, 1e9, &mision->distanciaTierraLuna)) {
        return 0;
    }

    return 1;
}

/* Prepara las descripciones y el puntaje inicial de los tres eventos. */
static void prepararEventos(Mision *mision)
{
    strcpy(mision->eventos[0].descripcion,
           "La etapa ICPS se separa de Orion");
    strcpy(mision->eventos[1].descripcion,
           "Orion continua el viaje con los motores apagados");
    strcpy(mision->eventos[2].descripcion,
           "Orion se aproxima al punto de equilibrio gravitatorio");

    mision->eventos[0].alertaRegistrada = 0;
    mision->eventos[1].alertaRegistrada = 0;
    mision->eventos[2].alertaRegistrada = 0;
    mision->puntajeOperativo = 100;
}

/*
 * Recorre el arreglo de eventos y guarda la decision tomada por el usuario.
 * Cada alerta descuenta diez puntos del puntaje operativo.
 */
static int ejecutarEventos(Mision *mision)
{
    int indiceEvento;

    puts("\n------------- EVENTOS DE LA MISION -------------");

    for (indiceEvento = 0;
         indiceEvento < CANTIDAD_EVENTOS;
         indiceEvento++) {
        int decisionEvento;

        printf("\nEvento %d: %s\n", indiceEvento + 1,
               mision->eventos[indiceEvento].descripcion);
        puts("1. Registrar estado nominal");
        puts("2. Registrar una alerta");

        if (!leerNumeroEntero("Decision: ", 1, 2, &decisionEvento)) {
            return 0;
        }

        if (decisionEvento == 2) {
            mision->eventos[indiceEvento].alertaRegistrada = 1;
            mision->puntajeOperativo -= 10;
            puts("Alerta registrada. Se descuentan 10 puntos.");
        } else {
            puts("Estado nominal registrado.");
        }
    }

    return 1;
}

/*
 * Calcula las magnitudes energeticas solicitadas para la Inyeccion Translunar.
 * El potencial se calcula por unidad de masa para comparar el inicio del viaje
 * con el punto de equilibrio Tierra-Luna.
 */
static void calcularResultados(const Mision *mision, Resultado *resultado)
{
    double radioInicial;
    double distanciaInicialLuna;
    double raizMasaTierra;
    double raizMasaLuna;
    double potencialInicialPorKg;
    double potencialEquilibrioPorKg;
    double energiaCineticaPorKg;

    radioInicial = RADIO_TIERRA + mision->altitudLeo;
    distanciaInicialLuna = mision->distanciaTierraLuna - radioInicial;

    raizMasaTierra = sqrt(MASA_TIERRA);
    raizMasaLuna = sqrt(MASA_LUNA);

    resultado->posicionEquilibrio =
        mision->distanciaTierraLuna * raizMasaTierra /
        (raizMasaTierra + raizMasaLuna);

    resultado->energiaCineticaInicial =
        0.5 * mision->masaOrion * mision->velocidadTli *
        mision->velocidadTli;

    potencialInicialPorKg =
        -CONSTANTE_GRAVITACION * MASA_TIERRA / radioInicial
        -CONSTANTE_GRAVITACION * MASA_LUNA / distanciaInicialLuna;

    potencialEquilibrioPorKg =
        -CONSTANTE_GRAVITACION * MASA_TIERRA /
         resultado->posicionEquilibrio
        -CONSTANTE_GRAVITACION * MASA_LUNA /
         (mision->distanciaTierraLuna - resultado->posicionEquilibrio);

    resultado->cambioEnergiaPotencialPorKg =
        potencialEquilibrioPorKg - potencialInicialPorKg;

    energiaCineticaPorKg =
        0.5 * mision->velocidadTli * mision->velocidadTli;

    resultado->trabajoAdicionalPorKg =
        resultado->cambioEnergiaPotencialPorKg - energiaCineticaPorKg;

    /* Si la energia inicial es suficiente, el trabajo adicional minimo es cero. */
    if (resultado->trabajoAdicionalPorKg < 0.0) {
        resultado->trabajoAdicionalPorKg = 0.0;
    }

    resultado->trabajoAdicionalTotal =
        resultado->trabajoAdicionalPorKg * mision->masaOrion;
}

/* Muestra el titulo general del simulador. */
void mostrarTitulo(void)
{
    puts("\n============================================");
    puts("   ARTEMIS - SIMULADOR DE MISION TLI");
    puts("============================================");
}

/* Muestra las acciones disponibles para el usuario. */
void mostrarMenu(void)
{
    puts("\n1. Iniciar mision");
    puts("2. Ver ultimo reporte");
    puts("0. Salir");
}

/* Coordina la carga, los eventos, los calculos y el reporte de una mision. */
void ejecutarMision(void)
{
    Mision nuevaMision = {0};
    Resultado nuevoResultado = {0};

    puts("\nOrion se prepara para realizar la maniobra TLI.");

    if (!pedirDatosMision(&nuevaMision)) {
        puts("La carga de datos fue cancelada.");
        return;
    }

    prepararEventos(&nuevaMision);

    if (!ejecutarEventos(&nuevaMision)) {
        puts("La simulacion fue cancelada.");
        return;
    }

    calcularResultados(&nuevaMision, &nuevoResultado);

    misionActual = nuevaMision;
    resultadoActual = nuevoResultado;
    hayMisionCalculada = 1;

    puts("\nLa mision fue procesada correctamente.");
    mostrarReporte();
}

/* Presenta los datos, resultados y decisiones de la ultima mision. */
void mostrarReporte(void)
{
    int indiceEvento;

    if (!hayMisionCalculada) {
        puts("\nPrimero debe ejecutar una mision.");
        return;
    }

    puts("\n--------------- REPORTE DE MISION ---------------");
    printf("Operador/a: %s\n", misionActual.nombreOperador);
    printf("Masa de Orion: %.2f kg\n", misionActual.masaOrion);
    printf("Velocidad TLI: %.2f m/s\n", misionActual.velocidadTli);
    printf("Altitud LEO: %.2f m\n", misionActual.altitudLeo);
    printf("Distancia Tierra-Luna: %.2f m\n",
           misionActual.distanciaTierraLuna);

    puts("\nResultados fisicos:");
    printf("Energia cinetica inicial: %.6e J\n",
           resultadoActual.energiaCineticaInicial);
    printf("Punto de equilibrio: %.2f km desde el centro terrestre\n",
           resultadoActual.posicionEquilibrio / 1000.0);
    printf("Cambio de energia potencial: %.6e J/kg\n",
           resultadoActual.cambioEnergiaPotencialPorKg);
    printf("Trabajo adicional minimo: %.6e J/kg\n",
           resultadoActual.trabajoAdicionalPorKg);
    printf("Trabajo adicional total: %.6e J\n",
           resultadoActual.trabajoAdicionalTotal);

    printf("\nPuntaje operativo: %d/100\n",
           misionActual.puntajeOperativo);
    puts("Eventos registrados:");

    for (indiceEvento = 0;
         indiceEvento < CANTIDAD_EVENTOS;
         indiceEvento++) {
        printf("%d. %s: %s\n",
               indiceEvento + 1,
               misionActual.eventos[indiceEvento].descripcion,
               misionActual.eventos[indiceEvento].alertaRegistrada
                   ? "alerta"
                   : "estado nominal");
    }

    puts("\nInterpretacion:");
    puts("Con los motores apagados, Orion continua por inercia.");
    puts("La gravedad terrestre actua como fuerza externa y reduce");
    puts("progresivamente la velocidad mientras la nave se aleja.");
    puts("El viaje de ida necesita energia para salir del campo");
    puts("gravitatorio terrestre. En el regreso, la misma atraccion");
    puts("favorece el movimiento hacia la Tierra y reduce el impulso");
    puts("adicional que debe aportar la nave.");
}
