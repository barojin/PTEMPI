# PTEMPI
Implemented MPI parallel program parallelizing the operation between 16 threads on a computer cluster and compared the performance of O(2^n) computation on single laptop with on cluster computers. [C, Message Passing Interface library]

## constraints
The power of variable is 2.<br>
The numbers in the range of [0, 25].<br>
This code is executable on computer cluster.<br>
16 tasks are allowed in parallel.<br>

## Run
```
mpicc cpi.c -o cpi  
sbatch runAssignment1.sbatch  
```

## Debug
The command 'sqeue' shows the list of id of jobs running on the server.<br>
The command 'scancel [id num]' to kill the task.<br>
