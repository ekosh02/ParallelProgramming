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

    int const n = 10;
    int rank, size;
    MPI_Status st;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int ln = n / size;
    int arr[n * n], brr[n];
    int *a = malloc(ln * n * sizeof(int));

    int *sum1 = malloc(ln * sizeof(int));
    int sum2[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i * n + j] = rand() % 10;
            if (rank == 0)
            {
                printf("%d ", arr[i * n + j]);
            }
        }
        if (rank == 0)
        {
            printf("\n");
        }
    }
    if (rank == 0)
    {
        printf("\n");
    }
    for (int i = 0; i < 10; i++)
    {
        brr[i] = rand() % 10;
        if (rank == 0)
        {
            printf("brr[i] %d ", brr[i]);
        }
    }
    if (rank == 0)
    {
        printf("\n");
    }
    MPI_Scatter(arr, ln * n, MPI_INT, a, ln * n, MPI_INT, rank, MPI_COMM_WORLD);
    MPI_Bcast(brr, n, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = 0; i < ln; i++)
    {
        sum1[i] = 0;
        for (int j = 0; j < n; j++)
        {

            sum1[i] += a[i * n + j] * brr[j];
        }
        printf("rank %d sumJ %d \n", rank, sum1[i]);
    }

    MPI_Gather(sum1, ln, MPI_INT, sum2, ln, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        for (int i = 0; i < n; i++)
        {
            printf("sum %d  %d \n", rank, sum2[i]);
        }
    }
    MPI_Finalize();

    return 0;
}