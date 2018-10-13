void my_dyn_init(...) {}
void my_dyn_next(...) {}
#pragma omp declare schedule(my_dynamic) init(my_dyn_init) next(my_dyn_next) fini(my_dyn_fini)
void example() {
    static schedule_data sd; 
    int chunkSize = 4;
    #pragma omp parallel for schedule(my_dynamic:chunkSize,&sd)
    for(int i = 0; i < n; i++)
        c[i] = a[i]*b[i];
}
