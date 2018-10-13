
#pragma omp parallel for nowait
  for (int i = 0; i < n/2; i++)
      c[i] += a[i]*b[i];

#pragma omp parallel for schedule(dynamic)
  for (int i = n/2; i < n; i++)
      c[i] += a[i]*b[i];
