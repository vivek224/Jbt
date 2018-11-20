## Easy-to-use Within-node Performance Tuning Techniques to Scale Applications on Supercomputers

__Vivek Kale__

**Abstract**: The emergence of sophisticated applications and complex
supercomputers cause performance bottlenecks that create challenges,
motivating novel and easy-to-use techniques that mitigate impact of
the bottlenecks. A particular challenge is load imbalances across
cores of a multicore node on a supercomputer that can slow down an
application’s execution significantly. Although dynamic load
balancing within a multicore node can mitigate these problems in
principle, such balancing is challenging because of its impact on
data movement and synchronization overhead. In this talk, I first
discuss the aforementioned challenge, in the context of challenges
in running sophisticated applications on emerging supercomputers.
Then, I discuss a series of novel loop scheduling strategies for
MPI+OpenMP programs that mitigate node-local load imbalances without
incurring high overheads. The underlying methodology helps speed up
applications on supercomputers with minimal application programmer
intervention. Finally, I discuss work on combining my loop scheduling
strategies with other performance optimizations and for making
them easy-to-use. Specifically, I describe: (a) a proposal for
User-Defined Schedules in OpenMP for supporting myriad efficient
loop scheduling strategies, including application-specific ones;
(b) a technique that combines my intra-node loop scheduling strategies
with inter-node load balancing strategies in the Charm++ runtime
system; and (c) some ideas for how to program nodes with GPGPUs
based on loop scheduling strategies and data movement optimizations.

\end{frame}