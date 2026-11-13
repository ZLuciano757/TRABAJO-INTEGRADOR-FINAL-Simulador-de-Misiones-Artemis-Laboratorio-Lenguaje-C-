#ifndef ARTEMIS_H
#define ARTEMIS_H
#define ETAPA 1
#define G 6.67430e-11
#define MT 5.972e24
#define ML 7.342e22
#define D_LUNA 384000000.0
#define RT 6371000.0

typedef struct { 
    char nombre[64];
    double masa,velocidad,altitud,distancia,g,tierra,luna;
} Mision;

typedef struct {
    double energiaK,escape,xEquilibrio,deltaU,trabajoKg,trabajoTotal;
} Resultado;

void mostrarTitulo(void);

void mostrarMenu(void);

void ejecutarMision(void);

void mostrarReporte(void);

void calcularResultado(const Mision *,Resultado *);

#endif
