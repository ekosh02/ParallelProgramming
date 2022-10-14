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

  int myRank;

  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  int a;
  int j = 0;
  int result;

  if (myRank % 2 == 0)
  {
    for (int i = 0; i < 10; i++)
    {
      a += myRank + (rand() % 100);
      printf("a += %d \n", a);
    }
    result = a / 10.;
    printf("myRank = %d ", myRank);
    printf("result %d \n", result);
  }

  MPI_Finalize();
  return 0;
}