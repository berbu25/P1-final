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
    int* clave = new int[contador];

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
                        false;
                    }
                }
            }
        }
    }

    // Calcular la dimensión de las matrices de la cerradura
    int dimension = (clave[0] > clave[1]) ? clave[0] : clave[1];
    if (dimension % 2 == 0) {
        dimension++;
    }
    //Hace que la dimensión minima de la matriz sea 3x3
    if (dimension < 3) {
        dimension = 3;
    }

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

        int** matriz1 = reservarMatriz(dimension);
        generarMatriz(matriz1, dimension);

        int** matriz2 = reservarMatriz(dimension);
        generarMatriz(matriz2, dimension);


        // Realizar las comparaciones entre las matrices
        cout << "\nComparaciones entre los valores en las matrices rotadas:" << endl;
        bool claveCumplida = false;

        //int rotacionesMatriz1 = 0; //Contador de rotaciones para matriz1
        int rotacionesMatriz = 0; // Contador de rotaciones para matriz2

        // Realizar las comparaciones entre las matriz 2
        for (int m=0; m<4; ++m){

            // Realizar las comparaciones entre las matrices
            int fila = clave[0];
            int columna = clave[1];
            int valorA = matriz1[fila][columna];
            int valorB = matriz2[fila][columna];
            int condicionComparacion = clave[i + 2];

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

                cout << "La restriccion se cumplio en la comparacion " << m + 1<<" - Matriz " <<i+1<<" vs Matriz "<< i + 2 << " rotada " << (rotacionesMatriz * 90) << " grados: Cumple" << endl <<endl;
                imprimirMatriz(matriz1, dimension);
                imprimirMatriz(matriz2, dimension);
                claveCumplida = true;
                break; // Si la clave se cumple, salir del bucle
            }

            //ESTO DE ABAJO LO AGREGUÉ PARA IMPRIMIR LA MATRIZ A DE LA COMPARACION BORRARRRRRRRRR
            cout<<endl<<"Matriz "<<i + 1<<endl;
            imprimirMatriz(matriz1, dimension);

            // Rotar la matriz 2 para la próxima iteración
            cout<<endl<<"Matriz "<<i + 2<<" parcialmente rotada"<<endl;
            imprimirMatriz(matriz2, dimension);
            rotarMatriz(matriz2, dimension);
            rotacionesMatriz++;

            cout<<endl<<"Va a hacer otra iteracion\n"<<endl;

            if (claveCumplida) {
                break;
            }
            if (!claveCumplida) { // si no se cumple se debe ampliar matriz

            }
        }
        if (!claveCumplida) {
            if (rotacionesMatriz!=0){
                rotacionesMatriz=0;
            }
            cout << "La restriccion NO se cumplio con ninguna rotacion"<< endl;
            //cout << "No se cumplio la clave en ninguna rotacion de las matrices " << i + 1 << " y " << i + 2 << endl;
        }
        cout<<endl<<"Rotacion:"<<rotacionesMatriz<<endl;
        // Liberar memoria de las matrices
        liberarMatriz(matriz1, dimension);
        liberarMatriz(matriz2, dimension);
    }

    // Liberar memoria de la matriz base
    liberarMatriz(matrizBase, dimension);
}

int main() {
    crearCerradura();
    return 0;
}
