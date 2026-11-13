#include "validaciones.h"

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void limpiarRestoDeLinea(void)
{
    int caracter;

    while ((caracter = getchar()) != '\n' && caracter != EOF) {
        /* Descarta caracteres que exceden el tamaño del búfer. */
    }
}

void leerTexto(const char *mensaje, char *destino, size_t capacidad)
{
    for (;;) {
        char *inicio;
        size_t largo;

        printf("%s", mensaje);

        if (fgets(destino, (int)capacidad, stdin) == NULL) {
            clearerr(stdin);
            puts("No se pudo leer el texto. Intente nuevamente.");
            continue;
        }

        if (strchr(destino, '\n') == NULL && !feof(stdin)) {
            limpiarRestoDeLinea();
            puts("El texto es demasiado largo. Intente nuevamente.");
            continue;
        }

        destino[strcspn(destino, "\r\n")] = '\0';

        inicio = destino;
        while (isspace((unsigned char)*inicio)) {
            inicio++;
        }

        largo = strlen(inicio);
        while (largo > 0 && isspace((unsigned char)inicio[largo - 1])) {
            inicio[--largo] = '\0';
        }

        if (largo == 0) {
            puts("El texto no puede quedar vacío.");
            continue;
        }

        if (inicio != destino) {
            memmove(destino, inicio, largo + 1);
        }
        return;
    }
}

double leerReal(const char *mensaje, double minimo, double maximo)
{
    char linea[128];

    for (;;) {
        char *fin;
        double valor;

        printf("%s", mensaje);

        if (fgets(linea, sizeof linea, stdin) == NULL) {
            clearerr(stdin);
            puts("No se pudo leer el número. Intente nuevamente.");
            continue;
        }

        if (strchr(linea, '\n') == NULL && !feof(stdin)) {
            limpiarRestoDeLinea();
            puts("La entrada es demasiado larga. Intente nuevamente.");
            continue;
        }

        errno = 0;
        valor = strtod(linea, &fin);

        while (isspace((unsigned char)*fin)) {
            fin++;
        }

        if (fin == linea || *fin != '\0' || errno == ERANGE ||
            !isfinite(valor) || valor < minimo || valor > maximo) {
            printf("Ingrese un número válido entre %.3g y %.3g.\n",
                   minimo, maximo);
            continue;
        }

        return valor;
    }
}

int leerEntero(const char *mensaje, int minimo, int maximo)
{
    char linea[64];

    for (;;) {
        char *fin;
        long valor;

        printf("%s", mensaje);

        if (fgets(linea, sizeof linea, stdin) == NULL) {
            clearerr(stdin);
            puts("No se pudo leer la opción. Intente nuevamente.");
            continue;
        }

        if (strchr(linea, '\n') == NULL && !feof(stdin)) {
            limpiarRestoDeLinea();
            puts("La entrada es demasiado larga. Intente nuevamente.");
            continue;
        }

        errno = 0;
        valor = strtol(linea, &fin, 10);

        while (isspace((unsigned char)*fin)) {
            fin++;
        }

        if (fin == linea || *fin != '\0' || errno == ERANGE ||
            valor < minimo || valor > maximo) {
            printf("Ingrese un entero entre %d y %d.\n", minimo, maximo);
            continue;
        }

        return (int)valor;
    }
}
