#include <iostream> // Biblioteca para operaciones de entrada y salida
#include <vector>   // Biblioteca para usar vectores
#include <fstream>  // Biblioteca para trabajar con archivos
#include <climits> // Biblioteca para usar valores de límites, como INT_MAX
#include <set>      // Biblioteca para usar conjuntos, aunque no se utiliza aquí
#include <filesystem> // Biblioteca para manejar rutas y archivos en el sistema

#ifdef _WIN32
#include <windows.h> // Solo para Windows, usado para configurar la consola UTF-8
#endif

using namespace std; // Para evitar usar std:: antes de cada operación estándar
namespace fs = std::filesystem; // Alias para usar filesystem

#define INF INT_MAX // Define el valor de infinito como el máximo de un int

// Estructura para representar un borde en el grafo
struct Edge {
    int origen, destino, peso; // Origen y destino de un borde, y su peso
};

// Clase para representar el grafo
class Graph {
private:
    vector<Edge> edges; // Vector de bordes del grafo
    int V, E; // Numero de vertices y bordes
    fs::path rutaDot; // Ruta para el archivo .dot del grafo
    fs::path rutaGrafo; // Ruta para la imagen del grafo
    fs::path rutaCSV; // Ruta para el archivo CSV de resultados
    fs::path rutaImagenTabla; // Ruta base para las imagenes generadas de la tabla
    fs::path rutaScriptPython; // Ruta para el script Python que genera las imagenes

    // Convierte una letra en un numero de vertice, 'A' se convierte en 1, 'B' en 2, etc.
    [[nodiscard]] static int letraAVertice(char letra) {
        return letra - 'A' + 1;
    }

    // Convierte un numero de vertice en una letra, 1 se convierte en 'A', 2 en 'B', etc.
    [[nodiscard]] static char verticeALetra(int vertice) {
        return 'A' + vertice - 1;
    }

public:
    // Constructor que inicializa los valores y rutas del grafo
    Graph(int vertices, int edgesCount)
            : V(vertices), E(edgesCount),
              rutaDot(fs::current_path() / "grafo.dot"),
              rutaGrafo(fs::current_path() / "grafo.png"),
              rutaCSV(fs::current_path() / "tabla.csv"),
              rutaImagenTabla(fs::current_path() / "tabla_paso_"),
              rutaScriptPython(fs::current_path().parent_path() / "generar_tabla.py") {
        edges.reserve(E); // Reserva espacio para los bordes en el vector
    }

    // Metodo para agregar un borde al grafo usando letras para los vertices
    void addEdge(char origenLetra, char destinoLetra, int peso) {
        int origen = letraAVertice(origenLetra); // Convierte origen a numero
        int destino = letraAVertice(destinoLetra); // Convierte destino a numero
        edges.push_back({origen, destino, peso}); // Agrega el borde al vector
    }

    // Metodo para exportar el grafo a un archivo .dot y generar la imagen del grafo
    void exportarGrafo() const {
        ofstream archivo(rutaDot); // Abre archivo para escribir el grafo en formato .dot
        if (!archivo) { // Verifica si se pudo abrir el archivo
            cerr << "Error al crear el archivo dot." << endl;
            return;
        }

        archivo << "digraph G {\n"; // Escribe encabezado del archivo .dot
        for (const auto &edge : edges) { // Itera sobre todos los bordes
            archivo << verticeALetra(edge.origen) << " -> " << verticeALetra(edge.destino)
                    << " [label=\"" << edge.peso << "\"];\n"; // Agrega borde al archivo
        }
        archivo << "}\n"; // Cierra el grafo en el archivo .dot
        archivo.close(); // Cierra el archivo

        // Comando para generar la imagen usando Graphviz
        const string cmd = "dot -Tpng \"" + rutaDot.string() + "\" -o \"" + rutaGrafo.string() + "\"";
        if (system(cmd.c_str()) != 0) { // Ejecuta el comando y verifica errores
            cerr << "Error al generar la imagen del grafo." << endl;
            return;
        }

        // Muestra la imagen generada dependiendo del sistema operativo
        if (fs::exists(rutaGrafo)) {
            cout << "Imagen del grafo generada en: " << rutaGrafo << endl;
#ifdef _WIN32
            system((R"(start "" ")" + rutaGrafo.string() + "\"").c_str());
#elif __APPLE__
            system(("open \"" + rutaGrafo.string() + "\"").c_str());
#else
            system(("xdg-open \"" + rutaGrafo.string() + "\"").c_str());
#endif
        } else {
            cout << "Error: la imagen del grafo no se pudo generar." << endl;
        }
    }

    // Exporta el estado de las distancias y predecesores a un archivo CSV e imagen
    void exportarTablaImagen(const vector<int> &dist, const vector<int> &pred, int paso) const {
        ofstream archivo(rutaCSV); // Abre archivo CSV para escribir
        if (!archivo) { // Verifica si se pudo abrir el archivo
            cerr << "Error al crear el archivo CSV." << endl;
            return;
        }

        archivo << "Vertice,Distancia,Predecesor\n"; // Encabezado del CSV
        for (int i = 1; i <= V; ++i) { // Itera sobre los vertices
            archivo << verticeALetra(i) << ",";
            if (dist[i] == INF) { // Si la distancia es infinita
                archivo << "INF,-\n";
            } else { // Si tiene una distancia definida
                archivo << dist[i] << ",";
                archivo << (pred[i] == -1 ? "-" : string(1, verticeALetra(pred[i]))) << "\n";
            }
        }
        archivo.close(); // Cierra el archivo CSV

        // Comando para ejecutar el script Python que genera la imagen de la tabla
        const string rutaImagen = (rutaImagenTabla.string() + to_string(paso) + ".png");
        const string cmd = "python \"" + rutaScriptPython.string() + "\" \"" + rutaCSV.string() + "\" \"" + rutaImagen + "\"";
        if (system(cmd.c_str()) != 0) { // Ejecuta el comando y verifica errores
            cerr << "Error al generar la imagen de la tabla." << endl;
            return;
        }

#ifdef _WIN32
        system((R"(start "" ")" + rutaImagen + "\"").c_str()); // Abre la imagen en Windows
#elif __APPLE__
        system(("open \"" + rutaImagen + "\"").c_str()); // Abre la imagen en Mac
#else
        system(("xdg-open \"" + rutaImagen + "\"").c_str()); // Abre la imagen en Linux
#endif
    }

    // Detecta ciclos negativos y los marca en la distancia como -INF
    void detectarYMarcarCiclosNegativos(vector<int> &dist) {
        for (const auto& edge : edges) { // Itera sobre todos los bordes
            int u = edge.origen;
            int v = edge.destino;
            int peso = edge.peso;

            // Si se puede relajar mas, hay ciclo negativo
            if (dist[u] != INF && dist[u] + peso < dist[v]) {
                dist[v] = -INF; // Marca la distancia como ciclo negativo
            }
        }
    }

    // Algoritmo de Bellman-Ford para calcular la distancia mas corta desde el origen
    void bellmanFord(char origenLetra) {
        int origen = letraAVertice(origenLetra); // Convierte el origen a numero
        vector<int> dist(V + 1, INF); // Inicializa todas las distancias a infinito
        vector<int> pred(V + 1, -1); // Inicializa predecesores a -1 (sin predecesor)
        dist[origen] = 0; // La distancia al origen es cero

        for (int i = 1; i <= V - 1; ++i) { // Itera V-1 veces
            bool cambios = false;

            for (const auto& edge : edges) { // Itera sobre todos los bordes
                int u = edge.origen;
                int v = edge.destino;
                int peso = edge.peso;

                // Relaja la arista si es posible y actualiza predecesores
                if (dist[u] != INF && dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                    cambios = true;
                }
            }

            exportarTablaImagen(dist, pred, i); // Exporta la tabla en cada paso

            if (!cambios) break; // Si no hubo cambios, se detiene
        }

        detectarYMarcarCiclosNegativos(dist); // Marca ciclos negativos

        // Imprime las distancias finales desde el vertice de origen
        cout << "Distancias desde el vertice " << verticeALetra(origen) << ":\n";
        for (int i = 1; i <= V; ++i) {
            if (dist[i] == -INF) {
                cout << "Vertice " << verticeALetra(i) << ": -INF (ciclo negativo)\n";
            } else {
                cout << "Vertice " << verticeALetra(i) << ": " << (dist[i] == INF ? "INF" : to_string(dist[i])) << endl;
            }
        }
    }
};

// Solicita al usuario el vertice origen en forma de letra
char obtenerVerticeOrigen(int V) {
    char origen;
    cout << "Ingrese el vertice origen (A a " << static_cast<char>('A' + V - 1) << "): ";
    while (true) {
        cin >> origen;
        origen = toupper(origen); // Asegura que el origen sea mayuscula
        if (origen < 'A' || origen >= 'A' + V) { // Verifica validez
            cout << "Entrada no valida. Intente de nuevo: ";
        } else {
            break;
        }
    }
    return origen;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Configura la consola UTF-8 en Windows
#endif

    const int V = 5; // Numero de vertices
    const int E = 6; // Numero de aristas
    Graph graph(V, E); // Crea el grafo con V vertices y E aristas

    // Define el grafo pequeño y sencillo
    graph.addEdge('A', 'B', 4);
    graph.addEdge('A', 'C', 2);
    graph.addEdge('B', 'C', -1);
    graph.addEdge('B', 'D', 2);
    graph.addEdge('C', 'E', 3);
    graph.addEdge('E', 'B', -2);

    graph.exportarGrafo(); // Exporta y genera la imagen del grafo

    char origen = obtenerVerticeOrigen(V); // Solicita el vertice origen al usuario
    graph.bellmanFord(origen); // Ejecuta Bellman-Ford desde el vertice origen

    return 0; // Fin del programa
}
