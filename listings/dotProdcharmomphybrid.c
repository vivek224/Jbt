
#include "dotProd.decl.h"
#include "charm++.h"
#include <omp.h>

class Main : public CBase_Main {
public:
  CProxy_Elem vChunks;
  Main(CkArgMsg* msg) {
  omp_set_num_threads(omp_get_max_threads());
#pragma omp parallel
  {
    numThreads = omp_get_num_threads();
    if(numThreads <= 1)
      {
	printf("Number of threads is %d. Resetting a number greater than 1. \n", numThreads);
	omp_set_num_threads(DEFAULT_NUM_THREADS);
      }
    printf("Number of threads running on is: %d .\n", numThreads);
  }
  CProxy_rank0BlockMap myMap = CProxy_rank0BlockMap::ckNew();
  CkArrayOptions opts(numElemsPerNode*CkNumNodes());
  opts.setMap(myMap);
  vChunks = CProxy_Elem::ckNew(thisProxy, opts);
  int ind2 = CkIndex_Main::initializeStructures();
  CkStartQD(ind2, &thishandle); // Quiescience detection.                     
}
void doTests(){vChunks.doDotProduct();}
void initializeStructures(){vChunks.doInitVectors(); int ind = CkIndex_Main::doTests(); CkStartQD(ind, &thishandle); } // Quiescience detection.                                                                                                                        
void printResult(float result) {
  iter--;
  warm_up--;
  if (warm_up == 0) {
    t1 = CkWallTimer();
    CkPrintf("[main] Started wallclock timer\n");
  }
  if(iter == 0)
    {
      double t2 = CkWallTimer();
      float errorPercent = fabs( 100.0* (result - 6.00*probSize*CkNumNodes())/result );
      if ( errorPercent > 0.1)
	CkPrintf("result %f is wrong. shd be: %f\n", result, (6.0*probSize*CkNumNodes()));
      CkExit();
    }
  else
    vChunks.doDotProduct();
}
};

class Elem : public CBase_Elem {
public:
  float *a, *b;
  LoopHistory* lh;
  CProxy_Main mainProxy;
  Elem(CProxy_Main _mainProxy) {
    int value = thisIndex;
    // CkPrintf("DEBUG: Elem constructor %d on PE: %d \n", thisIndex, CkMyPe());
    mainProxy = _mainProxy;
    a = new float[probSize/numElemsPerNode]; // Each array on a node is of the size total problem size divided by number of chares per PE.                
    b = new float[probSize/numElemsPerNode];
    // TODO: Figure out what to do here. How do we create a loop history variable for Charm++ + OpenMP? Can we use the loop history from MPI+OpenMP?
    //lh = new LoopHistory(staticFraction); // Use static fraction provided by command-line parameter.
  }

  void doInitVectors()
  {
    float* params[2]; // Used for parameters to be passed to initVectors.                         
    params[0] = a;
    params[1] = b;
    int numberOfChunks= (probSize/numElemsPerNode)/chunkSize;
#ifdef OMP_HYBRID
    float r =0.0;
#pragma omp parallel
    {
#pragma omp for
      for(int i=0; i < (int) (ceil) (probSize/numElemsPerNode); i++)
	{
	  a[i] = 2.0;
	  b[i] = 3.0;
	}
    }
  }
}

void doDotProduct()
{
  float r;
  int numberOfChunks= (probSize/numElemsPerNode)/chunkSize;
#pragma omp parallel
  {
    if(omp_get_thread_num() == 0)
      printf("OpenMP implementation: Doing computation: The number of threads is %d\n", omp_get_num_threads());
#pragma omp for nowait reduction(+:r)
    for(int i=0; i < (int) (ceil((staticFraction*(probSize/numElemsPerNode)))); i++)
      r = r + a[i]*b[i];
#pragma omp for schedule(dynamic,chunkSize) reduction(+:r) // The clause reduction is a hint to LLVM OpenMP to optimize the code for reduct\ion operation.
    for(int i=(int) ((floor) (staticFraction*(probSize/numElemsPerNode))); i< (int) (probSize/numElemsPerNode); i++)
      r = r + a[i]*b[i];
  }
  // TODO: figure out what to do here. Is this needed only for Charm++ and CkLoop ? 
  CkCallback cb(CkReductionTarget(Main, printResult), mainProxy);
  contribute(sizeof(float), &r, CkReduction::sum_float, cb);
}

Elem(CkMigrateMessage*){}

float dotP(){
  float x = 0;
  for(int i=0; i<probSize/numElemsPerNode; i++)
    {
      x += a[i]*b[i];
    }
  return x;
}

};

class rank0BlockMap : public CkArrayMap
{
public:
  rank0BlockMap(void) {}
  rank0BlockMap(CkMigrateMessage *m){}
  int registerArray(CkArrayIndex& numElements,CkArrayID aid) {
    return 0;
  }
  // Assign chares to rank 0 of each process.                                                                                                                                                                                        
  int procNum(int /*arrayHdl*/, const CkArrayIndex &idx) {
    int elem=*(int *)idx.data();
    int charesPerNode = numElemsPerNode;
    int nodeNum = (elem/(charesPerNode));
    int numPEsPerNode = CkNumPes()/CkNumNodes();
    int penum = nodeNum*numPEsPerNode;
    return penum;
  }
};

#include "dotProd.def.h"