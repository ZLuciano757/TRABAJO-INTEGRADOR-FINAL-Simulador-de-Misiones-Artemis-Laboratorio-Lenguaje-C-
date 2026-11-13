#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <stddef.h>

void leerTexto(const char *mensaje, char *destino, size_t capacidad);
double leerReal(const char *mensaje, double minimo, double maximo);
int leerEntero(const char *mensaje, int minimo, int maximo);

#endif
