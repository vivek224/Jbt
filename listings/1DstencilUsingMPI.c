for(ts = 0; ts < 1000; ts++) // 1000 timesteps
  {
    MPI_Irecv(leftGhost,gSz,MPI_DOUBLE,id-1,..,&requests[numRequests++]);
    MPI_Irecv(rightGhost,gSz,MPI_DOUBLE,id+1, ..., &requests[numRequests++]);
    MPI_Isend(leftBoundary,bSz,MPI_DOUBLE,id-1, ..., &requests[numRequests++]);
    MPI_Isend(rightBoundary,bSz,MPI_DOUBLE, id+1,..., &requests[numRequests++]); 
    MPI_Waitall(numRequests,requests, MPI_STATUSES_IGNORE);
    for(i = 0; i < n; i++) w[i] = (u[i-1] + u[i+1] + u[i])/3.0; 
    temp = w;
    w = u;
    u = temp; 
  }


