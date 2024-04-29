#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{3}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
      for (i = 1; i < 32 + 1; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        buf = orig[i_col + (32 + 1) * (j_col + (32 + 1) * k_col)] + 
          orig[i_col + (32 + 1) * (j_col + (32 + 1) * k_col)] + 
          orig[i_col + (32 + 1) * (j_col + (32 + 1) * k_col)] + 
          orig[i_col + (32 + 1) * (j_col + (32 + 1) * k_col)] + 
          orig[i_col + (32 + 1) * (j_col + (32 + 1) * k_col)] + 
          orig[i_col + (32 + 1) * (j_col + (32 + 1) * k_col)] + 
          orig[i_col + (32 + 1) * (j_col + (32 + 1) * k_col)] + 
          orig[i_col + (32 + 1) * (j_col + (32 + 1) * k_col)];
        sol[i + (32 + 1) * (j + (32 + 1) * k)] = buf;
      }
    }
  }
}