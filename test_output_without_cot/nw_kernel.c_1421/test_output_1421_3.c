#pragma ACCEL PARALLEL FACTOR=auto{16}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}

  needwun(SEQA,SEQB,alignedA,alignedB,M,ptr);