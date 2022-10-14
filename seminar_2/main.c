#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int errCode;

    if ((errCode = MPI_Init(&argc, &argv)) != 0)
    {
        return errCode;
    }
    int rank, size;
    int sum = 0, suma = 0, avg = 0, a, b, n;
    MPI_Status st;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand(rank);
    n = rand() % 10;
    int sum_n = n;
    int *arr = malloc(n * n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10;
        sum += arr[i];
    }
    int next = rank + 1;
    int prev = rank - 1;

    if (rank == size - 1)
    {
        next = 0;
    }
    if (rank == 0)
    {
        prev = size - 1;
        MPI_Send(&n, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Send(&sum, 1, MPI_INT, next, 1, MPI_COMM_WORLD);
        printf("rank %d %d %d \n", rank, n, sum);

        MPI_Recv(&a, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &st);
        MPI_Recv(&b, 1, MPI_INT, prev, 1, MPI_COMM_WORLD, &st);
        printf("%d %d  \n", sum_n, sum);
    }
    else
    {
        MPI_Recv(&a, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &st);
        MPI_Recv(&b, 1, MPI_INT, prev, 1, MPI_COMM_WORLD, &st);
        printf("rank %d %d %d \n", rank, n, sum);
        sum_n += a;
        sum += b;
        MPI_Send(&sum_n, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Send(&sum, 1, MPI_INT, next, 1, MPI_COMM_WORLD);
        printf("%d %d \n", sum_n, sum);
    }

    if (rank == size - 1)
    {

        printf("sum %d %d \n", sum, sum_n);
        printf("avg %d \n", sum / sum_n);
    }

    MPI_Finalize();

    return 0;
}