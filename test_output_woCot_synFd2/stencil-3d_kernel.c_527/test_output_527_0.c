#pragma ACCEL PIPELINE auto{}

#pragma ACCEL TILE FACTOR=auto{1}

#pragma ACCEL PIPELINE auto{flatten}

#pragma ACCEL TILE FACTOR=auto{2}

#pragma ACCEL PARALLEL FACTOR=auto{1}
void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long bound;
  long t1;
  long t2;
  long t3;
  
#pragma ACCEL PARALLEL FACTOR=auto{1}
  loopk:
  for (k = 1; k < 32 + 1; k++) {
    
#pragma ACCEL PIPELINE auto{off}
    
#pragma ACCEL TILE FACTOR=auto{1}
    
#pragma ACCEL PARALLEL FACTOR=auto{1}
    loopj:
    for (j = 1; j < 32 + 1; j++) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{1}
      loopi:
      for (i = 1; i < 32 + 1; i++) {
        i_col = i - 1;
        j_col = j - 1;
        k_col = k - 1;
        t1 = orig[i_col + (j_col + (k_col * 32)) * 39];
        t2 = orig[i_col + ((j_col + (k_col * 32)) + 32) * 39];
        t3 = orig[i_col + ((j_col + (k_col * 32)) + 32L * 32) * 39];
        sol[i + j * 32 + k * 32 * 32] = ((t1 + t2) + t3) / 3L;
      }
    }
  }
}