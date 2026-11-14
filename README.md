# TRABAJO-INTEGRADOR-FINAL-Simulador-de-Misiones-Artemis-Laboratorio-Lenguaje-C-
# 🚀 Simulador de Misiones Artemis - Escenario 3: Inyección Translunar (TLI)

**Trabajo Práctico Integrador Final** - Algoritmos y Estructuras de Datos / Laboratorio de C  
*Universidad Tecnológica Nacional - Facultad Regional Resistencia (UTN FRC)*

---

## 👥 Integrantes y Comisión
* **Integrante 1:** Fernández, Thiago - LU: 30165
* **Integrante 2:** Gatti Flekenstein, Luciano Emmanuel - LU: 30274
* **Integrante 3:** Hofstetter, Guadalupe - LU: 28117
* **Integrante 4:** Velázquez, Yeny Elisa - LU: 31056
* **Integrante 5:** Zamparo, Luciano Miqueas Gaspar - LU:29285
* **Comisión:** K 1.4

---

## 🎯 Descripción del Escenario Artemis Asignado (Escenario 3)
Este sistema simula la maniobra crítica de **Inyección Translunar (TLI)** y la consiguiente **Trayectoria de Retorno Libre (Free Return Trajectory)** de la nave Orion hacia la Luna.

El programa aborda los cálculos físicos y de simulación basados en:
1. **Primera Ley de Newton (Ley de Inercia):** Comportamiento del estado de movimiento de la nave tras apagar los propulsores y la desaceleración progresiva debida a la atracción gravitatoria terrestre.
2. **Energía Cinética y Mecánica:** Cálculo de la energía cinética inicial a partir de una velocidad de escape/inyección de 10.900,0  m/s y el principio de conservación de la energía mecánica para determinar el trabajo adicional requerido hasta el punto de equilibrio gravitatorio Tierra-Luna.
3. **Análisis Energético Comparativo:** Justificación de la diferencia de consumo de combustible entre el viaje de ida (Tierra-Luna) y el de regreso (Luna-Tierra).

---

## 🏗️ Arquitectura y Modularización del Proyecto
El proyecto se encuentra desarrollado íntegramente en lenguaje C y estructurado de forma modular a lo largo de 5 etapas progresivas para separar responsabilidades de manera limpia y robusta:

* **`main.c`:** Módulo principal que contiene el flujo de ejecución, menús interactivos por consola y la navegación entre las distintas etapas de la simulación.
* **`artemis.c` / `artemis.h`:** Módulo de lógica de negocio y gestión de estados específicos de la misión TLI.
* **`fisica.c` / `fisica.h`:** Módulo especializado en la resolución de fórmulas físicas, cinemáticas, gravitacionales y energéticas del escenario aeroespacial (incorporado a partir de las etapas avanzadas).
* **`validaciones.c` / `validaciones.h`:** Módulo de seguridad encargado de garantizar el ingreso correcto de datos por parte del usuario (control de tipos, rangos y prevención de bucles infinitos ante errores).
* **`Makefile`:** Automatizador de compilación para generar los binarios de manera limpia y rápida en entornos basados en Unix/Linux o MinGW.

---

## ⚙️ Instrucciones de Compilación y Ejecución

Para compilar y ejecutar el proyecto desde la terminal de comandos, sigue estos pasos:

1. Clonar o descargar el repositorio en tu equipo.
2. Ubicarte mediante la terminal en la carpeta de la etapa correspondiente (por ejemplo, `Etapa_5/`).
3. Ejecutar el comando de compilación mediante el Makefile:
   ```bash
   make
   ```
4. Ejecutar el simulador resultante:
   ```bash
   ./artemis
   ```
5. Para limpiar los archivos binarios compilados previamente:
   ```bash
   make clean
   ```

---

## 🤖 Registro de Uso de Inteligencia Artificial (IA)
En cumplimiento con la transparencia en el uso de herramientas de Inteligencia Artificial Generativa, se detallan a continuación las consultas realizadas y su validación:

* **Herramientas utilizadas:** Gemini / ChatGPT.
* **Tareas específicas y prompts:**
  * *Consulta conceptual:* "Explicar la aplicación del principio de conservación de la energía mecánica y el cálculo del trabajo adicional para el punto de equilibrio Tierra-Luna en C."
  * *Validación de código:* Análisis de paso de parámetros por punteros en las funciones de cálculo físico para optimizar el rendimiento y evitar copias innecesarias de estructuras.
  * *Depuración:* Resolución de advertencias del compilador GCC (`-Wall -Wextra`) relacionadas con tipos de datos `float` / `double` y validaciones de entrada en `validaciones.c`.
* **Validación humana:** El código generado fue revisado, adaptado a la arquitectura modular exigida y testeado para garantizar.
