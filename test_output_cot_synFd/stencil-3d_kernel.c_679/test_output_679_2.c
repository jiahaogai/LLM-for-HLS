}
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
    for (j = 0; j < 8; j++) {
      SIJ = SI[j];
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      for (i = 0; i < 8; i++) {
        sol[idx(tj,ti,k,j,i)] = W[j] * SIJ * SK[i];
      }
    }
  }
//#pragma endscop
}