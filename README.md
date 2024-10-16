# Proyecto: Algoritmo de Bellman-Ford y Generación de Tablas Visuales

Este proyecto usa el algoritmo de Bellman-Ford para encontrar la distancia más corta en un grafo dirigido, incluso si hay pesos negativos. También crea imágenes que muestran cómo se calcula la distancia y quiénes son los nodos anteriores en cada paso.

## Funcionalidad

El proyecto tiene dos partes principales:

1. **C++ (Algoritmo de Bellman-Ford)**: El programa en C++ representa un grafo y encuentra las distancias más cortas desde un nodo de origen a todos los demás nodos. También puede detectar ciclos negativos. Crea un archivo de imagen que muestra el grafo y guarda los resultados en archivos CSV.

2. **Python (Generación de Tablas Visuales)**: Un script en Python lee el archivo CSV generado por el programa en C++ y crea imágenes que muestran las distancias y los nodos anteriores en cada paso del algoritmo.

## ¿Cómo Funciona?

1. **Ejecutar el Programa en C++**:
   - Define y guarda los nodos y aristas del grafo.
   - Ejecuta el algoritmo de Bellman-Ford desde un nodo de origen, calculando y guardando las distancias mínimas y los nodos anteriores en un archivo CSV.
   - Genera una imagen del grafo en formato `.png` usando Graphviz.

2. **Ejecutar el Script en Python**:
   - Lee el archivo CSV y genera imágenes con tablas que muestran el estado de las distancias y los nodos anteriores en cada paso del algoritmo.

### Diagrama de Flujo del Proceso:

1. El usuario define el grafo y elige un nodo de origen en el programa C++.
2. El programa en C++ ejecuta Bellman-Ford, crea archivos CSV con los resultados y genera la imagen del grafo.
3. El script en Python lee cada archivo CSV y crea una imagen de tabla.

## Pasos para Ejecutar el Proyecto

### Requisitos Previos

- **C++**: Un compilador que soporte C++17 o superior.
- **Graphviz**: Debe estar instalado en tu sistema y accesible desde la línea de comandos.
- **Python 3**: Necesitas instalar `pandas` y `matplotlib`:
  ```bash
  pip install pandas matplotlib
  ```

### Paso 1: Compilar y Ejecutar el Código en C++

1. Compila el archivo `main.cpp`:
   El programa te pedirá el nodo de origen para ejecutar Bellman-Ford. Después de la ejecución, se generará:
   - Un archivo `.dot` y su imagen `.png` del grafo.
   - Archivos CSV que muestran la tabla de distancias y nodos anteriores en cada paso.
   - El archivo `main.cpp` ejecuta el script de Python para cada archivo CSV creado. El archivo `.py` genera imágenes de tablas con `pandas` y `matplotlib`.

## Consideraciones Importantes

- **Compatibilidad del Sistema Operativo**: Asegúrate de que el comando para abrir las imágenes (`system`) en el archivo C++ está configurado para tu sistema operativo.
- **Instalación de Graphviz**: Debes tener Graphviz instalado y accesible para convertir el archivo `.dot` en una imagen.
- **Directorio de Salida**: El script de Python creará un directorio de salida si no existe. Asegúrate de tener permisos para crear directorios en la ubicación donde ejecutas el script.

## Archivos del Proyecto

- **main.cpp**: Implementa el algoritmo de Bellman-Ford y genera archivos de resultados.
- **generar_tabla.py**: Lee los archivos CSV y genera imágenes con las tablas de distancias y nodos anteriores.
- **Imágenes y Archivos CSV**: Se crearán en el directorio donde se ejecute el código.

## Ejemplo de Uso

Al ejecutar el programa en C++, se generará un grafo como el siguiente:

```
A -> B (4)
A -> C (2)
B -> C (-1)
B -> D (2)
C -> E (3)
E -> B (-2)
```

Después de elegir el nodo de origen, el programa calculará las distancias más cortas y generará la imagen del grafo y las tablas de distancias.

--- 
