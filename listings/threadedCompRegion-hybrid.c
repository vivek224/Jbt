double fs = get_env_var(STATIC_FRACTION);
#pragma omp parallel nowait
{
#pragma omp for
  for (int i = 0; i < fs*n; i++)
      c[i] += a[i]*b[i];
}

#pragma omp parallel
{
#pragma omp for schedule(dynamic)
  for (int i = fs*n; i < n; i++)
      c[i] += a[i]*b[i];
}
