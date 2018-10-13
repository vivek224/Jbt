### Synergistic Load Balancing and Loop Scheduling

- So far, my work focused on within node load balancing
- Need to combine with across-node balancing
- Charm++ support across node load  balancing
- We extended Charm++’s loop scheduling mechanisms with my scheduling strategies

\end{frame}


### Load Balance Heat Maps for Lassen

\begin{figure}
\includegraphics[scale=0.5]{     } 
\end{figure}



### Load Balancing + Loop Scheduling Technique

\begin{columns}
\begin{column}{0.5\columnwidth}

- Modify across node load balancing in Charm++ to assign load to one PE in each node.
- Use my loop scheduling strategies (in CkLoop) to optimize within node performance.

\end{column}

\end{columns}







\end{frame} 
