

### Synergistic Load Balancing and Loop Scheduling

- So far, my work focused on within node load balancing
- Need to combine with across-node balancing
- Charm++ support across node load  balancing
- We extended Charm++’s loop scheduling mechanisms with my scheduling strategies

\end{frame}


### An Intelligent Runtime System for Clusters of SMPs

- An adaptive runtime system like Charm++ intelligently balances computational work periodically.
- Two issues exist when using a basic Charm++ scheduling scheme.    
  1. Challenge of the cost of over-decomposition.
  2. Challenge and opportunity to exploit multi-core nodes to mitigate imbalance.
  
- We can address both challenges by:
  1. Having Charm++'s load balancer assign Charm++ objects, i.e., chares, to nodes.% (instead of cores).
  2. Using loop parallelism to distribute work within a node.

%  \begin{figure}
%    \begin{center}
%      \includegraphics[width=0.75\columnwidth]{./images/CharmLdbWithLoop-manyChares}
%      \includegraphics[width=0.75\columnwidth]{./images/CharmLdbWithLoop-fewChares}
%      \label{fig:charmcklooptimeline}
%    \end{center}
%    \caption{\label{fig:charmcklooptimeline}\small Timelines using Charm++-only for default (left) and a mode where the number of chares per node is reduced (right)}
%  \end{figure}

\end{frame}


### Charm++ 

%\begin{figure}[ht!]
% \label{fig:charmBeforeAndAfterLdBCkLoop}
%  \begin{center}
    %\includegraphics[width=.8\columnwidth]{images/charmLdbWithLoopwCharmonly-unbalanced}
    %\includegraphics[width=.8\columnwidth]{images/charmLdbWithLoopwCharmonly-balanced}
%  \end{center}
%  \caption{\label{fig:charmBeforeAndAfterLdBCkLoop} \small Timelines for execution of a code without (left) and with (right) Charm++ load balancing.}
  % A green rectangle on a non-zero core on a node corresponds to loop iterations spawned from core 0.
%\end{figure}

\end{frame}


### Load Balancing and Loop Scheduling Technique

- Modify across node load balancing in Charm++ to assign load to one PE in each node.
- Use my loop scheduling strategies in CkLoop to optimize within node performance.

\end{frame}


### Key Idea of Our Solution

1. Modify Charm++ RTS to assign chares to core 0 of each node only.
2. Reduce the number of chares per PE.
3. Adjust parameters of within-node loop scheduler,e.g., vary dynamic fraction, based on parameters of Charm++.
4. Tune Charm++ RTS parameters to work with adjustments of within-node loop scheduling.

  %\begin{figure}
  %  \label{fig:statDynSched}
  %  \begin{center}
          %\subfloat[\tiny Static Scheduling.]{\includegraphics[width=.20\columnwidth]{./images/threadedCompRegion-static-withChare}}\hspace*{0.1in}
          %\subfloat[\tiny Dynamic Scheduling.]{\includegraphics[width=.27\columnwidth]{./images/threadedCompRegion-dynamic-withChare}}\hspace*{0.1in}
          %\subfloat[\tiny Mixed Scheduling]{\includegraphics[width=.24\columnwidth]{images/threadedCompRegion-hybrid-withChare}}
 %   \end{center}
 %   \caption{\label{fig:statDynSched} \tiny Mixed static/dynamic scheduling within a chare, i.e., Charm++ object.}
 % \end{figure}

\end{frame}


### Baseline Results and Analysis: Existence of Within-node Load Imbalance through Heat Maps

\begin{figure}[ht!]
\begin{center}
{\includegraphics[width=.25\columnwidth]{images/nolb_node_load_with_iter}}
{\includegraphics[width=0.25\columnwidth]{plots/greedylb_node_load_with_iter__2_.pdf}}\\
{\includegraphics[width=0.25\columnwidth]{images/nolb_pe_load_with_iter}}
{\includegraphics[width=0.25\columnwidth]{plots/greedylb_pe_load_with_iter}}
\end{center}
\caption{\label{fig:motexample2} \footnotesize Load imbalances across nodes (left) and across cores (right) when the greedy load balancing strategy is used.}
\end{figure}

- \tiny Using no load balancing, node 2 is heavily overloaded for iterations 8 and 9. Hence, we need load balancing to distribute the load across nodes.
- \tiny Inter-node load balancing using GreedyLB balances load across nodes well.
- \tiny Balancing load across nodes using GreedyLB still leaves load imbalance in the cores within a node.

\end{frame}


### Additional Baseline Results

\begin{figure}
 \label{fig:addbr}
    \centering
  \includegraphics[scale=0.3]{plots/additionalBaselineResults.png}
  \caption{\label{fig:addbr}Baseline Results for Lassen Using Charm++ + OpenMP implementation shown in the middle.}
\end{figure}

\end{frame}


### Proposed Set of Techniques
  
1. We decide on the combinations of advanced loop scheduling and advanced load balancing strategies to use.
2. We either experimentally tune or use an automated technique to adjust parameters of load balancing and loop scheduler together to improve performance of application.
3. We then consider advanced load balancing and loop scheduling strategies that can help for the combined load balancing and loop scheduling technique.

\end{frame}


### Performance Model for Load Balancing and Loop Scheduling

 \begin{table}[h!t]
              \centering
              \label{tab:pmta}
              \begin{tabular}{|l|l|}
                \hline
                \tiny$t_1$    & \tiny Duration of a loop iteration\\ %iteration on one core \\
                \hline
                \tiny$T_p$    & \begin{tabular}[c]{@{}l@{}}\tiny Total execution time of a threaded computation region\vspace*{-0.3in} \\ \tiny consisting of $N$ loop \iterations on $p$ cores\end{tabular} \\ \hline
%             \tiny$q$      & \tiny Scheduler's dequeue overhead of a loop iteration                                                                 \
\\ \hline
                  %             \tiny$d$  & \tiny Time for executing an iteration dynamically
                  \\ \hline
                  \tiny$\delta$ & \tiny Expected cost of load imbalance on a node to the application                                         \\ \hline
                  \tiny$load_i$ & \tiny Load on the $i^{th}$ core of a node on an arbitrary timestep                             \\ \hline
              \end{tabular}
              \caption{\label{tab:pmta} \tiny Terms in implementation}
   \end{table}
          
\end{frame}


### Adaptive Loop Scheduling 

- We refer to this scheduling strategy as \emph{adaptive loop scheduling} and use a parametrized version of it to schedule loop iterations of a chare to cores.
- The best-performing collection of scheduler parameter values is the best-performing one, on average, for each chare. An optimal collection of scheduler parameter values, in isolation, isn't necessarily the best-performing, given an arbitrary collection of parameter values for the load balancer.
- Thus, our technique is to search for the collection of parameter values for the scheduler together with those for the load balancer that obtains best performance.

\end{frame}


\begin{frame}{Implementation}{Front-end Code}

\begin{figure}
\label{code:dotpCharmckhyb}
\lstinputlisting{./listings/old-dotpcharmckhyb.cc}\hspace*{-1.9in}
\vspace*{-0.8in}\caption{\label{code:dotPCharmckhyb}{\tiny  \label{code:dotpCharmckhyb} Dot product code's modification using Charm++ with CkLoop.}}
\end{figure}

- Figure~\ref{code:dotpcharmckhyb} shows the user code with the adapted CkLoop library using the function {\tt CkParLoop()} for the computational region of the program.
- The user creates a kernel for the computation region and replaces the region with a call to {\tt CkParLoop()} having the name of the kernel for the computa
tion region as a parameter to the function.
- Here, the user calls the function on thread 0 providing the kernel to be called, the range of iterations of the loop and the number of chunks used in the loop.
- The user specifies a loop history variable that has a field for the static fraction within it.
- The lines of code in the user code with the library is 3\% more than the original user code.

\end{frame}


### Results

    \begin{figure}[ht!]
          \begin{center}
         \subfloat[\tiny Dot Product on 4 nodes of Stampede.]{\includegraphics[width=.45\columnwidth]{plots/dotProd-4nodes-bw}}
 	    \subfloat[\tiny Particle-in-Cell on 4 nodes of Blue Waters.]{\includegraphics[width=.45\columnwidth]{plots/PIC-4nodes-bw}}
          \end{center}
          \caption{\tiny Execution times of scientific applications on multi-core clusters.}
	  \label{fig:scalability-results-PIC-BW}
	  \end{figure}

- For dot product using 64 chares, a static fraction of 75\% with a chunk size of 8 gives the best performance, showing utility of adaptive loop scheduling.
- PIC using modified inter-node load balancing with adaptive loop scheduling is 19.13\% faster than PIC using adaptive scheduling without load balancing.
- Synergistic performance improvements using combination of inter-node and intra-node load balancing.


\end{frame}



### Related Work: Combining Load Balancing and Loop Scheduling

- Habanero\cite{Habanero}: library with support for data locality within node
- MPI+OpenMP\cite{MPIOpenMP}: basic hybrid parallel programming model.
- OmpSS\cite{ompss}: library for extensible loop scheduling schemes.

\end{frame}



### Load Balancing and Loop Scheduling: Conclusion 

- Connection to ParaDis.
- Need sophisticated loop scheduling in Charm++. 
- Described a technique and implementation to improve performance of applications.
- Using our technique and implementation, we demonstrate performance improvement of 17.2%.
- For future work, we'll explore other adjustments to parameters of the Charm++ RTS to facilitate for loop scheduling. 
- Considering a proposal with Harshitha Menon from LLNL in the last the months for new strategies and sophisticated implementation.

\end{frame} 