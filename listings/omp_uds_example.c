void myDynInit(...) {}
void myDynNext(...) {}
#pragma omp declare schedule(myDyn) init(myDynInit) next(myDynNext) fini(myDynFini)
void example() {
    static schedule_data sd; 
    int chunkSize = 4;
    #pragma omp parallel for schedule(myDyn:chunkSize,&sd)
    for(int i = 0; i < n; i++)
        c[i] = a[i]*b[i];
}
