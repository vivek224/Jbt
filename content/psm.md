
### Work on Application Code for X-ray Imaging at USC/ISI 

1. Performance assessment

- \small Computational requirements to calculate number of GPUs needed.
- \small Ensured that a dedicated network, similar to ESnet, doesn’t slow down computation: our application has unique requirements in that we need to stream the input data from data source to the supercomputer center.

2. Performance optimization.

- \small Ptychography code optimization: compiler flag optimization, loop unrolling, started work on half-precision instructions for NVIDIA Tesla P100.
- \small Tomography code optimization: discussed and worked on translating matlab code to C++ code, including working on numerical optimization.

3. Procurement of resources to set up experiments.

- \small Obtained machine resources from University of Southern California's High Performance Computing Center.
- \small Worked on proposal for Intel MICs to add to USC HPC system.


\end{frame}
