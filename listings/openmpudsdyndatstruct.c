typedef struct {int lb; int ub; int incr; int counter; looprecordt;
#pragma omp declare schedule(mydyn) init(mydynInit) next(mydynNext) fini(mydynFini)
void example() {
    loop_record_t lr;
#pragma omp parallel for schedule(mydyn:&lr:&lr:&lr)
    for (int i = 0; i < n; i++) a[i] = s * a[i] * b[i];
}
void mysdInit(int lb, int ub, int incr, int chunksz, loopRecordT * lr) {
    	lr->lb = lb;lr->ub = ub;lr->incr = incr; lr->chunks= chunksz; lr->counter = 0;
}
void mysdNext(int * lower, int * upper, loopRecordT * lr) {
    int start; if(lr->counter < (lr->ub - lr->lb)) {
    *lower = lr->fs*(lr->ub - lr->lb)*(tid/numThreads);
    *upper = *lower + lr->fs*(lr->ub - lr->lb)/numthreads;
     lr->counter += (*upper - *lower)/numThreads; 
}
else {
#pragma omp atomic capture
    {
        start = lr->counter;
        lr->counter += lr->chunksz * lr->incr;
    }
    *lower = start; *upper = start + lr->chunksz * lr->incr;
}
void mysd_fini(loop_record_t * lr) {}
#pragma omp declare schedule(mysd) init(mysd_init) next(mysd_next) fini(mysd_fini)
void example() { loop_record_t lr;
#pragma omp parallel for schedule(mysd:&lr:&lr:&lr)
    for (int i = 0; i < n; i++) a[i] = s * a[i] * b[i];
}
