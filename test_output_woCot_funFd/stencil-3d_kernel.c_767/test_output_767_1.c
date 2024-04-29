#pragma ACCEL kernel

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
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{2}
  loopj:
/* Standardize from: for(j = 1;j < 392;j++) {...} */
  for (j = 1 + 392 * 0; j < 392 + 392 * 0; j += 392 * 0) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{1}
    loopk:
/* Standardize from: for(k = 1;k < 392;k++) {...} */
    for (k = 1 + 392 * 0; k < 392 + 392 * 0; k += 392 * 0) {
      
#pragma ACCEL PIPELINE auto{off}
      
#pragma ACCEL TILE FACTOR=auto{1}
      
#pragma ACCEL PARALLEL FACTOR=auto{8}
      loopi:
/* Standardize from: for(i = 1;i < 392;i++) {...} */
      for (i = 1 + 392 * 0; i < 392 + 392 * 0; i += 392 * 0) {
        i_col = i - 1 + 392 * (k - 1);
        j_col = j - 1 + 392 * (k - 1);
        k_col = k - 1;
        t1 = orig[i_col + 392 * j_col];
        t2 = orig[i_col + 392 * (j_col + 1)];
        t3 = orig[i_col + 392 * (j_col + 2)];
        bound = (392 - 1 - 0) * (2);
        loop1:
        for (k = 0; k < bound; k++) {
          ((long *)sol)[i_col + 392 * ((j_col) + 392 * k)] = C0 * (t1) + 
            C1 * (t2 + t3);
        }
      }
    }
  }
}