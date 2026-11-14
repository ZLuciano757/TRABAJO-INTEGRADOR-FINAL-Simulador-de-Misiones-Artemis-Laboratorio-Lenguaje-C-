#include "artemis.h"
#include "validaciones.h"
#include <stdio.h>
int main(void){mostrarTitulo();int op;do{mostrarMenu();
#if ETAPA >= 2
op=leerEntero("Opción: ",0,2);
#else
op=leerEntero("Opción: ",0,1);
#endif
if(op==1)ejecutarMision();
#if ETAPA >= 2
else if(op==2)mostrarReporte();
#endif
}while(op!=0);puts("Simulación finalizada. ¡Buen viaje, Orion!");return 0;}
