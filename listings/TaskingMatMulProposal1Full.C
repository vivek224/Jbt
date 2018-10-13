#define M 256
#define N 1024
#define P 256
void matmul(int** A, int ** B, int **C) {
#pragma omp taskloop workshare(i,4) asp(C:writeshared,i\%4) 
asp(A[0:P]:readshared) asp(B[0:N/4]:readprivate)
for (i = 0; i < M; i++)
  for (j = 0; j < N; j++)
    for (k = 0; k < P; k++)
       C[i][j] += A[i][k] * B[k][j];
}