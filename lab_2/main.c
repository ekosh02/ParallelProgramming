#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

const int SLOTS_COUNT = 4;

int main(int argc, char *argv[])
{

  int errCode;

  if ((errCode = MPI_Init(&argc, &argv)) != 0)
  {
    return errCode;
  }

  int rank, size, a, b, c, d;
  MPI_Status st;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  srand(rank);
  a = rand() % 10 + rank;
  b = rand() % 10 + rank;
  int next = rank + 1;
  int prev = rank - 1;

  if (rank == size - 1)
  {
    next = 0;
  }
  if (rank == 0)
  {

    prev = size - 1;
    MPI_Send(&a, 1, MPI_INT, prev, 0, MPI_COMM_WORLD);
    MPI_Send(&b, 1, MPI_INT, next, 1, MPI_COMM_WORLD);
    printf("in  rank %d %d %d \n", rank, a, b);
    MPI_Recv(&c, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &st);
    MPI_Recv(&d, 1, MPI_INT, prev, 1, MPI_COMM_WORLD, &st);
    printf("out rank %d %d %d \n", rank, c, d);
  }
  else
  {
    MPI_Send(&a, 1, MPI_INT, prev, 0, MPI_COMM_WORLD);
    MPI_Send(&b, 1, MPI_INT, next, 1, MPI_COMM_WORLD);
    printf("in  rank %d %d %d \n", rank, a, b);
    MPI_Recv(&c, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &st);
    MPI_Recv(&d, 1, MPI_INT, prev, 1, MPI_COMM_WORLD, &st);
    printf("out rank %d %d %d \n", rank, c, d);
  }
  MPI_Finalize();

  return 0;
}
