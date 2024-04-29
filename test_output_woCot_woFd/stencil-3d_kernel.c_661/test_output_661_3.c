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
  for (k = 1; k < 40; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 1; j < 40; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loop_i:
      for (i = 1; i < 40; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        buf = orig[INDEX(i_col, j_col, k_col)] + orig[INDEX(i_col, j_col, k)] + orig[INDEX(i_col, j, k_col)] + orig[INDEX(i_col, j, k)] + orig[INDEX(i, j_col, k_col)] + orig[INDEX(i, j_col, k)] + orig[INDEX(i, j, k_col)] + orig[INDEX(i, j, k)];
        sol[INDEX(i, j, k)] = buf;
      }
    }
  }
}