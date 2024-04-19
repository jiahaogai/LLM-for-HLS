### ACCEL PARALLEL FACTOR=auto{32}
 
#pragma ACCEL PARALLEL FACTOR=auto{32}
  
#pragma ACCEL PIPELINE auto{__PIPE__L1}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L1}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L1}
  for (i = 0; i < 128; i++) {
    A[i] = SEQA[i];
  }
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L2}
  
#pragma ACCEL PIPELINE auto{__PIPE__L2}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__L2}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__L3}
  for (i = 0; i < 128; i++) {
    B[i] = SEQB[i];
  }
  
#pragma ACCEL PIPELINE auto{__PIPE__score}
  
#pragma ACCEL TILE FACTOR=auto{__TILE__score}
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__score}
  needwun_score(A,B,M,ptr);
  
#pragma ACCEL PARALLEL FACTOR=auto{__PARA__trace}
  needwun_trace(A,B,ALIGN_A,ALIGN_B,M,ptr);
}