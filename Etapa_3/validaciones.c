#include "validaciones.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void leerTexto(const char*p,char*s,size_t n){for(;;){printf("%s",p);if(!fgets(s,(int)n,stdin)){clearerr(stdin);puts("Error de lectura.");continue;}if(!strchr(s,'\n')&&!feof(stdin)){int c;while((c=getchar())!='\n'&&c!=EOF){}puts("Texto demasiado largo.");continue;}s[strcspn(s,"\r\n")]=0;char*a=s;while(isspace((unsigned char)*a))a++;if(!*a){puts("El texto no puede estar vacío.");continue;}if(a!=s)memmove(s,a,strlen(a)+1);return;}}
double leerReal(const char*p,double min,double max){char s[128];for(;;){printf("%s",p);if(!fgets(s,sizeof s,stdin)){clearerr(stdin);continue;}char*e;errno=0;double x=strtod(s,&e);while(isspace((unsigned char)*e))e++;if(e==s||*e||errno==ERANGE||x!=x||x<min||x>max){printf("Ingrese un número entre %.3g y %.3g.\n",min,max);continue;}return x;}}
int leerEntero(const char*p,int min,int max){char s[64];for(;;){printf("%s",p);if(!fgets(s,sizeof s,stdin)){clearerr(stdin);continue;}char*e;errno=0;long x=strtol(s,&e,10);while(isspace((unsigned char)*e))e++;if(e==s||*e||errno==ERANGE||x<min||x>max){printf("Ingrese un entero entre %d y %d.\n",min,max);continue;}return(int)x;}}
