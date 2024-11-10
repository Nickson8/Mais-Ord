#include "../../Alg1/FILA_ENCADEADA/fila.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n) {
  int i, j;
  bool swapped;
  for (i = 0; i < n - 1; i++) {
    swapped = false;
    for (j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        swapped = true;
      }
    }

    // If no two elements were swapped by inner loop,
    // then break
    if (swapped == false)
      break;
  }
}

void selecao_direta(int v[], int n) {
  int menor_i;
  for (int i = 0; i < n; i++) {
    menor_i = i;
    for (int j = i; j < n; j++) {
      if (v[j] < v[menor_i]) {
        menor_i = j;
      }
    }
    swap(&v[i], &v[menor_i]);
  }
}

void insertion_sort(int v[], int n) {
  int i, j, aux;
  for (int i = 1; i < n; i++) {
    aux = v[i];
    for (int j = i - 1; j >= 0 && aux < v[j]; j--) {
      v[j + 1] = v[j];
    }
    v[j + 1] = aux;
  }
}

void shell_sort(int v[], int n, int incrementos[], int n_inc) {
  int inc, i, j, aux;
  for (inc = 0; inc < n_inc; inc++) {
    int h = incrementos[inc];
    for (int i = h; i < n; i++) {
      aux = v[i];
      for (int j = i - h; j >= 0 && aux < v[j]; j -= h) {
        v[j + h] = v[j];
      }
      v[j + h] = aux;
    }
  }
}

void quick_sort(int v[], int ini, int fim) {
  int pivo = v[(ini + fim) / 2];
  int i = ini, j = fim;

  do {
    while (v[i] < pivo)
      i++;
    while (v[j] > pivo)
      j--;

    if (i <= j) {
      swap(&v[i], &v[j]);
      i++;
      j--;
    }

  } while (i < j);

  if (j > ini)
    quick_sort(v, ini, j);
  if (i < fim)
    quick_sort(v, i, fim);
}

void rearranjar_heap(int v[], int i, int tamanho_do_heap) {
  int esq, dir, maior, aux;
  esq = 2 * i + 1;
  dir = 2 * i + 2;
  if ((esq < tamanho_do_heap) && (v[esq] > v[i]))
    maior = esq;
  else
    maior = i;
  if ((dir < tamanho_do_heap) && (v[dir] > v[maior]))
    maior = dir;
  if (maior != i) {
    aux = v[i];
    v[i] = v[maior];
    v[maior] = aux;
    rearranjar_heap(v, maior, tamanho_do_heap);
  }
}

void construir_heap(int v[], int tam) {
  for (int i = (tam / 2) - 1; i >= 0; i--) {
    rearranjar_heap(v, i, tam);
  }
}

void heap_sort(int v[], int tam) {
  construir_heap(v, tam);
  swap(&v[0], &v[tam - 1]);
  tam--;
  for (int i = 0; i < tam; i++) {
    rearranjar_heap(v, 0, tam);
    swap(&v[0], &v[tam - 1]);
    tam--;
  }
}

void intercala(int v[], int ini, int meio, int fim) {
  int i, j, k, n1, n2;

  // calculando tamanho dos subarranjos
  n1 = meio - ini + 1;
  n2 = fim - meio;

  // declarando subarranjos que serão intercalados
  int L[n1 + 1], R[n2 + 1];

  // iniciando subarranjos a partir de v
  for (i = 0; i < n1; i++)
    L[i] = v[ini + i];
  L[n1] = 9999; // inserindo sentinela

  for (j = 0; j < n2; j++)
    R[j] = v[meio + j + 1];
  R[n2] = 9999; // inserindo sentinela

  // intercalando arranjos
  i = j = 0;
  for (k = ini; k <= fim; k++)
    if (L[i] <= R[j]) {
      v[k] = L[i];
      i++;
    } else {
      v[k] = R[j];
      j++;
    }
}

void merge_sort(int v[], int ini, int fim) {
  int meio = (ini + fim) / 2;
  if (ini < fim) { // existe mais de 1 elemento
    merge_sort(v, ini, meio);
    merge_sort(v, meio + 1, fim);
    intercala(v, ini, meio, fim);
  }
}

int digito(int n, int m) {
  for (int i = 0; i < m; i++) {
    n = n / 10;
  }

  return n % 10;
}

void radix_sort(int v[], int tam) {

  FILA *f[10];

  for (int i = 0; i < 10; i++) {
    f[i] = fila_criar();
  }

  int maior = -999999;
  for (int i = 0; i < tam; i++) {
    if (v[i] > maior)
      maior = v[i];
  }

  int m = 1;
  while (maior / 10 != 0) {
    m++;
    maior /= 10;
  }

  int k;
  for (int j = 0; j < m; j++) {
    for (int i = 0; i < tam; i++) {
      fila_inserir(f[digito(v[i], m)], v[i]);
    }

    k = 0;
    for (int i = 0; i < tam; i++) {
      while (!fila_vazia(f[i]))
        v[k++] = fila_remover(f[i]);
    }
  }
}

// contagem de menores
void contagem_de_menores(int v[], int tam) {
  int cont[tam];
  memset(cont, 0, tam * sizeof(int));

  for (int i = 0; i < tam; i++) {
    for (int j = 0; j < tam; j++) {
      if (v[j] < v[i]) {
        cont[i]++;
      }
    }
  }

  int aux[tam];
  memcpy(aux, v, tam * sizeof(int));
  memset(v, -1, tam * sizeof(int));

  for (int i = 0; i < tam; i++) {
    int ind = cont[i];
    while (v[ind] != -1 && ind < tam) {
      ind++;
    }
    v[ind] = aux[i];
  }
}

// contagem de tipos
void counting_sort(int v[], int tam) {
  int min = INT_MAX;
  int max = -INT_MAX;

  for (int i = 0; i < tam; i++) {
    if (v[i] < min) {
      min = v[i];
    }

    if (v[i] > max) {
      max = v[i];
    }
  }

  int range = max - min + 1;
  int offset = 0;
  if (min < 0) {
    offset = -min;
  }

  int tipos[range];
  memset(tipos, 0, range * sizeof(int));

  for (int i = 0; i < tam; i++) {
    tipos[v[i] + offset]++;
  }

  int ind = 0;

  for (int i = min; i <= max; i++) {
    if (tipos[i + offset] == 0) {
      continue;
    }

    for (int j = 0; j < tipos[i + offset]; j++) {
      v[ind++] = i;
    }
  }
}
