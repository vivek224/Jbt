#pragma omp parallel 
{
#pragma omp for schedule(dynamic)
  for (int i=0; i<n; i++)
    c[i] += a[i]*b[i];
}
