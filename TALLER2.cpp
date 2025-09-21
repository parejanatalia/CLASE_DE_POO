
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    int opcion = 0;

    cout << "=== TALLER2 -ARRAYS Y VECTORES ===" << endl;

    while (opcion != 8) {
        cout << "\n---------------------------------------------------" << endl;
        cout << "MENU DE EJERCICIOS" << endl;
        cout << "1. Mediana de un array" << endl;
        cout << "2. Busqueda binaria" << endl;
        cout << "3. Transpuesta de una matriz" << endl;
        cout << "4. Sistema de inventario simple" << endl;
        cout << "5. Ordenamiento por seleccion" << endl;
        cout << "6. Encontrar elementos duplicados" << endl;
        cout << "7. Juego de tres en raya" << endl;
        cout << "8. Salir" << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "Elige una opcion (1-8): ";

        cin >> opcion;

        switch (opcion) {
            case 1: {
                // === EJERCICIO 1: MEDIANA DE UN ARRAY ===
                cout << "\n--- 1. Mediana de un array ---\n";
                int n_ingresados; // Aquí se almacena la cantidad de números que se van a ingresar para calcular la mediana
                cout << "Cuantos numeros quieres ingresar?: ";
                      cin >> n_ingresados;
                int numeros_ingresados[100];
                cout << "Ingresa los numeros: ";

                for (int i = 0; i < n_ingresados; i++) {
                   // aqui
                        cin >> numeros_ingresados[i];
                }

                // Ordenar el array (usando burbuja)
                for (int i = 0; i < n_ingresados - 1; i++) {
                    for (int j = 0; j < n_ingresados - 1 - i; j++) {
                    if (numeros_ingresados[j] > numeros_ingresados[j + 1]) {

                            int temp = numeros_ingresados[j];
                            numeros_ingresados[j] = numeros_ingresados[j + 1];
                            numeros_ingresados[j + 1] = temp;
                    }
                    }
                }

                cout << "Array ordenado: ";
                for (int i = 0; i < n_ingresados; i++)
                    cout << numeros_ingresados[i] << "   ";
                cout << endl;

                double mediana;//me falta arreglar el problema con los n ingresados
                if (n_ingresados % 2 == 0) {
                        mediana = (double)(numeros_ingresados[n_ingresados / 2 - 1] + numeros_ingresados[n_ingresados / 2]) / 2.0;
                } else {
                    mediana = numeros_ingresados[n_ingresados / 2];
                }
                cout << "La mediana es: " << mediana << endl;
                break;
            }
            case 2: {
                // === EJERCICIO 2: BÚSQUEDA BINARIA ===
                cout << "\n--- 2. Busqueda binaria ---\n";
                // Este es el array ordenado donde se va a realizar la búsqueda.
                int array_a_buscar[] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
                int tamano_array = 9;
                cout << "Array a buscar: ";
                for (int i = 0; i < tamano_array; i++) cout << array_a_buscar[i] << " ";
                cout << endl;
                int numero_a_buscar;
                cout << "Introduce un numero a buscar: ";
                cin >> numero_a_buscar;

                int indice_izq = 0, indice_der = tamano_array - 1;
                bool encontrado = false;
                int posicion_encontrada = -1;

                while (indice_izq <= indice_der) {
                    int indice_medio = indice_izq + (indice_der - indice_izq) / 2;
                    if (array_a_buscar[indice_medio] == numero_a_buscar) {
                        encontrado = true;
                        posicion_encontrada = indice_medio;
                        break;
                    }
                    if (array_a_buscar[indice_medio] < numero_a_buscar) {
                        indice_izq = indice_medio + 1;
                    } else {
                        indice_der = indice_medio - 1;
                    }
                }

                if (encontrado) {
                    cout << "El elemento " << numero_a_buscar << " se encontro en la posicion " << posicion_encontrada << "\n";
                } else {
                    cout << "El elemento " << numero_a_buscar << " no se encontro en el array\n";
                }
                break;
            }
            case 3: {
                // === EJERCICIO 3: TRANSPUESTA DE UNA MATRIZ ===
                cout << "\n--- 3. Transpuesta de una matriz ---\n";
                int matriz_original[2][3] = {{1, 2, 3}, {4, 5, 6}};
                int filas_matriz = 2, columnas_matriz = 3;
                int matriz_transpuesta[3][2];

                cout << "Matriz original:\n";
                for (int i = 0; i < filas_matriz; i++) {
                    cout << "    ";
                    for (int j = 0; j < columnas_matriz; j++) {
                        cout << setw(3) << matriz_original[i][j] << " ";
                    }
                    cout << "\n";
                }

                // Calcular la transpuesta
                for (int i = 0; i < filas_matriz; i++) {
                    for (int j = 0; j < columnas_matriz; j++) {
                        matriz_transpuesta[j][i] = matriz_original[i][j];
                    }
                }

                cout << "\nMatriz transpuesta:\n";
                for (int i = 0; i < columnas_matriz; i++) {
                    cout << "    ";
                    for (int j = 0; j < filas_matriz; j++) {
                        cout << setw(3) << matriz_transpuesta[i][j] << " ";
                    }
                    cout << "\n";
                }
                break;
            }
            case 4: {
                // === EJERCICIO 4: SISTEMA DE INVENTARIO SIMPLE ===
                cout << "\n--- 4. Sistema de inventario simple ---\n";
                const int CAPACIDAD_MAXIMA = 50;
                string nombres_productos[CAPACIDAD_MAXIMA];
                int cantidades_productos[CAPACIDAD_MAXIMA];
                int total_productos = 0;
                int sub_opcion;

                while (true) {
                    cout << "\n-- Menu de Inventario --" << endl;
                    cout << "1. Agregar producto" << endl;
                    cout << "2. Mostrar inventario" << endl;
                    cout << "3. Salir del inventario" << endl;
                    cout << "Elige una opcion: ";
                    cin >> sub_opcion;

                    if (sub_opcion == 1) {
                        if (total_productos < CAPACIDAD_MAXIMA) {
                            cout << "Nombre del producto: ";
                            cin.ignore();
                            getline(cin, nombres_productos[total_productos]);
                            cout << "Cantidad: ";
                            cin >> cantidades_productos[total_productos];
                            total_productos++;
                        } else {
                            cout << "Inventario lleno, no se pueden agregar mas productos." << endl;
                        }
                    } else if (sub_opcion == 2) {
                        cout << "\n--- Inventario Actual ---\n";
                        cout << setw(15) << "PRODUCTO" << setw(10) << "CANTIDAD" << "\n";
                        cout << "-------------------------\n";
                        for (int i = 0; i < total_productos; i++) {
                            cout << setw(15) << nombres_productos[i] << setw(10) << cantidades_productos[i] << "\n";
                        }
                    } else if (sub_opcion == 3) {
                        break;
                    } else {
                        cout << "Opcion no valida." << endl;
                    }
                }
                break;
            }
            case 5: {
                // === EJERCICIO 5: ORDENAMIENTO POR SELECCIÓN ===
                cout << "\n--- 5. Ordenamiento por seleccion ---\n";
                int cantidad_numeros;
                cout << "Cuantos numeros quieres ordenar?: ";
                cin >> cantidad_numeros;
                int array_desordenado[100];
                cout << "Ingresa los numeros: ";
                for (int i = 0; i < cantidad_numeros; i++) {
                    cin >> array_desordenado[i];
                }

                // Algoritmo de ordenamiento por seleccion
                for (int i = 0; i < cantidad_numeros - 1; i++) {
                    int indice_minimo = i;
                    for (int j = i + 1; j < cantidad_numeros; j++) {
                        if (array_desordenado[j] < array_desordenado[indice_minimo]) {
                            indice_minimo = j;
                        }
                    }
                    int temporal = array_desordenado[i];
                    array_desordenado[i] = array_desordenado[indice_minimo];
                    array_desordenado[indice_minimo] = temporal;
                }

                cout << "Array ordenado: ";
                for (int i = 0; i < cantidad_numeros; i++) cout << array_desordenado[i] << " ";
                cout << endl;
                break;
            }
            case 6: {
                // === EJERCICIO 6: ENCONTRAR ELEMENTOS DUPLICADOS ===
                cout << "\n--- 6. Encontrar elementos duplicados ---\n";
                int cantidad_numeros_dup;
                cout << "Cuantos numeros quieres ingresar?: ";
                cin >> cantidad_numeros_dup;
                int array_con_duplicados[100];
                cout << "Ingresa los numeros: ";
                for (int i = 0; i < cantidad_numeros_dup; i++) {
                    cin >> array_con_duplicados[i];
                }

                bool hay_duplicado = false;
                cout << "\nBuscando duplicados...\n";
                for (int i = 0; i < cantidad_numeros_dup; i++) {
                    for (int j = i + 1; j < cantidad_numeros_dup; j++) {
                        if (array_con_duplicados[i] == array_con_duplicados[j]) {
                            cout << "Elemento duplicado encontrado: " << array_con_duplicados[i] << endl;
                            hay_duplicado = true;
                        }
                    }
                }
                if (!hay_duplicado) {
                    cout << "No se encontraron duplicados." << endl;
                }
                break;
            }
            case 7: {
                // === EJERCICIO 7: JUEGO DE TRES EN RAYA ===
                cout << "\n--- 7. Juego de tres en raya ---\n";
                char tablero[3][3] = {{'1','2','3'}, {'4','5','6'}, {'7','8','9'}};
                char jugador_actual = 'X';
                int eleccion_casilla;
                bool hay_ganador = false;

                for (int turno = 0; turno < 9; turno++) {
                    cout << "\n";
                    for (int i = 0; i < 3; i++) {
                        cout << " " << tablero[i][0] << " | " << tablero[i][1] << " | " << tablero[i][2] << endl;
                        if (i < 2) cout << "---|---|---\n";
                    }

                    cout << "\nTurno del jugador " << jugador_actual << ". Elige una casilla: ";
                    cin >> eleccion_casilla;

                    int fila_elegida = (eleccion_casilla - 1) / 3;
                    int col_elegida = (eleccion_casilla - 1) % 3;

                    if (tablero[fila_elegida][col_elegida] != 'X' && tablero[fila_elegida][col_elegida] != 'O') {
                        tablero[fila_elegida][col_elegida] = jugador_actual;

                        // Revisar si hay ganador
                        for (int i = 0; i < 3; i++) {
                            if ((tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) ||
                                (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i])) {
                                hay_ganador = true;
                            }
                        }
                        if ((tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) ||
                            (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0])) {
                            hay_ganador = true;
                        }

                        if (hay_ganador) {
                            cout << "¡El jugador " << jugador_actual << " ha ganado!\n";
                            break;
                        }

                        if (jugador_actual == 'X') jugador_actual = 'O';
                        else jugador_actual = 'X';
                    } else {
                        cout << "Casilla ocupada, pierdes el turno.\n";
                        turno--; // Para que el turno no avance
                    }
                }

                if (!hay_ganador) cout << "¡Es un empate!\n";
                cout << "\nTablero final:\n";
                for (int i = 0; i < 3; i++) {
                    cout << " " << tablero[i][0] << " | " << tablero[i][1] << " | " << tablero[i][2] << endl;
                    if (i < 2) cout << "---|---|---\n";
                }
                break;
            }
            case 8:
                cout << "\nSaliendo del programa. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "\nOpcion no valida. Por favor, elige un numero del 1 al 8." << endl;
                break;
        }
    }

    return 0;
}
