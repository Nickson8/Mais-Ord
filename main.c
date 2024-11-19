/* #include "../../Alg1/FILA_ENCADEADA/fila.h" */
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

void swap(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// An optimized version of Bubble Sort
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

    // If no two elements were swapped by inner loop,
    // then break

    if (swapped == false)
      break;
  }
}

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

int medianaDeTres(int v[], int ini, int fim) {
  int a=v[ini], b=v[fim], c=v[(ini+fim)/2];
  if ((a > b && a < c) || (a > c && a < b))
      return a;
  else if ((b > a && b < c) || (b > c && b < a))
      return b;
  else
      return c;
}
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

void merge_sort(int v[], int ini, int fim, long long int *swaps,
                long long int *comps) {
  int meio = (ini + fim) / 2;
  if (ini < fim) { // existe mais de 1 elemento
    merge_sort(v, ini, meio, swaps, comps);
    merge_sort(v, meio + 1, fim, swaps, comps);
    intercala(v, ini, meio, fim, swaps, comps);
  }
}

int digito(int n, int m) {
  for (int i = 0; i < m; i++) {
    n = n / 10;
  }

  return n % 10;
}

/* void radix_sort(int v[], int tam) { */
/**/
/*   FILA *f[10]; */
/**/
/*   for (int i = 0; i < 10; i++) { */
/*     f[i] = fila_criar(); */
/*   } */
/**/
/*   int maior = -999999; */
/*   for (int i = 0; i < tam; i++) { */
/*     if (v[i] > maior) */
/*       maior = v[i]; */
/*   } */
/**/
/*   int m = 1; */
/*   while (maior / 10 != 0) { */
/*     m++; */
/*     maior /= 10; */
/*   } */
/**/
/*   int k; */
/*   for (int j = 0; j < m; j++) { */
/*     for (int i = 0; i < tam; i++) { */
/*       fila_inserir(f[digito(v[i], m)], v[i]); */
/*     } */
/**/
/*     k = 0; */
/*     for (int i = 0; i < tam; i++) { */
/*       while (!fila_vazia(f[i])) */
/*         v[k++] = fila_remover(f[i]); */
/*     } */
/*   } */
/* } */

// contagem de menores
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

void new_and_improved_radix_sort(int v[], int tam, long long int *swaps,
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

float sort_eval_tam(void (*sort_func_tam)(int *, int, long long int *,
                                          long long int *),
                    int v[], int tam, long long int *swaps,
                    long long int *comps) {
  clock_t start = clock();
  sort_func_tam(v, tam, swaps, comps);
  clock_t end = clock();

  return (((float)end - start)) / CLOCKS_PER_SEC;
}

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


/****************************************************************************************************** */
// Function to create directory if it doesn't exist
void create_directory(const char* dirname) {
    #ifdef _WIN32
        mkdir(dirname);
    #else
        mkdir(dirname, 0777);
    #endif
}

// Function to create full filepath with directory and prefix
char* create_filepath(const char* dir, const char* prefix, const char* suffix) {
    char* filepath = malloc(256 * sizeof(char)); // Allocate space for filepath
    if (filepath == NULL) return NULL;
    
    snprintf(filepath, 256, "%s/%s_%s", dir, prefix, suffix);
    return filepath;
}





void generate_sorting_metrics_csvs(void (*sort_func)(int*, int, long long int*, long long int*),
                                 const char* sort_name) {
    // Create directory for this sorting algorithm
    char dirname[100];
    snprintf(dirname, sizeof(dirname), "%s_metrics", sort_name);
    create_directory(dirname);
    
    // Create filepaths
    char* time_filepath = create_filepath(dirname, sort_name, "time_metrics.csv");
    char* swap_filepath = create_filepath(dirname, sort_name, "swap_metrics.csv");
    char* comp_filepath = create_filepath(dirname, sort_name, "comp_metrics.csv");
    
    if (!time_filepath || !swap_filepath || !comp_filepath) {
        printf("Error: Failed to create filepaths\n");
        return;
    }
    
    // Open the three CSV files
    FILE *time_file = fopen(time_filepath, "w");
    FILE *swap_file = fopen(swap_filepath, "w");
    FILE *comp_file = fopen(comp_filepath, "w");
    
    if (!time_file || !swap_file || !comp_file) {
        printf("Error: Failed to open one or more files\n");
        free(time_filepath);
        free(swap_filepath);
        free(comp_filepath);
        return;
    }
    
    // Write headers
    fprintf(time_file, "n,Ordered,Reversed,Randomized\n");
    fprintf(swap_file, "n,Ordered,Reversed,Randomized\n");
    fprintf(comp_file, "n,Ordered,Reversed,Randomized\n");
    
    // Test sizes from 1 to 100000
    for (int n = 1; n <= 30000; n+=200) {
        // Arrays to store metrics for each type
        float times[3] = {0};
        long long int swaps[3] = {0};
        long long int comps[3] = {0};
        
        // Test each array type (Ordered, Reversed, Randomized)
        for (int type = 0; type < 3; type++) {
            // Reset metrics for this test
            long long int curr_swaps = 0;
            long long int curr_comps = 0;
            float total_time = 0;
            
            // For randomized arrays, we'll take an average of 5 runs
            int num_trials = (type == 2) ? 5 : 1;
            
            for (int trial = 0; trial < num_trials; trial++) {
                // Generate array based on type
                int* arr;
                switch (type) {
                    case 0: // Ordered
                        arr = gerar_ordenado(n);
                        break;
                    case 1: // Reversed
                        arr = gerar_reverso(n);
                        break;
                    case 2: // Randomized
                        arr = gerar_aleatorio(n);
                        break;
                }
                
                // Measure sorting time
                clock_t start = clock();
                sort_func(arr, n, &curr_swaps, &curr_comps);
                clock_t end = clock();
                
                total_time += ((float)(end - start)) / CLOCKS_PER_SEC;
                
                // Verify sort was successful
                if (!test_sort(arr, n)) {
                    printf("Error: Sort failed for n=%d, type=%d\n", n, type);
                    free(arr);
                    continue;
                }
                
                free(arr);
            }
            
            // Calculate averages for randomized arrays
            times[type] = total_time / num_trials;
            swaps[type] = curr_swaps / num_trials;
            comps[type] = curr_comps / num_trials;
        }
        
        // Write metrics to respective files
        fprintf(time_file, "%d,%.6f,%.6f,%.6f\n", n, times[0], times[1], times[2]);
        fprintf(swap_file, "%d,%lld,%lld,%lld\n", n, swaps[0], swaps[1], swaps[2]);
        fprintf(comp_file, "%d,%lld,%lld,%lld\n", n, comps[0], comps[1], comps[2]);
        
        // Print progress update every 1000 iterations
        if (n % 1000 == 0) {
            printf("Processed n=%d\n", n);
        }
    }
    
    // Close files
    fclose(time_file);
    fclose(swap_file);
    fclose(comp_file);
    
    // Free allocated memory
    free(time_filepath);
    free(swap_filepath);
    free(comp_filepath);
    
    printf("Finished generating CSV files for %s in directory '%s':\n", sort_name, dirname);
    printf("1. %s_time_metrics.csv - Execution times\n", sort_name);
    printf("2. %s_swap_metrics.csv - Number of swaps\n", sort_name);
    printf("3. %s_comp_metrics.csv - Number of comparisons\n", sort_name);
}












void generate_sorting_metrics_csvs_if(void (*sort_func)(int*, int, int, long long int*, long long int*),
                                 const char* sort_name) {
    // Create directory for this sorting algorithm
    char dirname[100];
    snprintf(dirname, sizeof(dirname), "%s_metrics", sort_name);
    create_directory(dirname);
    
    // Create filepaths
    char* time_filepath = create_filepath(dirname, sort_name, "time_metrics.csv");
    char* swap_filepath = create_filepath(dirname, sort_name, "swap_metrics.csv");
    char* comp_filepath = create_filepath(dirname, sort_name, "comp_metrics.csv");
    
    if (!time_filepath || !swap_filepath || !comp_filepath) {
        printf("Error: Failed to create filepaths\n");
        return;
    }
    
    // Open the three CSV files
    FILE *time_file = fopen(time_filepath, "w");
    FILE *swap_file = fopen(swap_filepath, "w");
    FILE *comp_file = fopen(comp_filepath, "w");
    
    if (!time_file || !swap_file || !comp_file) {
        printf("Error: Failed to open one or more files\n");
        free(time_filepath);
        free(swap_filepath);
        free(comp_filepath);
        return;
    }
    
    // Write headers
    fprintf(time_file, "n,Ordered,Reversed,Randomized\n");
    fprintf(swap_file, "n,Ordered,Reversed,Randomized\n");
    fprintf(comp_file, "n,Ordered,Reversed,Randomized\n");
    
    // Test sizes from 1 to 100000
    for (int n = 1; n <= 30000; n+=200) {
        // Arrays to store metrics for each type
        float times[3] = {0};
        long long int swaps[3] = {0};
        long long int comps[3] = {0};
        
        // Test each array type (Ordered, Reversed, Randomized)
        for (int type = 0; type < 3; type++) {
            // Reset metrics for this test
            long long int curr_swaps = 0;
            long long int curr_comps = 0;
            float total_time = 0;
            
            // For randomized arrays, we'll take an average of 5 runs
            int num_trials = (type == 2) ? 5 : 1;
            
            for (int trial = 0; trial < num_trials; trial++) {
                // Generate array based on type
                int* arr;
                switch (type) {
                    case 0: // Ordered
                        arr = gerar_ordenado(n);
                        break;
                    case 1: // Reversed
                        arr = gerar_reverso(n);
                        break;
                    case 2: // Randomized
                        arr = gerar_aleatorio(n);
                        break;
                }
                
                // Measure sorting time
                clock_t start = clock();
                sort_func(arr, 0, n - 1, &curr_swaps, &curr_comps);
                clock_t end = clock();
                
                total_time += ((float)(end - start)) / CLOCKS_PER_SEC;
                
                // Verify sort was successful
                if (!test_sort(arr, n)) {
                    printf("Error: Sort failed for n=%d, type=%d\n", n, type);
                    free(arr);
                    continue;
                }
                
                free(arr);
            }
            
            // Calculate averages for randomized arrays
            times[type] = total_time / num_trials;
            swaps[type] = curr_swaps / num_trials;
            comps[type] = curr_comps / num_trials;
        }
        
        // Write metrics to respective files
        fprintf(time_file, "%d,%.6f,%.6f,%.6f\n", n, times[0], times[1], times[2]);
        fprintf(swap_file, "%d,%lld,%lld,%lld\n", n, swaps[0], swaps[1], swaps[2]);
        fprintf(comp_file, "%d,%lld,%lld,%lld\n", n, comps[0], comps[1], comps[2]);
        
        // Print progress update every 1000 iterations
        if (n % 1000 == 0) {
            printf("Processed n=%d\n", n);
        }
    }
    
    // Close files
    fclose(time_file);
    fclose(swap_file);
    fclose(comp_file);
    
    // Free allocated memory
    free(time_filepath);
    free(swap_filepath);
    free(comp_filepath);
    
    printf("Finished generating CSV files for %s in directory '%s':\n", sort_name, dirname);
    printf("1. %s_time_metrics.csv - Execution times\n", sort_name);
    printf("2. %s_swap_metrics.csv - Number of swaps\n", sort_name);
    printf("3. %s_comp_metrics.csv - Number of comparisons\n", sort_name);
}



/************************************************************************************************************************************************* */








int main(void) {
  void (*func_tam)(int *, int, long long int *, long long int *) = &bubbleSort;
  //void (*func_inf_sup)(int *, int, int, long long int *, long long int *) = &quick_sort;

  const char *sortname = "bubble_test";

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

  generate_sorting_metrics_csvs(&contagem_de_menores, "Counting");
}
