#include "artemis.h"
#include "validaciones.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
static Mision actual; static Resultado resultado; static int hayResultado=0;
void mostrarTitulo(void){puts("\nARTEMIS | SIMULADOR DE INYECCION TRANSLUNAR (TLI)");}
void mostrarMenu(void){puts("\n1. Iniciar misión");
#if ETAPA >= 2
puts("2. Ver reporte");
#endif
puts("0. Salir");}
void ejecutarMision(void){
#if ETAPA == 1
puts("\nOrion se prepara para TLI. Próxima etapa: entradas de misión.");
#elif ETAPA == 2
memset(&actual,0,sizeof actual);leerTexto("\nOperador/a: ",actual.nombre,sizeof actual.nombre);
actual.masa=leerReal("Masa Orion (kg, 1 a 100000): ",1,100000);actual.velocidad=leerReal("Velocidad TLI (m/s, 1 a 50000): ",1,50000);
actual.altitud=leerReal("Altitud LEO (m, 1 a 1000000): ",1,1000000);actual.distancia=leerReal("Distancia Tierra-Luna (m, 1e6 a 1e9): ",1e6,1e9);
puts("\nCon motores apagados, Orion continúa por inercia; la gravedad modifica su movimiento. Cálculos en etapa 3.");
#elif ETAPA >= 3
memset(&actual,0,sizeof actual);leerTexto("\nOperador/a: ",actual.nombre,sizeof actual.nombre);
actual.masa=leerReal("Masa Orion (kg, 1 a 100000): ",1,100000);actual.velocidad=leerReal("Velocidad TLI (m/s, 1 a 50000): ",1,50000);
actual.altitud=leerReal("Altitud LEO (m, 1 a 1000000): ",1,1000000);actual.distancia=leerReal("Distancia Tierra-Luna (m, 1e6 a 1e9): ",1e6,1e9);
actual.g=G;actual.tierra=MT;actual.luna=ML;
#if ETAPA >= 4
puts("\nConstantes estándar cargadas; puede ajustarlas:");
actual.g=leerReal("G (1e-12 a 1e-9): ",1e-12,1e-9);actual.tierra=leerReal("Masa Tierra (kg, 1e23 a 1e25): ",1e23,1e25);actual.luna=leerReal("Masa Luna (kg, 1e21 a 1e23): ",1e21,1e23);
const char*eventos[]={"TLI ejecutada; ICPS desacoplada.","Crucero translunar; motores apagados.","Punto de equilibrio idealizado."};int puntos=100;
puts("\n--- SIMULACION POR EVENTOS ---");for(int i=0;i<3;i++){printf("\nEvento %d/3: %s\n1. Monitoreo nominal\n2. Registrar alerta y continuar\n",i+1,eventos[i]);if(leerEntero("Decisión: ",1,2)==2){puntos-=10;puts("Alerta registrada (-10 puntos).");}else puts("Telemetría nominal registrada.");}printf("Misión completada. Puntaje: %d/100.\n",puntos);
#endif
calcularResultado(&actual,&resultado);hayResultado=1;puts("\n--- REPORTE FISICO ---");mostrarReporte();
#endif
}
void calcularResultado(const Mision*m,Resultado*r){if(!m||!r)return;
#if ETAPA >= 3
double r0=RT+m->altitud;double x=m->distancia*sqrt(m->tierra)/(sqrt(m->tierra)+sqrt(m->luna));r->energiaK=.5*m->masa*m->velocidad*m->velocidad;r->escape=sqrt(2*m->g*m->tierra/r0);r->xEquilibrio=x;
double u0=-m->g*m->tierra/r0-m->g*m->luna/(m->distancia-r0),uf=-m->g*m->tierra/x-m->g*m->luna/(m->distancia-x);r->deltaU=uf-u0;r->trabajoKg=r->deltaU-.5*m->velocidad*m->velocidad;r->trabajoTotal=r->trabajoKg*m->masa;
#else
(void)m;(void)r;
#endif
}
void mostrarReporte(void){
#if ETAPA < 3
puts("El reporte energético se incorpora en etapa 3.");
#else
if(!hayResultado){puts("Primero ejecute una misión.");return;}printf("Operador/a: %s\nKi = %.3e J\nRapidez de escape ideal en LEO = %.2f m/s\n",actual.nombre,resultado.energiaK,resultado.escape);
printf("Equilibrio idealizado: %.2f km desde centro terrestre\nCambio de energía potencial = %.3e J/kg\nTrabajo externo adicional = %.3e J/kg; total = %.3e J\n",resultado.xEquilibrio/1000,resultado.deltaU,resultado.trabajoKg,resultado.trabajoTotal);
puts("Con motores apagados, la inercia mantiene el movimiento y la gravedad cambia progresivamente la velocidad."); puts("La ida exige energía para alejarse del pozo gravitatorio terrestre; al regresar,"); puts("la caída hacia la Tierra libera energía potencial. El consumo real depende de la trayectoria.");
#endif
}

