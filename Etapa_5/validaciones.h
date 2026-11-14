#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <stddef.h>

int leerTexto(const char *mensaje, char *textoIngresado, size_t capacidad);
int leerNumeroReal(const char *mensaje, double minimo, double maximo,
                   double *numeroIngresado);
int leerNumeroEntero(const char *mensaje, int minimo, int maximo,
                     int *numeroIngresado);

#endif
