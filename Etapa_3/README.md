# Artemis: Inyección Translunar (Situación 3)

Simulador de consola en C para la maniobra TLI, la inercia con motores apagados y un análisis energético simplificado.

## Integrantes y comisión
- Integrantes: completar (equipo de 3 a 5).
- Comisión: completar.

## Escenario
La etapa ICPS impulsa Orion hasta velocidad TLI y se desacopla. Con motores apagados, Orion conserva el movimiento por inercia mientras la gravedad terrestre altera su rapidez. Se ingresan masa, rapidez, altitud y distancia Tierra-Luna; etapa 4 suma constantes editables y tres eventos operativos.

La consigna indica masa 26.000 kg, velocidad 10.900 m/s, distancia Tierra-Luna 384.000 km y altitud LEO 192 km. No da las masas celestes ni G para esta situación; el programa usa G=6,67430e-11, MT=5,972e24 kg y ML=7,342e22 kg.

## Modelo y supuestos
Punto de equilibrio colineal: x=D*sqrt(MT)/(sqrt(MT)+sqrt(ML)). Energía potencial por unidad de masa: U/m=-G*MT/rT-G*ML/rL. Trabajo externo por unidad de masa: Wext/m=(Ufinal-Uinicial)-Ki/m, suponiendo llegada momentánea en reposo al punto de equilibrio. Radio inicial: radio terrestre medio (6371 km) más altitud LEO. Modelo didáctico radial de dos cuerpos; no integra trayectoria real ni incorpora velocidad tangencial orbital, movimiento Tierra-Luna, rotación, Sol o navegación. Wext negativo indica ausencia de aporte externo positivo bajo estos supuestos.

## Archivos y compilación
main.c contiene menú y navegación. artemis.h/.c reúnen estructuras, constantes, simulación y cálculos. validaciones.h/.c valida entradas. Makefile compila con GCC y enlaza libm. Ejecutar make y luego ./artemis (Windows MinGW: mingw32-make y .\artemis.exe); make clean elimina objetos.

Cada carpeta es un snapshot completo. ETAPA en artemis.h activa el avance incluido (1 a 4). Para historial progresivo, copiar Etapa_1 a un repositorio Git, hacer commit; reemplazar con los archivos de Etapa_2, Etapa_3 y Etapa_4 y hacer un commit en cada paso.

Commits sugeridos:
1. feat: crear menú y estructura modular
2. feat: agregar entradas validadas y datos de misión
3. feat: calcular energías de trayectoria translunar
4. feat: añadir eventos interactivos y reporte final

Distribuyan aportes y commits reales entre integrantes; no atribuyan commits falsamente.

## Registro de uso de IA (revisar y completar)
- Herramienta: ChatGPT.
- Uso: organizar la consigna en etapas, proponer arquitectura C, primer borrador de código y documentar hipótesis físicas.
- Consulta: solicitud de resolver el PDF con situación 3 en cuatro partes incrementales, cada una con código completo, para GitHub y commits.
- Adaptación y validación: el equipo debe compilar con GCC, comprobar manualmente fórmulas y resultados, probar entradas normales e inválidas y completar qué cambió. Reemplacen esta sección por un registro fiel del trabajo real.

## Mejoras futuras
Integrar numéricamente la trayectoria con condiciones orbitales y paso temporal, guardar varias misiones en un arreglo y resumir estadísticas.
