import pandas as pd  # Importa pandas para manipulación de datos
import matplotlib.pyplot as plt  # Importa matplotlib para graficar
import sys  # Importa sys para manejo de argumentos del sistema
import os  # Importa os para operaciones de archivos y directorios


def generar_tabla_imagen(csv_fl, output_img):
    try:
        # Leer el archivo CSV
        df = pd.read_csv(csv_fl)  # Lee el archivo CSV en un DataFrame de pandas
    except FileNotFoundError:
        print(f"Error: El archivo '{csv_fl}' no se encontró.")  # Error si no se encuentra el archivo
        return
    except pd.errors.EmptyDataError:
        print("Error: El archivo CSV está vacío.")  # Error si el archivo está vacío
        return
    except Exception as e:
        print(f"Error al leer el archivo CSV: {e}")  # Otros posibles errores al leer el CSV
        return

    # Crear la figura y el eje
    fig, ax = plt.subplots()  # Crea una figura y un eje para el gráfico

    # Ocultar el marco del gráfico
    ax.xaxis.set_visible(False)  # Oculta el eje X
    ax.yaxis.set_visible(False)  # Oculta el eje Y
    ax.set_frame_on(False)  # Quita el marco alrededor de la gráfica

    # Dibujar la tabla
    tabla = ax.table(cellText=df.values, colLabels=df.columns, cellLoc='center', loc='center')
    # Crea una tabla centrada con los datos y encabezados del DataFrame

    # Ajustar el tamaño de las celdas y el estilo
    font_size = 12  # Define el tamaño de la fuente para la tabla

    # Calcular el ancho de las columnas automáticamente
    column_widths = []  # Lista para almacenar el ancho de cada columna
    for col in df.columns:
        max_length = max(df[col].astype(str).map(len).max(),
                         len(col))  # Encuentra el valor máximo de longitud en cada columna
        column_widths.append(
            max_length * 0.15)  # Ajusta el ancho de columna basado en la longitud y un factor de escala

    # Calcular el alto de las filas
    cell_height = 0.7  # Define un valor estándar para la altura de las celdas

    # Establecer bordes y estilo de celdas
    for key, cell in tabla.get_celld().items():
        cell.set_edgecolor('black')  # Establece bordes negros para las celdas
        cell.set_fontsize(font_size)  # Aplica el tamaño de fuente
        cell.set_text_props(ha='center', va='center')  # Centra el texto en cada celda

    # Calcular el tamaño de la figura
    fig_width = sum(column_widths)  # Suma los anchos de las columnas para el ancho total
    fig_height = cell_height * (len(df) + 1)  # Multiplica el alto de celda por el número de filas + 1 (encabezado)

    fig.set_size_inches(fig_width, fig_height)  # Ajusta el tamaño de la figura

    # Ajustar los márgenes automáticamente
    margin_factor = 0.1  # Define un margen base
    plt.subplots_adjust(
        top=1 - margin_factor,
        bottom=margin_factor,
        left=margin_factor,
        right=1 - margin_factor
    )  # Ajusta los márgenes de la figura

    # Guardar la imagen en la ubicación especificada
    output_dir = os.path.dirname(output_img)  # Obtiene el directorio de salida de la ruta
    if not os.path.exists(output_dir) and output_dir != '':  # Verifica si el directorio existe
        os.makedirs(output_dir)  # Crea el directorio si no existe

    plt.savefig(output_img, bbox_inches='tight')  # Guarda la figura como imagen con ajuste de bordes
    plt.close()  # Cierra la figura para liberar memoria


# Bloque principal del script
if __name__ == "__main__":
    if len(sys.argv) != 3:  # Verifica si se pasaron correctamente 2 argumentos al script
        print("Uso: python generar_tabla.py <archivo_csv> <imagen_salida>")
        sys.exit(1)  # Termina el script si los argumentos no son correctos

    csv_file = sys.argv[1]  # Toma el nombre del archivo CSV de los argumentos
    output_image = sys.argv[2]  # Toma el nombre del archivo de salida de los argumentos
    generar_tabla_imagen(csv_file, output_image)  # Llama a la función para generar la imagen de la tabla
