#ifndef ARTEMIS_H
#define ARTEMIS_H

#define ETAPA 2

#define G 6.67430e-11
#define MASA_TIERRA 5.972e24
#define MASA_LUNA 7.342e22
#define DISTANCIA_LUNA 384000000.0
#define RADIO_TIERRA 6371000.0

typedef struct {
    char nombre[64];
    double masa;
    double velocidad;
    double altitud;
    double distancia;
    double constanteG;
    double masaTierra;
    double masaLuna;
} Mision;

typedef struct {
    double energiaCinetica;
    double rapidezEscape;
    double posicionEquilibrio;
    double cambioEnergiaPotencial;
    double trabajoPorKilogramo;
    double trabajoTotal;
} Resultado;

void mostrarTitulo(void);
void mostrarMenu(void);
void ejecutarMision(void);
void mostrarReporte(void);
void calcularResultado(const Mision *mision, Resultado *resultado);

#endif
