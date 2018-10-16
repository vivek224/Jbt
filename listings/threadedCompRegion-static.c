#pragma omp parallel for schedule(static)
   for(int i=0; i<n; i++)
      c[i] += a[i]*b[i];
