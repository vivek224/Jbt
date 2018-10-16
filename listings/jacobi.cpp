
for(int i=0; i<iterations; ++i) {
  for(int y=1; y<(n-1); ++y) {
    for(int x=(y*n)+1; x<(y*n) + n-1; ++x) {
      dest[x]=(src[x-n]+src[x+n]+src[x]+src[x-1]+src[x+1])*0.2;
    }
  }
  std::swap(dest, src);
 }
