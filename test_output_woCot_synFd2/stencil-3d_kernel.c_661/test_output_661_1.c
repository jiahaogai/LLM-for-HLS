#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{3}
 
#pragma ACCEL PIPELINE auto{off}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PARALLEL FACTOR=auto{2}
 void kernel_stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long buf;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loop_k:
  for (k = 2; k < 32 + 2; k++) {
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loop_j:
    for (j = 2; j < 32 + 2; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_i:
      for (i = 2; i < 32 + 2; i++) {
        i_col = i - 2;
        j_col = j - 2;
        k_col = k - 2;
        buf = orig[IX(k_col, j_col, i_col)] + orig[IX(k_col, j_col, i_col + 1)] + orig[IX(k_col, j_col + 1, i_col)] + orig[IX(k_col, j_col + 1, i_col + 1)] + orig[IX(k_col + 1, j_col, i_col)] + orig[IX(k_col + 1, j_col, i_col + 1)] + orig[IX(k_col + 1, j_col + 1, i_col)] + orig[IX(k_col + 1, j_col + 1, i_col + 1)];
        sol[IX(k, j, i)] = buf;
      }
    }
  }
}
 #pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  
#pragma ACCEL PARALLEL FACTOR=auto{3}
  loop_k:
  for (k = 0; k < 32 + 2; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{2}
    loop_j:
    for (j = 0; j < 32 + 2; j++) {
      
#pragma ACCEL PARALLEL FACTOR=auto{16}
      loop_i:
      for (i = 0; i < 32 + 2; i++) {
        orig[IX(k, j, i)] = sol[IX(k, j, i)];
      }
    }
  }
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  kernel_stencil3d(32, 32, orig, sol);
}