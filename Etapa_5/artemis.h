#ifndef ARTEMIS_H
#define ARTEMIS_H

/* Permite identificar esta carpeta como la quinta etapa del proyecto. */
#ifndef ETAPA
#define ETAPA 5
#endif

/* Constantes fisicas utilizadas en el problema 3. */
#define CONSTANTE_GRAVITACION 6.67430e-11
#define MASA_TIERRA 5.972e24
#define MASA_LUNA 7.342e22
#define RADIO_TIERRA 6371000.0

#define CANTIDAD_EVENTOS 3

/* Guarda una decision tomada durante un evento de la mision. */
typedef struct {
    char descripcion[80];
    int alertaRegistrada;
} Evento;

/* Reune los datos ingresados y el estado general de la mision. */
typedef struct {
    char nombreOperador[64];
    double masaOrion;
    double velocidadTli;
    double altitudLeo;
    double distanciaTierraLuna;
    Evento eventos[CANTIDAD_EVENTOS];
    int puntajeOperativo;
} Mision;

/* Guarda los resultados pedidos para el problema de Inyeccion Translunar. */
typedef struct {
    double energiaCineticaInicial;
    double posicionEquilibrio;
    double cambioEnergiaPotencialPorKg;
    double trabajoAdicionalPorKg;
    double trabajoAdicionalTotal;
} Resultado;

void mostrarTitulo(void);
void mostrarMenu(void);
void ejecutarMision(void);
void mostrarReporte(void);

#endif
