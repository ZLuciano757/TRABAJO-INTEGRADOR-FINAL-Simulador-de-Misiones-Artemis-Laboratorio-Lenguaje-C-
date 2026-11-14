#include "validaciones.h"

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Lee una linea completa y descarta los caracteres sobrantes cuando el texto
 * ingresado supera la capacidad disponible.
 */
static int leerLinea(const char *mensaje, char *lineaIngresada,
                     size_t capacidad)
{
    int caracterSobrante;

    printf("%s", mensaje);

    if (fgets(lineaIngresada, (int)capacidad, stdin) == NULL) {
        return 0;
    }

    if (strchr(lineaIngresada, '\n') == NULL && !feof(stdin)) {
        while ((caracterSobrante = getchar()) != '\n' &&
               caracterSobrante != EOF) {
            /* Solo se descartan los caracteres que no entraron en el arreglo. */
        }

        puts("La entrada es demasiado larga.");
        return -1;
    }

    lineaIngresada[strcspn(lineaIngresada, "\r\n")] = '\0';
    return 1;
}

/* Solicita un texto no vacio y lo guarda en el arreglo recibido. */
int leerTexto(const char *mensaje, char *textoIngresado, size_t capacidad)
{
    while (1) {
        int resultadoLectura;
        char *inicioTexto;
        char *finalTexto;

        resultadoLectura = leerLinea(mensaje, textoIngresado, capacidad);
        if (resultadoLectura == 0) {
            return 0;
        }
        if (resultadoLectura == -1) {
            continue;
        }

        inicioTexto = textoIngresado;
        while (isspace((unsigned char)*inicioTexto)) {
            inicioTexto++;
        }

        if (*inicioTexto == '\0') {
            puts("El texto no puede estar vacio.");
            continue;
        }

        if (inicioTexto != textoIngresado) {
            memmove(textoIngresado, inicioTexto, strlen(inicioTexto) + 1);
        }

        finalTexto = textoIngresado + strlen(textoIngresado) - 1;
        while (finalTexto > textoIngresado &&
               isspace((unsigned char)*finalTexto)) {
            *finalTexto = '\0';
            finalTexto--;
        }

        return 1;
    }
}

/*
 * Solicita un numero real dentro de un rango. Acepta punto o coma como
 * separador decimal y vuelve a pedir el dato cuando la entrada es incorrecta.
 */
int leerNumeroReal(const char *mensaje, double minimo, double maximo,
                   double *numeroIngresado)
{
    char lineaIngresada[128];

    while (1) {
        int resultadoLectura;
        char *finConversion;
        double numeroConvertido;
        size_t indiceCaracter;

        resultadoLectura =
            leerLinea(mensaje, lineaIngresada, sizeof lineaIngresada);
        if (resultadoLectura == 0) {
            return 0;
        }
        if (resultadoLectura == -1) {
            continue;
        }

        for (indiceCaracter = 0;
             lineaIngresada[indiceCaracter] != '\0';
             indiceCaracter++) {
            if (lineaIngresada[indiceCaracter] == ',') {
                lineaIngresada[indiceCaracter] = '.';
            }
        }

        errno = 0;
        numeroConvertido = strtod(lineaIngresada, &finConversion);

        while (isspace((unsigned char)*finConversion)) {
            finConversion++;
        }

        if (finConversion == lineaIngresada || *finConversion != '\0' ||
            errno == ERANGE || !isfinite(numeroConvertido) ||
            numeroConvertido < minimo || numeroConvertido > maximo) {
            printf("Ingrese un numero entre %.3g y %.3g.\n", minimo, maximo);
            continue;
        }

        *numeroIngresado = numeroConvertido;
        return 1;
    }
}

/* Solicita un numero entero dentro del rango indicado. */
int leerNumeroEntero(const char *mensaje, int minimo, int maximo,
                     int *numeroIngresado)
{
    char lineaIngresada[64];

    while (1) {
        int resultadoLectura;
        char *finConversion;
        long numeroConvertido;

        resultadoLectura =
            leerLinea(mensaje, lineaIngresada, sizeof lineaIngresada);
        if (resultadoLectura == 0) {
            return 0;
        }
        if (resultadoLectura == -1) {
            continue;
        }

        errno = 0;
        numeroConvertido = strtol(lineaIngresada, &finConversion, 10);

        while (isspace((unsigned char)*finConversion)) {
            finConversion++;
        }

        if (finConversion == lineaIngresada || *finConversion != '\0' ||
            errno == ERANGE || numeroConvertido < minimo ||
            numeroConvertido > maximo) {
            printf("Ingrese un entero entre %d y %d.\n", minimo, maximo);
            continue;
        }

        *numeroIngresado = (int)numeroConvertido;
        return 1;
    }
}
