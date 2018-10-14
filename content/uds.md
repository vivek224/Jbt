
### An Implementation of the Static/Dynamic Schedule with UDS

\begin{figure}
    \centering
    \lstinputlisting{listings/openmpudsdyndatstruct.c}
    \caption{Caption}
    \label{fig:my_label}
\end{figure}

\end{frame}

### Issues to Consider

1. Modifiers to clause: non-monotonic

 - Problem: How do we handle loop having indices that are non-monotonic?
 - Code example:
 - Solution: For the proposal, we restrict users to to use monotonic loops for now

2. How do schedules guarantee correct execution when a global variables are used?

- Problem:
- Code example:
- Solution we propose:

3. Compatibility with clause `concurrent`:

 - Problem: See e-mails from Xinmin et al on this, including definition of concurrent in the classical sense.
 - Code example showing problem:
 - Proposed Solution: can enforce that concurrent not be used with user-defined schedule.


\end{frame}
