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