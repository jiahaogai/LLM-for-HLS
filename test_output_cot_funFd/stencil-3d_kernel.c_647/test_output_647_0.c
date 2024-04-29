#pragma ACCEL kernel

void stencil3d(long C0,long C1,long orig[39304],long sol[32768])
{
  long i;
  long j;
  long k;
  long k_col;
  long j_col;
  long i_col;
  long ko;
  long ki;
  long kj;
  long tmp;
  
#pragma ACCEL PIPELINE auto{off}
  
#pragma ACCEL TILE FACTOR=auto{1}
  loop_i:
/* Standardize from: for(i = 1; i < 32; i++) {...} */
  for (i = 1 + 0; i < 33 - 1; i += 1) {
    
#pragma ACCEL PIPELINE auto{}
    
#pragma ACCEL TILE FACTOR=auto{2}
    loop_j:
/* Standardize from: for(j = 1; j < 32; j++) {...} */
    for (j = 1 + 0; j < 33 - 1; j += 1) {
      
#pragma ACCEL PIPELINE auto{}
      
#pragma ACCEL TILE FACTOR=auto{1}
      loop_k:
/* Standardize from: for(k = 1; k < 32; k++) {...} */
      for (k = 1 + 0; k < 33 - 1; k += 1) {
        k_col = ((33 * (k - 1)) + 1);
        j_col = ((33 * (j - 1)) + 1);
        i_col = ((33 * (i - 1)) + 1);
        ko = 0;
        
#pragma ACCEL PARALLEL FACTOR=auto{16}
        loop_ki:
        for (ki = 1; ki < 33; ki++) {
          tmp = ((ki * i_col) + j_col);
          sol[tmp] = ((C0 * orig[ko]) + (C1 * (tmp = ((ki * j_col) + k_col), orig[tmp])));
          ko++;
        }
      }
    }
  }
}