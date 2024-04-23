#include <iostream>

using namespace std;

// Función para reservar memoria para una matriz de tamaño m x m
int** reservarMatriz(int m) {
    int** matriz = new int*[m + 1];
    for (int i = 1; i <= m; i++) {
        matriz[i] = new int[m + 1];
    }
    return matriz;
}

// Función para liberar memoria de una matriz
void liberarMatriz(int** matriz, int m) {
    for (int i = 1; i <= m; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

// Función para generar una matriz con números ascendentes, con el centro en 0
void generarMatriz(int** matriz, int m) {
    int k = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == (m + 1) / 2 && j == (m + 1) / 2) {
                matriz[i][j] = 0;
            } else {
                matriz[i][j] = k++;
            }
        }
    }
}

// Función para rotar una matriz en 90 grados en sentido horario
void rotarMatriz(int** matriz, int m) {
    // Crear una matriz temporal para almacenar la matriz rotada
    int** matrizRotada = reservarMatriz(m);

    // Realizar la rotación
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            matrizRotada[j][m - i + 1] = matriz[i][j];
        }
    }

    // Copiar la matriz rotada de vuelta a la matriz original
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            matriz[i][j] = matrizRotada[i][j];
        }
    }

    // Liberar la memoria de la matriz temporal
    liberarMatriz(matrizRotada, m);
}

// Función para imprimir una matriz
void imprimirMatriz(int** matriz, int m) {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Función para agregar un dato al final de un arreglo
int* agregarDato(int numero, int* arreglo, int longitud) {
    int* nuevoArreglo = new int[longitud + 1];
    for (int i = 0; i < longitud; i++) {
        nuevoArreglo[i] = arreglo[i];
    }
    nuevoArreglo[longitud] = numero;
    delete[] arreglo;
    return nuevoArreglo;
}

// Función para crear una "cerradura" de matrices y comparar los valores según las condiciones definidas en la clave
void crearCerradura() {
    int contador = 0, condicion;
    cout << "Ingrese la clave: (La condicion 1 es la fila y la condicion 2 es la columna)" << endl;
    int* clave = nullptr;

    // Leer las condiciones de entrada del usuario
    while (true) {
        cout << "Ingrese la condicion " << contador + 1 << ": ";
        cin >> condicion;
        if (condicion == -3) {
            break;
        }
        if (contador == 0 || contador == 1) {
            if (condicion < 1) {
                cout << "La fila o la columna deben ser positivas" << endl;
            } else {
                clave = agregarDato(condicion, clave, contador);
                contador++;
            }
        } else {
            if (condicion != 0 && condicion != 1 && condicion != -1 && condicion != -3) {
                cout << "Debe ingresar <0> <1> <-1> o <-3>" << endl;
            } else {
                if (condicion != -3) {
                    clave = agregarDato(condicion, clave, contador);
                    contador++;
                } else {
                    if (contador <= 2) {
                        cout << "Debe ingresar al menos 3 condiciones (fila, columna, condicion1)" << endl;
                    } else {
                        break;
                    }
                }
            }
        }
    }
    int modos[contador-1] = {0};
    int dimensiones[contador-1] = {0}; // Nuevo arreglo para almacenar las dimensiones de las matrices

    // Calcular la dimensión de las matrices de la cerradura
    int dimension = (clave[0] > clave[1]) ? clave[0] : clave[1];
    if (dimension % 2 == 0) {
        dimension++;
    }
    dimension=dimension+(contador);
    if (dimension % 2 == 0) {
        dimension++;
    }

    int dimension1=dimension;
    int dimension2=dimension;

    // Generar la matriz base para la cerradura y mostrarla
    int** matrizBase = reservarMatriz(dimension);
    generarMatriz(matrizBase, dimension);
    cout << "\nMatriz base para esta clave:" << endl;
    imprimirMatriz(matrizBase, dimension);

    // Imprimir todos los elementos del arreglo clave, excluyendo -3
    cout << "Elementos del arreglo clave:" << endl;
    for (int i = 0; i < contador; ++i) {
        cout << clave[i] << " ";
    }
    cout << endl;

    cout <<"\nCantidad de elementos en la clave: "<<contador << endl;

    // Crear todas las matrices de la cerradura y comparar los valores según la clave
    for (int i = 0; i < contador - 2; ++i) {
        bool claveCumplida = false;

        int** matriz1 = reservarMatriz(dimension1);
        generarMatriz(matriz1, dimension1);
        int** matriz2 = reservarMatriz(dimension2);
        generarMatriz(matriz2, dimension2);

        // Realizar las comparaciones entre las matrices
        cout << "\nComparaciones entre los valores en las matrices rotadas:" << endl;

        int rotacionesMatriz = 0; // Contador de rotaciones para matriz2
        int rotacionesModos = modos[i+1]; // Obtener las rotaciones de la matriz correspondiente
        // Realizar las rotaciones necesarias para la matriz 1
        for (int r = 0; r < rotacionesModos; ++r) {
            rotarMatriz(matriz1, dimension1);
        }

        // Realizar las rotaciones necesarias para la matriz 2
        for (int r = 0; r < rotacionesMatriz; ++r) {
            rotarMatriz(matriz2, dimension2);
        }
        int condicionComparacion = clave[i + 2];
        int fila = clave[0];
        int fila1=fila;
        int fila2=fila;
        int columna = clave[1];
        int columna1=columna;
        int columna2=columna;
        int aux = 0;

        do{
            // Realizar las comparaciones entre las matriz 2
            for (int m=0; m<4; ++m){
                // Realizar las comparaciones entre las matrices
                int valorA = matriz1[fila1][columna1];
                int valorB = matriz2[fila2][columna2];

                // Verificar si la clave se cumple en la posición dada
                bool resultadoComparacion = false;
                if (condicionComparacion == 1) {
                    resultadoComparacion = (valorA > valorB);
                } else if (condicionComparacion == 0) {
                    resultadoComparacion = (valorA == valorB);
                } else if (condicionComparacion == -1) {
                    resultadoComparacion = (valorA < valorB);
                }

                if (resultadoComparacion) {
                    cout << "La restriccion se cumplio en la comparacion " << m + 1 << " - Matriz " << i + 1 << " vs Matriz " << i + 2 << " rotada " << (rotacionesMatriz * 90) << " grados: Cumple" << endl << endl;
                    imprimirMatriz(matriz1, dimension1);
                    imprimirMatriz(matriz2, dimension2);
                    claveCumplida = true;
                    modos[i + 2] = rotacionesMatriz;
                    break; // Si la clave se cumple, salir del bucle
                }

                // Rotar la matriz 2 para la próxima iteración
                rotarMatriz(matriz2, dimension2);
                rotacionesMatriz++;
            }

            if (!claveCumplida) {
                liberarMatriz(matriz2, dimension2);
                dimension2 = dimension;
                matriz2 = reservarMatriz(dimension2);
                generarMatriz(matriz2, dimension2);
                rotacionesMatriz = 0;
                cout << "La dimension de la matriz B se va a modificar:" << endl;
                if (condicionComparacion == 1) {
                    cout << endl << "Matriz2 se va a reducir" << endl;
                    liberarMatriz(matriz2, dimension2);
                    dimension2 = dimension2 - 2;
                    matriz2 = reservarMatriz(dimension2);
                    generarMatriz(matriz2, dimension2);
                    fila2 = fila2 - 1;
                    columna2 = columna2 - 1;
                } else if (condicionComparacion == 0) {
                    if (dimension1 > dimension2) {
                        cout << endl << "Matriz2 va a aumentar" << endl;
                        liberarMatriz(matriz2, dimension2);
                        dimension2 = dimension2 + 2;
                        matriz2 = reservarMatriz(dimension2);
                        generarMatriz(matriz2, dimension2);
                        fila2 = fila2 + 1;
                        columna2 = columna2 + 1;
                    } else if (dimension1 < dimension2) {
                        cout << endl << "Matriz2 se va a reducir" << endl;
                        liberarMatriz(matriz2, dimension2);
                        dimension2 = dimension2 - 2;
                        matriz2 = reservarMatriz(dimension2);
                        generarMatriz(matriz2, dimension2);
                        fila2 = fila2 - 1;
                        columna2 = columna2 - 1;
                    }
                } else if (condicionComparacion == -1) {
                    cout << endl << "Matriz2 va a aumentar" << endl;
                    liberarMatriz(matriz2, dimension2);
                    dimension2 = dimension2 + 2;
                    matriz2 = reservarMatriz(dimension2);
                    generarMatriz(matriz2, dimension2);
                    fila2 = fila2 + 1;
                    columna2 = columna2 + 1;
                }
                aux++;
                cout << endl << aux << endl;
            }
        }while(!claveCumplida && aux<100 && dimension2>=3);

        if (!claveCumplida) {
            modos[i+2] = 0; // Si no se cumple, almacenar cero en la posición correspondiente
            cout << "La restriccion NO se cumplio con ninguna rotacion" << endl;
        }
        if (i==0) {
            dimensiones[i] = dimension1;
        }
        // Almacenar la dimensión de la matriz 2 en dimensiones
        dimensiones[i + 1] = dimension2;

        // Liberar memoria de las matrices
        liberarMatriz(matriz1, dimension1);
        liberarMatriz(matriz2, dimension2);

        // Actualizar la dimensión de la matriz 1 para la siguiente iteración
        dimension1 = dimension2;
    }

    // Imprimir los modos de rotación
    cout << "\nModos de rotacion: { ";
    for (int i = 1; i < contador; ++i) {
        cout << modos[i] << " ";
    }
    cout << "}" << endl;

    // Imprimir las dimensiones de las matrices
    cout << "Dimensiones de las matrices: { ";
    for (int i = 0; i < contador - 1; ++i) {
        cout << dimensiones[i] << " ";
    }
    cout << "}" << endl;

    // Liberar memoria de la matriz base
    liberarMatriz(matrizBase, dimension);
    delete[] clave;
}

int main() {
    crearCerradura();
    return 0;
}
