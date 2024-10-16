# Proyecto: Algoritmo de Bellman-Ford y Generación de Tablas Visuales

Este proyecto implementa el algoritmo de Bellman-Ford para calcular la distancia más corta en un grafo dirigido con la posibilidad de manejar pesos negativos. Además, se genera una representación visual del grafo y del proceso de cálculo en forma de imágenes que muestran el estado de la tabla de distancias y predecesores en cada iteración.

## Funcionalidad

El proyecto consta de dos componentes principales:

1. **C++ (Algoritmo de Bellman-Ford)**: El programa en C++ representa un grafo dirigido y permite calcular las distancias más cortas desde un nodo de origen a todos los demás nodos, detectando ciclos negativos. Se genera un archivo de imagen que representa visualmente el grafo y se guardan los resultados del cálculo en archivos CSV.

2. **Python (Generación de Tablas Visuales)**: Un script en Python lee el archivo CSV generado por el programa en C++ y crea imágenes que muestran una tabla con las distancias y predecesores en cada iteración del algoritmo.

## ¿Cómo Funciona?

1. **Ejecución del Programa en C++**:
   - Define y almacena los nodos y aristas del grafo.
   - Ejecuta el algoritmo de Bellman-Ford a partir de un nodo de origen, calculando y almacenando las distancias mínimas y predecesores de cada nodo en un archivo CSV.
   - Genera una imagen del grafo en formato `.png` utilizando Graphviz.

2. **Ejecución del Script en Python**:
   - Lee el archivo CSV y genera imágenes con tablas que muestran el estado de las distancias y los predecesores en cada iteración del algoritmo de Bellman-Ford.

### Diagrama de Flujo del Proceso:

1. El usuario define el grafo y elige un nodo de origen en el programa C++.
2. El programa en C++ ejecuta Bellman-Ford, crea archivos CSV con los resultados y genera la imagen del grafo.
3. El script en Python lee cada archivo CSV y crea una imagen de tabla.

## Pasos para Ejecutar el Proyecto

### Requisitos Previos

- **C++**: Un compilador compatible con C++17 o superior.
- **Graphviz**: Para generar la imagen del grafo, debe estar instalado en el sistema y accesible en la línea de comandos.
- **Python 3**: Asegúrate de tener instalados `pandas` y `matplotlib`:
  ```bash
  pip install pandas matplotlib
  ```

### Paso 1: Compilar y Ejecutar el Código en C++

1. Compila el archivo `main.cpp`:
   ```bash
   g++ main.cpp -o bellmanford
   ```
2. Ejecuta el programa:
   ```bash
   ./bellmanford
   ```
   El programa pedirá el nodo de origen para ejecutar Bellman-Ford. Tras la ejecución, se generará:
   - Un archivo `.dot` y su correspondiente imagen `.png` con el grafo.
   - Archivos CSV con el estado de la tabla de distancias y predecesores en cada iteración.

### Paso 2: Generar Imágenes de Tablas con Python

1. Ejecuta el script de Python para cada archivo CSV generado. El formato de uso es:
   ```bash
   python generar_tabla.py <archivo_csv> <imagen_salida>
   ```
   Ejemplo:
   ```bash
   python generar_tabla.py tabla.csv tabla_paso_1.png
   ```

### Nota:

Si deseas automatizar la generación de imágenes, puedes crear un script de shell o batch que recorra los archivos CSV y ejecute el comando anterior para cada archivo.

## Consideraciones Importantes

- **Compatibilidad del Sistema Operativo**: Asegúrate de que el comando para abrir las imágenes (`system`) en el archivo C++ está correctamente configurado según tu sistema operativo (`Windows`, `MacOS`, o `Linux`).
- **Instalación de Graphviz**: Es imprescindible tener Graphviz instalado y accesible para que el archivo `.dot` se convierta en una imagen.
- **Directorio de Salida**: El script de Python creará el directorio de salida si no existe. Asegúrate de tener permisos para crear directorios en la ubicación donde ejecutas el script.

## Archivos del Proyecto

- **main.cpp**: Implementa el algoritmo de Bellman-Ford y genera archivos de resultados.
- **generar_tabla.py**: Lee los archivos CSV y genera imágenes con las tablas de distancias y predecesores.
- **Imagenes y Archivos CSV**: Se generarán en el directorio donde se ejecute el código.

## Ejemplo de Uso

Al ejecutar el programa C++, se generará un grafo como el siguiente:

```
A -> B (4)
A -> C (2)
B -> C (-1)
B -> D (2)
C -> E (3)
E -> B (-2)
```

Tras elegir el nodo de origen, el programa calculará las distancias mínimas y generará la representación visual del grafo y las tablas de distancias.

---

Este README te da una visión general de cómo trabajar con el proyecto y los pasos para su ejecución. ¡Disfruta explorando el algoritmo de Bellman-Ford!
