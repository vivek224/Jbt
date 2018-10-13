\section{Data Locality for OpenMP Tasking}
\begin{frame}[label=motivationdlts]{Motivation}
\begin{itemize}
\item  In an OpenMP application in which work is scheduled to threads dynamically, \underline{data locality} is important for efficient execution of the application.
\item Using the clause {\tt affinity} for task scheduling proposed for OpenMP 5.0 can improve data locality~\cite{ompaffclause}.
\item However, strategies for tasking are fixed by OpenMP's runtime system, even with hints to the affinity clause.
\item One can argue that this small set of strategies isn’t beneficial for all application-architecture pairs~\cite{worksteal99, Kulkarni08schedulingstrategies}. \nocite{Olivier:2012:CMW:2388996.2389085}
\end{itemize} 
\end{frame}

\begin{frame}[label=posssoldlts]{A Possible Solution}
\begin{itemize}
\item OpenMP needs an adequate amount of support to maintain high levels of data locality when scheduling tasks to threads.
\item Specifically, we need task-to-thread affinity in OpenMP to reduce
\begin{enumerate} 
\item capacity cache misses on a multi-core node, or \textit{locality-awareness}, and 
\item coherence cache misses on a multi-core node, or \textit{locality-sensitivity}.
\end{enumerate}
\item We need to provide more hints to OpenMP's runtime for assigning OpenMP's tasks to threads in a way that preserves data locality.
\end{itemize}

\end{frame} 




\begin{frame}[label=contributiondlts]{Contribution} 
\begin{itemize} 
 \item Our solution builds on the {\tt affinity} clause for OpenMP 5.0~\cite{OpenMP} $\rightarrow$ the user provides input to the clause as hints on
\begin{enumerate} 
\small \item \small \textit{what} data needs to be localized
\item \small the \textit{degree} to which the data should be localized
\end{enumerate}
\item Prior work on the degree to which the data should be localized has been shown to improve performance~\cite{dynwork}.
\item \underline{\textit{Contribution}}: the addition of constructs to OpenMP that provides and allow for a rich set of task scheduling schemes having (a) locality-awareness or (b) locality-sensitivity.
\item This work develops ideas of (a) for the affinity clause, and building on (b) from previous work for the affinity clause.
\end{itemize}
\end{frame}


\section{Data Scheduling}
\begin{frame}{Scheduling Data Access}
\begin{itemize}
    \item OpenMP lacks a mechanism for allowing the thread identifier to affect the scheduling of inner loops (when this is legal)
    \item Here we show two examples of how such mechanism can be used
    \item Benefits: Improve execution time, energy consumption and make better usage of available bandwidth
    \item We show the results of some preliminary experiments conducted to show the benefits of the proposed directive
\end{itemize}
\end{frame}

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