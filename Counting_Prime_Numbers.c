#include <stdio.h>
#include <string.h>
#include "mpi.h"
#include <math.h>

int Is_Prime(int num) {
    if (num <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int my_rank; /* rank of process */
    int p;       /* number of process */
    int source;  /* rank of sender */
    int dest;    /* rank of receiver */
    int tag = 0; /* tag for messages */
    int x, y;
    int totalCount = 0;
    int subCount = 0;
    MPI_Status status; /* return status for */

    /* Start up MPI */
    MPI_Init(&argc, &argv);
    /* Find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    /* Find out number of process */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (my_rank == 0) {
        /* Master Process */
        printf("Enter lower bound: ");
        scanf("%d", &x);
        printf("Enter upper bound: ");
        scanf("%d", &y);

        int r = (y - x) / p;
        int rem = (y - x) % p;

        // Broadcast x and r to each slave process
        for (dest = 1; dest < p; ++dest) {
            MPI_Send(&x, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
            MPI_Send(&r, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
            if(dest == p-1)
            {
                MPI_Send(&rem, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
            }
            //x += r; // Adjust x for the next process
        }

        // Calculate primes for the master process
        

        // Receive sub count from each slave process
        for (source = 1; source < p; ++source) {
            MPI_Recv(&subCount, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            totalCount += subCount;
            printf("Total number of prime numbers##### is: %d %d\n", source , totalCount);
        }

        printf("Total number of prime numbers is: %d\n", totalCount);
    } else {
        /* Slave Process */
        int r;
        MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&r, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int a = x + (my_rank - 1) * r; //   
        int b = a + (r *(my_rank)) -1; 
        if(my_rank==p-1) {
            int rem;
            MPI_Recv(&rem, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            b += rem;
        }

        for (int j = a; j <= b; ++j) {
            if (Is_Prime(j)) {
                subCount++;
            }
        }

        MPI_Send(&subCount, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Total number of prime numbers && is: %d\n", subCount);
    }

    /* shutdown MPI */
    MPI_Finalize();
    return 0;
}
