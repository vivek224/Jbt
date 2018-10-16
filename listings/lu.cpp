for(int i=0; i<size; i++) {
  for(int j=i+1; j<size; j++) {
    A[j*size+i] /= A[i*size+i];
    for(int k=i+1; k<size; k++) {
      A[j*size+k] -= A[j*size+i] * A[i*size+k];
    }
  }
 }
