#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int verificarInput(int input);
int verificarHilos(int n, int col, int row);
int verificarMatrices(int col, int row);

int main(int argc, char *argv[]) {
  if (verificarInput(argc) == -1)
    return -1;
  srand(time(0));
  int numHilos = atoi(argv[5]);
  int columnas_A = atoi(argv[1]);
  int filas_A = atoi(argv[2]);
  int columnas_B = atoi(argv[3]);
  int filas_B = atoi(argv[4]);
  if (verificarHilos(numHilos, columnas_A, filas_A) == -1)
    return -1;
  if (verificarMatrices(columnas_A, filas_B) == -1)
    return -1;
  printf("Se realizara la multiplicacion de matrices con los valores:\n");
  printf("Columnas de A: %d\nFilas de A: %d\n", columnas_A, filas_A);
  printf("Columnas de B: %d\nFilas de B: %d\n", columnas_B, filas_B);
  printf("Numero de hilos: %d\n", numHilos);
}

int verificarInput(int input) {
  if (input < 5) {
    printf("[ERROR] - Error al introducir datos\n");
    printf("[ERROR] - Numero de parametros incorrecto\n");
    printf("Uso: ./programa <colA> <filA> <colB> <filB> <numHilos>\n");
    return -1;
  }
  return 0;
}

int verificarHilos(int n, int col, int row) {
  if (n > col || n > row) {
    printf("[ERROR] - El numero de hilos no puede ser mayor que el numero de "
           "filas y columnas de la matriz A\n");
    printf("[ERROR] - Valor introducido: %d\n", n);
    return -1;
  }
  return 0;
}

int verificarMatrices(int col, int row) {
  if (col != row) {
    printf("[ERROR] - La multiplicacion de matrices no puede llevarse a cabo "
           "con esos valores.\n");
    printf("[ERROR] - Valores introducidos: columnas de A = %d, filas de B = "
           "%d.\n",
           col, row);
    return -1;
  }
  return 0;
}