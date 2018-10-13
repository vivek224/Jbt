for(ts = 0; ts < 1000; ts++) // 1000 timesteps
  {
    if(id > 0)
      MPI_Irecv(leftGhost, gSize, MPI_DOUBLE, id - 1, 0 , MPI_COMM_WORLD, &requests[numRequests++]);
    if(id < p-1)
      MPI_Irecv(rightGhost, gSize, MPI_DOUBLE, id + 1, 0 , MPI_COMM_WORLD, &requests[numRequests++]);
    if (id > 0)
      MPI_Isend(leftBoundary, bSize, MPI_DOUBLE, id-1, 0, MPI_COMM_WORLD, &requests[numRequests++]);
    if (id < p - 1 )
      MPI_Isend(rightBoundary, bSize, MPI_DOUBLE, id+1, 0, MPI_COMM_WORLD, &requests[numRequests++]); 
    MPI_Waitall(numRequests, requests, MPI_STATUSES_IGNORE);
    for(i = 0; i < n; i++)
	w[i] =  (u[i-1] + u[i+1] + u[i])/3.0; 
    temp = w;
    w = u;
    u = temp; 
  }


