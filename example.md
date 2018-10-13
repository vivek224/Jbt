# How 

### We can do that?

* Yeah to some extent, with \texttt{markdown} package :-)
    - __$\hash$__ and __$\hash\hash$__ for section and subsection headers (in ToC)
    - Redefine __$\hash\hash\hash$__ to start a frame and frametitle
    - (Nested) bullet and numbered lists
    - Text formatting (*italic*, **bold becomes italic + alerted**) 
    - Redefine __$\hash\hash\hash\hash$__ to start a block with title \linebreak
          and __\texttt{-{}-{}-{}-}__ to end the block
    - ___Compile with \texttt{-{}-shell-escape}___ (Overleaf does this already)
* (Alternative approaches: Pandoc, wikitobeamer)

\end{frame}

%%%%%%%%%%%%%%%%%%%%%%

### Caveats

- Nothing too complicated! 
- No verbatim or fragile stuff!
- No $\hash$ and \textunderscore{} characters!\linebreak 
  (I used `$\hash$` and `\textunderscore`)
- Can't pass options to frames
- __Need to write \texttt{\textbackslash end\string{frame\string}} manually!__

\end{frame}

%%%%%%%%%%%%%%%%%%%%%%