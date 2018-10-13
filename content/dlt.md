% \begin{frame}[label=exj2d]{Example: Jacobi 2D Stencil Loop Shift}

### {Example: Jacobi 2D Stencil Loop Shift}
\footnotesize{
\begin{itemize}
    \item Second example: Jacobi-2D
    \item Shift loop-i w.r.t to thread number
    \item Effect: Ideally, user-provided mapping function should attempt to reuse the data already brought into cache by the thread
\end{itemize}
}
\begin{minipage}{0.43\textwidth}
```C, caption=\footnotesize{Jacobi Stencil LoopShift Semantics}
for (t = 0; t < TSTEPS; t++) {
 #pragma omp parallel
 {
  int ii;
  #pragma omp for private (j)
  for (ii = 1; ii < n-1; ii++) {
   int tid = omp_get_thread_num ();
   int i = (tid + ii) % (n-2) + 1;
   for (j = 1; j < n-1; j++)
    ref(B,i,j) = 0.2 * (
     ref(A,i,j) + ref(A,i-1,j) +
     ref(A,i+1,j) + ref(A,i,j-1) + 
     ref(A,i,j+1));
  }
 }
 /* pointer swap */
 temp = B; B = A; A = temp;
}
```
\end{minipage}
\hspace{0.5cm}
\begin{minipage}{0.48\textwidth}
```C, caption=\footnotesize{Jacobi Stencil LoopShift Directive}
for (t = 0; t < TSTEPS; t++) {
 #pragma omp parallel
 {
  // Assume tid is an ICV
  #pragma omp for private (j) \ 
    loopshift(i=(tid+ii)%(n-2)+1)
  for (int ii = 1; ii < n-1; ii++) {
   for (j = 1; j < n-1; j++)
    ref(B,i,j) = 0.2 * (
     ref(A,i,j) + ref(A,i-1,j) +
     ref(A,i+1,j) + ref(A,i,j-1) + 
     ref(A,i,j+1));
  }
 }
 /* pointer swap */
 temp = B; B = A; A = temp;
}
```
\end{minipage}
\end{frame}



\begin{frame}[label=dltsconclusions]{Conclusions}

1. \small Need mechanism to enable locality-aware and data-oriented task and thread scheduling in OpenMP 5.0 

2. \small Propose clause ```affinity``` and through using parameters and hints to the clause; propose ```loopshift```
directive to affect inner worksharing loops

3. Propose new types of  hints  for  locality-aware  task  scheduling’s  clause ```affinity``` that  specify
    - \footnotesize what data  should  be  associated  with  a  particular  thread,  or  privatized  
    - \footnotesize the degree to which that data should be privatized. 
    
4. We believe that such support in OpenMP  will improve  performance of many OpenMP application codes on current and future architectures. 
5. We’ll take feedback to add the ideas to OpenMP version 5.1 or a version of OpenMP immediately succeeding OpenMP version 5.1.

6. Please email Martin Kong or I with questions and inquiries.

\end{frame}