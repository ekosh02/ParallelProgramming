#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  // 48
  int errCode;

  if ((errCode = MPI_Init(&argc, &argv)) != 0)
  {
    return errCode;
  }

  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int k = size + 5;
  int *set_k = malloc(sizeof(int) * k);
  int *reduction_result = malloc(sizeof(int) * k);
  int sum2 = 0;
  int root_rank = 1;

  if (size != 4)
  {
    printf("size != 4\n");
    MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
  }

  if (rank == root_rank)
  {
    printf("size - %d \n", size);
    printf("set_k - %d \n", sizeof(set_k));
  }
  int sum = 0;
  for (int i = 0; i < k; i++)
  {
    set_k[i] = rand() % 5;
    sum += set_k[i];
    printf("%d %d \n", rank, set_k[i]);
  }

  MPI_Reduce(set_k, reduction_result, k, MPI_INT, MPI_SUM, root_rank, MPI_COMM_WORLD);
  if (rank == root_rank)
  {
    for (int i = 0; i < k; i++)
    {
      printf("%d \n", reduction_result[i]);
    }
  }

  MPI_Finalize();
  return 0;
}