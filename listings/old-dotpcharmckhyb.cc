#include "charm++.h"
#include "CkLoopAPI.h"
void doDotProduct()
{
  float r = 0.0; int numberOfChunks= (probSize/numElems)/chunkSize;
  float* params[2]; params[0] = a; params[1] = b;
  CkLoop_ParallelizeHybrid(lh, dotP_chunked, 2, params, numberOfChunks, 0, (probSize/numElems), 1, &r, CKLOOP_FLOAT_SUM);
  CkCallback cb(CkReductionTarget(Main, printResult), mainProxy);
  contribute(sizeof(float), &r, CkReduction::sum_float, cb);
}
extern "C" void dotP_chunked(int start, int end, void* result, int numParams, void* params)
{
  float** z = (float**) params; float* v1 = z[0];  float* v2 = z[1];
  float x = 0.0;for(int i=start; i<end; i++) x += a[i]*b[i]; * ((double**)result) = x; 
}
class rank0BlockMap : public CkArrayMap
{
public:
  rank0BlockMap(void) {}
  rank0BlockMap(CkMigrateMessage *m){}
  int registerArray(CkArrayIndex& numElements,CkArrayID aid){return 0;}
  int procNum(int /*arrayHdl*/, const CkArrayIndex &idx) {
    int elem=*(int *)idx.data(); int charesPerNode = numElemsPerNode;
    int nodeNum = (elem/(charesPerNode)); int numPEsPerNode = CkNumPes()/CkNumNodes();
    int penum = nodeNum*numPEsPerNode; return penum;
  }
};
