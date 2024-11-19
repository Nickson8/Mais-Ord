#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>


/******************************************************************************************************/

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

/**
 * O Bubble Sort é um algoritmo simples que percorre o vetor repetidamente, comparando elementos
 * adjacentes e os trocando de posição, se necessário.
 * 
 * @param arr -> vetor que será ordenado
 * @param n -> tamanho do vetor
 * @param swaps -> ponteiro que aponta para a variável que irá guardar o número de swaps
 * @param comps -> ponteiro que aponta para a variável que irá guardar o número de comparações
 * 
 * @return -> void
 */
void bubbleSort(int *arr, int n, long long int *swaps, long long int *comps) {
  int i, j;
  bool swapped;
  for (i = 0; i < n - 1; i++) {
    swapped = false;
    for (j = 0; j < n - i - 1; j++) {
      (*comps)++;
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        (*swaps)++;
        swapped = true;
      }
    }

    if (swapped == false)
      break;
  }
}

/******************************************************************************************************/

/**
 * O Selection Sort funciona selecionando o menor elemento de uma parte do vetor e o movendo para a
 * posição correta a cada iteração.
 * 
 * @param v -> vetor que será ordenado
 * @param n -> tamanho do vetor
 * @param swaps -> ponteiro que aponta para a variável que irá guardar o número de swaps
 * @param comps -> ponteiro que aponta para a variável que irá guardar o número de comparações
 * 
 * @return -> void
 */
void selecao_direta(int v[], int n, long long int *swaps,
                    long long int *comps) {
  int menor_i;
  for (int i = 0; i < n - 1; i++) {
    menor_i = i;
    for (int j = i + 1; j < n; j++) {
      (*comps)++;
      if (v[j] < v[menor_i]) {
        menor_i = j;
      }
    }
    if (i != menor_i) {
      swap(&v[i], &v[menor_i]);
      (*swaps)++;
    }
  }
}

/******************************************************************************************************/

/**
 * O Insertion Sort constrói o vetor ordenado gradualmente, inserindo elementos na posição correta.
 * 
 * @param v -> vetor que será ordenado
 * @param n -> tamanho do vetor
 * @param swaps -> ponteiro que aponta para a variável que irá guardar o número de swaps
 * @param comps -> ponteiro que aponta para a variável que irá guardar o número de comparações
 * 
 * @return -> void
 */
void insertion_sort(int v[], int n, long long int *swaps,
                    long long int *comps) {
  int i, j, aux;
  for (i = 1; i < n; i++) {
    aux = v[i];
    for (j = i - 1; j >= 0; j--) {
      (*comps)++;
      if (v[j] > aux) {
        v[j + 1] = v[j];
        (*swaps)++;
      } else {
        break;
      }
    }
    if (j != i - 1) {
      v[j + 1] = aux;
      (*swaps)++;
    }
  }
}

/******************************************************************************************************/


/**
 * O Shell Sort é uma generalização do Insertion Sort que melhora sua eficiência utilizando trocas
 * em intervalos maiores (gaps), reduzidos gradativamente.
 * 
 * @param v -> vetor que será ordenado
 * @param n -> tamanho do vetor
 * @param swaps -> ponteiro que aponta para a variável que irá guardar o número de swaps
 * @param comps -> ponteiro que aponta para a variável que irá guardar o número de comparações
 * 
 * @return -> void
 */
void shell_sort(int v[], int n, long long int *swaps, long long int *comps) {
  int incrementos[] = {5, 3, 1};
  int n_inc = 3;

  int inc, i, j, aux;
  for (inc = 0; inc < n_inc; inc++) {
    int h = incrementos[inc];
    for (i = h; i < n; i++) {
      aux = v[i];
      for (j = i - h; j >= 0 && aux < v[j]; j -= h) {
        (*comps)++;
        if (v[j] > aux) {
          v[j + h] = v[j];
          (*swaps)++;
        }
      }
      if (j != i - h) {
        (*swaps)++;
        v[j + h] = aux;
      }
    }
  }
}


/******************************************************************************************************/


int medianaDeTres(int v[], int ini, int fim) {
  int a=v[ini], b=v[fim], c=v[(ini+fim)/2];
  if ((a > b && a < c) || (a > c && a < b))
      return a;
  else if ((b > a && b < c) || (b > c && b < a))
      return b;
  else
      return c;
}


/**
 * O Quick Sort é um algoritmo de dividir e conquistar que particiona o vetor em dois subvetores em
 * torno de um pivô e ordena cada um recursivamente. 
 * 
 * @param v -> vetor que será ordenado
 * @param ini -> posição inicial do vetor que está sendo ordenado
 * @param fim -> posição final do vetor que está sendo ordenado
 * @param swaps -> ponteiro que aponta para a variável que irá guardar o número de swaps
 * @param comps -> ponteiro que aponta para a variável que irá guardar o número de comparações
 * 
 * @return -> void
 */
void quick_sort(int v[], int ini, int fim, long long int *swaps,
                long long int *comps) {
  int pivo = medianaDeTres(v, ini, fim);
  int i = ini, j = fim;

  do {
    (*comps)++;
    while (v[i] < pivo) {
      (*comps)++;
      i++;
    }
    while (v[j] > pivo) {
      (*comps)++;
      j--;
    }

    (*comps)++;
    if (i <= j) {
      (*swaps)++;
      swap(&v[i], &v[j]);
      i++;
      j--;
    }

  } while (i < j);
  (*comps)++;
  if (j > ini)
    quick_sort(v, ini, j, swaps, comps);
  (*comps)++;
  if (i < fim)
    quick_sort(v, i, fim, swaps, comps);
}


/******************************************************************************************************/


void rearranjar_heap(int v[], int i, int tamanho_do_heap, long long int *swaps,
                     long long int *comps) {
  int esq, dir, maior, aux;
  esq = 2 * i + 1;
  dir = 2 * i + 2;
  (*comps)++;
  if ((esq < tamanho_do_heap) && (v[esq] > v[i]))
    maior = esq;
  else
    maior = i;
  (*comps)++;
  if ((dir < tamanho_do_heap) && (v[dir] > v[maior]))
    maior = dir;

  if (maior != i) {
    (*swaps)++;
    aux = v[i];
    v[i] = v[maior];
    v[maior] = aux;
    rearranjar_heap(v, maior, tamanho_do_heap, swaps, comps);
  }
}

void construir_heap(int v[], int tam, long long int *swaps,
                    long long int *comps) {
  for (int i = (tam / 2) - 1; i >= 0; i--) {
    rearranjar_heap(v, i, tam, swaps, comps);
  }
}


/**
 * O Heap Sort utiliza a estrutura de dados Heap (árvore binária completa) para ordenar o vetor,
 * removendo o maior elemento da heap repetidamente.
 * 
 * @param v -> vetor que será ordenado
 * @param tam -> tamanho do vetor
 * @param swaps -> ponteiro que aponta para a variável que irá guardar o número de swaps
 * @param comps -> ponteiro que aponta para a variável que irá guardar o número de comparações
 * 
 * @return -> void
 */
void heap_sort(int v[], int tam, long long int *swaps, long long int *comps) {
  construir_heap(v, tam, swaps, comps);
  swap(&v[0], &v[tam - 1]);
  (*swaps)++;
  tam--;
  for (int i = tam - 1; i > 0; i--) {
    rearranjar_heap(v, 0, tam, swaps, comps);
    (*swaps)++;
    swap(&v[0], &v[tam - 1]);
    tam--;
  }
}

/******************************************************************************************************/


void intercala(int v[], int ini, int meio, int fim, long long int *swaps,
               long long int *comps) {
  int i, j, k, n1, n2;

  // calculando tamanho dos subarranjos
  n1 = meio - ini + 1;
  n2 = fim - meio;

  // declarando subarranjos que serão intercalados
  int L[n1 + 1], R[n2 + 1];

  // iniciando subarranjos a partir de v
  for (i = 0; i < n1; i++)
    L[i] = v[ini + i];
  L[n1] = 9999999; // inserindo sentinela

  for (j = 0; j < n2; j++)
    R[j] = v[meio + j + 1];
  R[n2] = 9999999; // inserindo sentinela

  // intercalando arranjos
  i = j = 0;
  for (k = ini; k <= fim; k++) {
    if(L[i]!=9999999 && R[j]!=9999999)(*comps)++;
    if (L[i] <= R[j]) {
      v[k] = L[i];
      i++;
    } else {
      v[k] = R[j];
      j++;
      if(L[i]!=9999999) (*swaps)++;
    }
  }
}


/**
 * O Merge Sort é um algoritmo de dividir e conquistar que divide o vetor ao meio, ordena as partes
 * recursivamente e as intercala. 
 * 
 * @param v -> vetor que será ordenado
 * @param ini -> posição inicial do vetor que está sendo ordenado
 * @param fim -> posição final do vetor que está sendo ordenado
 * @param swaps -> ponteiro que aponta para a variável que irá guardar o número de swaps
 * @param comps -> ponteiro que aponta para a variável que irá guardar o número de comparações
 * 
 * @return -> void
 */
void merge_sort(int v[], int ini, int fim, long long int *swaps,
                long long int *comps) {
  int meio = (ini + fim) / 2;
  if (ini < fim) { // existe mais de 1 elemento
    merge_sort(v, ini, meio, swaps, comps);
    merge_sort(v, meio + 1, fim, swaps, comps);
    intercala(v, ini, meio, fim, swaps, comps);
  }
}


/******************************************************************************************************/


int digito(int n, int m) {
  for (int i = 0; i < m; i++) {
    n = n / 10;
  }

  return n % 10;
}


/**
 * O algoritmo Contagem dos Menores conta quantos elementos no vetor são menores que cada elemento e
 * usa essa informação para colocá-los na posição correta. 
 * 
 * @param v -> vetor que será ordenado
 * @param tam -> tamanho do vetor
 * @param swaps -> ponteiro que aponta para a variável que irá guardar o número de swaps
 * @param comps -> ponteiro que aponta para a variável que irá guardar o número de comparações
 * 
 * @return -> void
 */
void contagem_de_menores(int v[], int tam, long long int *swaps,
                         long long int *comps) {
  int cont[tam];
  memset(cont, 0, tam * sizeof(int));

  for (int i = 0; i < tam; i++) {
    for (int j = 0; j < tam; j++) {
      (*comps)++;
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


/******************************************************************************************************/


/**
 * O Radix Sort é um algoritmo não baseado em comparações que ordena números inteiros processando cada
 * dígito separadamente.
 * 
 * @param v -> vetor que será ordenado
 * @param tam -> tamanho do vetor
 * @param swaps -> ponteiro que aponta para a variável que irá guardar o número de swaps
 * @param comps -> ponteiro que aponta para a variável que irá guardar o número de comparações
 * 
 * @return -> void
 */
void radix_sort(int v[], int tam, long long int *swaps,
                                 long long int *comps) {
  int max = -INT_MAX;

  for (int i = 0; i < tam; i++) { // acha o maior numero
    if (v[i] > max) {
      max = v[i];
    }
  }

  int m_max = log10((double)max); // pega a ordem 10 dele

  for (int i = 0; i <= m_max; i++) { // iterar para cada DIT
    int digitos[10];
    memset(digitos, 0, 10 * sizeof(int));

    for (int j = 0; j < tam; j++) { // contar digitos
      int dig = digito(v[j], i);
      digitos[dig]++;
    }

    int aux[tam];
    memcpy(aux, v, tam * sizeof(int));

    for (int j = 1; j < 10; j++) { // acumular numero de digitos previos
      digitos[j] += digitos[j - 1];
    }

    for (int j = tam - 1; j >= 0; j--) {
      int dig = digito(aux[j], i);
      if (digitos[dig] == 0) {
        continue;
      }

      v[digitos[dig] - 1] = aux[j];
      digitos[dig]--;
    }
  }
}


/******************************************************************************************************/


/**
 * É uma função que pega outra função como parâmetro, nesse caso é uma função de ordenação, calculando
 * o tempo de execução dela.
 * 
 * @param sort_func_tam -> função de ordenação que recebe o tamanho do vetor para ordena-lo
 * @param v -> vetor que será ordenado
 * @param tam -> tamanho do vetor
 * @param swaps -> ponteiro que aponta para a variável que irá guardar o número de swaps
 * @param comps -> ponteiro que aponta para a variável que irá guardar o número de comparações
 * 
 * @return -> tempo de execução
 */
float sort_eval_tam(void (*sort_func_tam)(int *, int, long long int *,
                                          long long int *),
                    int v[], int tam, long long int *swaps,
                    long long int *comps) {
  clock_t start = clock();
  sort_func_tam(v, tam, swaps, comps);
  clock_t end = clock();

  return (((float)end - start)) / CLOCKS_PER_SEC;
}



/**
 * É uma função que pega outra função como parâmetro, nesse caso é uma função de ordenação, calculando
 * o tempo de execução dela.
 * 
 * @param sort_func_inf_sup-> função de ordenação que recebe a posição final e inicial do vetor para ordena-lo
 * @param v -> vetor que será ordenado
 * @param ini -> posição inicial do vetor que está sendo ordenado
 * @param fim -> posição final do vetor que está sendo ordenado
 * @param swaps -> ponteiro que aponta para a variável que irá guardar o número de swaps
 * @param comps -> ponteiro que aponta para a variável que irá guardar o número de comparações
 * 
 * @return -> tempo de execução
 */
float sort_eval_inf_sup(void (*sort_func_inf_sup)(int *, int, int,
                                                  long long int *,
                                                  long long int *),
                        int v[], int inf, int sup, long long int *swaps,
                        long long int *comps) {
  clock_t start = clock();
  sort_func_inf_sup(v, inf, sup, swaps, comps);
  clock_t end = clock();

  return (((float)end - start)) / CLOCKS_PER_SEC;
}

/******************************************************************************************************/


int *gerar_ordenado(int tam) {
  int *v = malloc(tam * sizeof(int));
  for (int i = 0; i < tam; i++) {
    v[i] = i;
  }

  return v;
}


int *gerar_reverso(int tam) {
  int *v = malloc(tam * sizeof(int));
  for (int i = 0; i < tam; i++) {
    v[i] = tam - i;
  }

  return v;
}


int *gerar_aleatorio(int tam) {
  int *v = malloc(tam * sizeof(int));
  for (int i = 0; i < tam; i++) {
    v[i] = rand() % tam;
  }

  return v;
}


bool test_sort(int *v, int tam) {
  for (int i = 0; i < tam - 1; i++) {
    if (v[i] > v[i + 1]) {
      printf("%i larger than %i???\n", v[i], v[i + 1]);
      for (int j = 0; j < tam; j++) {
        printf("%i ", v[j]);
      }
      printf("\n");
      return false;
    }
  }

  return true;
}

/******************************************************************************************************/




int main(void) {
  void (*func_tam)(int *, int, long long int *, long long int *) = &bubbleSort;
  //void (*func_inf_sup)(int *, int, int, long long int *, long long int *) = &quick_sort;

  const char *sortname = "bubble";

  int *(*vec_gen[3])(int) = {&gerar_ordenado, &gerar_reverso, &gerar_aleatorio};
  char *order_type[3] = {"ordered", "reversed", "randomized"};

  char filename[100];
  sprintf(filename, "%sdata.csv", sortname);

  FILE *data = fopen(filename, "w");
  fprintf(data, "order, n, time, comps, swaps\n");

  for (int k = 0; k < 3; k++) {

    for (int size = 100; size <= 10000; size *= 10) {
      long long int swaps = 0;
      long long int comps = 0;

      int *v;
      bool r = true;
      float delta = 0;
      for(int _=0; _<5 && r; _++){

        v = vec_gen[k](size);

        delta += sort_eval_tam(func_tam, v, size, &swaps, &comps);
        //delta +=sort_eval_inf_sup(func_inf_sup, v, 0, size - 1, &swaps, &comps);

        if (!test_sort(v, size)) {
          printf("%s failed to sort an array with %i elements", sortname, size);
          return 0;
        }
        if(strcmp(order_type[k], "randomized")) r = false;

      }
      if(r){
        delta /= 5;
        swaps /= 5;
        comps /= 5;
      }

      free(v);

      printf("%s sorted an %s array with %i elements in %f seconds with %lli "
             "comparisons and %lli swaps\n",
             order_type[k], sortname, size, delta, comps, swaps);

      fprintf(data, "%s, %i, %f, %lli, %lli\n", order_type[k], size, delta,
              comps, swaps);
    }
    printf("\n\n");
  }
  fclose(data);
}
