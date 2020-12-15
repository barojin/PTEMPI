#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <mpi.h>
 
#define N 26
int* run_in_parallel(int array[], int sum, int level, int argc, char *argv[]);
int* func(int numbers[], int sum, int level, int argc, char *argv[]);
int* func2(int numbers[], int sum, int level);

int main(int argc, char *argv[]) 
{
    FILE *fp;
    int* a;
    fp = fopen("cpi.out", "w+");
    int numbers[N]; 
    
    int i;
    for (i = 0; i < N; ++i){
        numbers[i] = i;
    }

    a = func(numbers, 0, 0, argc, argv);
    
    int j = 0;
    for(int i = 0; i < 10; i++){
        if (a[j] != i){
            fprintf(fp, "%d ", i);
        }
        else{
            j++;
        }
    }

   fclose(fp);
   return 0;
}

int* func(int numbers[], int sum, int level, int argc, char *argv[]) {
    if (level == 9){
        return run_in_parallel(numbers, sum, level, argc, argv);
    }
    else if(sum >= 0){
        int n = N - level;
        int i;
        for (i = n - 1; i >= 0; --i){
            int num = numbers[i];    
            int newNumbers[n-1]; // initilize new numbers array
            int k = 0;
            int j;
            for (j = 0; j < n; ++j){
                if (numbers[j] != num){
                    newNumbers[k] = numbers[j];
                    k++;
                } 
            }
            
            if (level < 6){
                return func(newNumbers, sum + num * num, level + 1, argc, argv);
            }else{
                return func(newNumbers, sum - num * num, level + 1, argc, argv);
            }
             
        }
    }
}

int* func2(int numbers[], int sum, int level) {
    if (level == 12){
        if (sum == 0){
            return numbers;
        }
    }
    else if(sum >= 0){
        int n = N - level;
        int i;
        for (i = n - 1; i >= 0; --i){
            int num = numbers[i];    
            int newNumbers[n-1]; 
            int k = 0;
            int j;
            for (j = 0; j < n; ++j){
                if (numbers[j] != num){
                    newNumbers[k] = numbers[j];
                    k++;
                } 
            }
            return func2(newNumbers, sum - num * num, level + 1);
        }
    }
}

int* run_in_parallel(int array[], int sum, int level, int argc, char *argv[]){
    int pid, np, ierr;
    int *res;
    MPI_Status status; 
    double s_time, e_time;
  
    ierr = MPI_Init(&argc, &argv); 
    s_time = MPI_Wtime();
    
    if (ierr != 0){
        printf("MPI_Init error\n");
        exit(1);
    }
  
    MPI_Comm_rank(MPI_COMM_WORLD, &pid); 
    MPI_Comm_size(MPI_COMM_WORLD, &np); 

    // each process do their jobs
    res = func2(array, sum, level);
    
    MPI_Barrier(MPI_COMM_WORLD);
    e_time = MPI_Wtime();
    //printf("It takes %.6f time\n", e_time - s_time);
    MPI_Finalize();
    return res;
}
